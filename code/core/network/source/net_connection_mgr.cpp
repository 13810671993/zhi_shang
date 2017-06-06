#include "network_common.h"

CNetConnectionMgr::CNetConnectionMgr() : m_ioServer(), m_acceptor(m_ioServer)
{
    m_pNodeIDLayer = new CNetNodeIDLayer();
}

CNetConnectionMgr::~CNetConnectionMgr()
{
    if (m_pNodeIDLayer != NULL)
    {
        delete m_pNodeIDLayer;
        m_pNodeIDLayer = NULL;
    }
}

UINT32 CNetConnectionMgr::StartListen(IN UINT16 u16Port)
{
    UINT32  u32Ret = 0;
    do
    {
        // �����˵�
        boost::asio::ip::tcp::endpoint  end_point(boost::asio::ip::tcp::v4(), u16Port);
        // protocol
        m_acceptor.open(boost::asio::ip::tcp::v4());
        // bind
        m_acceptor.bind(end_point);
        // listen
        m_acceptor.listen();
        // ��ʼ��������
        u32Ret = DoAccept();
        CHECK_ERR_BREAK(u32Ret == 0, u32Ret, "DoAccept Failed. u32Ret = 0x%x", u32Ret);
    } while (0);

    // ��������connect
    LogInfo("Start listen. port = %d", u16Port);
    m_ioServer.run();
    return u32Ret;
}

UINT32 CNetConnectionMgr::DoAccept()
{
    boost::shared_ptr<CNetSession> ptrSession(new CNetSession(m_ioServer, this));
    // ע��AcceptHandler
    m_acceptor.async_accept(ptrSession->GetSocket(), boost::bind(&CNetConnectionMgr::AcceptHandlerCB, this, boost::asio::placeholders::error, ptrSession));

    return COMERR_OK;
}

VOID CNetConnectionMgr::AcceptHandlerCB(IN const boost::system::error_code& ec, IN boost::shared_ptr<CNetSession>& ptrSession)
{
    if (ec)
    {
        LogInfo("AcceptHandlerCB not success. error_code = %d, error: %s", ec.value(), ec.message().c_str());
        return;
    }

    // ��һ���µ�����

    // ��¼��������µ����� Ϊ�����ڵ�ID
    UINT32  u32Ret = 0;
    UINT32  u32NodeID = 0;
    do 
    {
        u32Ret = m_pNodeIDLayer->GenerateNetNodeID(ptrSession, u32NodeID);
        CHECK_ERR_BREAK(u32Ret == 0, u32Ret, "GenerateNetNodeID Failed. u32Ret = 0x%x", u32Ret);
    } while (0);
    // ��������Ự
    ptrSession->StartSession(u32NodeID);

    // Ŀǰ�����Ǻ��������reset ����Ŀ����Ϊ��һ���µ�����׼��һ���µ�CNetSession
    ptrSession.reset(new CNetSession(m_ioServer, this));
    // ���������µ����� û�м������� �����ٽ�����������
    m_acceptor.async_accept(ptrSession->GetSocket(), boost::bind(&CNetConnectionMgr::AcceptHandlerCB, this, boost::asio::placeholders::error, ptrSession));
}

UINT32 CNetConnectionMgr::Disconnect(IN UINT32 u32NodeID)
{
#ifdef _DEBUG_
    std::cout << u32NodeID << std::endl;
#endif
    LogInfo("Disconnect u32NodeID = %u", u32NodeID);
    return m_pNodeIDLayer->ReleaseNetNodeID(u32NodeID);
}

VOID CNetConnectionMgr::PostMessage(IN UINT32 u32NodeID, IN UINT32 u32MsgType, IN UINT32 u32MsgLen, IN const CHAR* pcMsg)
{
    boost::shared_ptr<CNetSession> ptrSession;
    do 
    {
        UINT32 u32Ret = m_pNodeIDLayer->GetSession(u32NodeID, ptrSession);
        CHECK_ERR_BREAK(u32Ret == 0, u32Ret, "GetSession Failed. u32Ret = 0x%x", u32Ret);
    } while (0);
    ptrSession->SendMessage(u32MsgType, u32MsgLen, pcMsg);
}

