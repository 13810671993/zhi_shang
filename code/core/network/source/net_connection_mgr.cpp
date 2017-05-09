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
    boost::system::error_code error;
    do
    {
        // �����˵�
        boost::asio::ip::tcp::endpoint  end_point(boost::asio::ip::tcp::v4(), u16Port);
        CHECK_ERR_BREAK(error == 0, (UINT32)error.value(), "Create endpoint Failed. error = 0x%x\n", error.value());
        // protocol
        m_acceptor.open(boost::asio::ip::tcp::v4());
        CHECK_ERR_BREAK(error == 0, (UINT32)error.value(), "Acceptor open Failed. error = 0x%x\n", error.value());
        // bind
        m_acceptor.bind(end_point);
        CHECK_ERR_BREAK(error == 0, (UINT32)error.value(), "Acceptor bind Failed. error = 0x%x\n", error.value());
        // listen
        m_acceptor.listen();
        CHECK_ERR_BREAK(error == 0, (UINT32)error.value(), "Acceptor listen Failed. error = 0x%x\n", error.value());
        // ��ʼ��������
        u32Ret = DoAccept();
        CHECK_ERR_BREAK(u32Ret == 0, u32Ret, "DoAccept Failed. u32Ret = 0x%x\n", u32Ret);
    } while (0);

    // ��������connect
    std::cout << "�������� port: " << u16Port << std::endl;
    RunIOServer();
    return u32Ret;
}

UINT32 CNetConnectionMgr::DoAccept()
{
    boost::shared_ptr<CNetSession> ptrSession(new CNetSession(m_ioServer, this));
    // ע��AcceptHandler
    m_acceptor.async_accept(ptrSession->GetSocket(), boost::bind(&CNetConnectionMgr::AcceptHandlerCB, this, boost::asio::placeholders::error, ptrSession));

    return COMERR_OK;
}

VOID CNetConnectionMgr::RunIOServer()
{
    m_ioServer.run();
}

VOID CNetConnectionMgr::AcceptHandlerCB(const boost::system::error_code& ec, boost::shared_ptr<CNetSession> ptrSession)
{
    if (ec)
        return;
    // ��һ���µ�����

    // ��¼��������µ����� Ϊ�����ڵ�ID
    UINT32  u32Ret = 0;
    UINT32  u32NodeID = 0;
    do 
    {
        u32Ret = m_pNodeIDLayer->GenerateNetNodeID(ptrSession, u32NodeID);
        CHECK_ERR_BREAK(u32Ret == 0, u32Ret, "GenerateNetNodeID Failed. u32Ret = 0x%x\n", u32Ret);
    } while (0);
    // ��������Ự
    ptrSession->StartSession(u32NodeID);

    // Ŀǰ�����Ǻ��������reset ����Ŀ����Ϊ��һ���µ�����׼��һ���µ�CNetSession
    ptrSession.reset(new CNetSession(m_ioServer, this));
    // ���������µ����� û�м������� �����ٽ�����������
    m_acceptor.async_accept(ptrSession->GetSocket(), boost::bind(&CNetConnectionMgr::AcceptHandlerCB, this, boost::asio::placeholders::error, ptrSession));
}

UINT32 CNetConnectionMgr::Disconnect(UINT32 u32NodeID)
{
    std::cout << u32NodeID << std::endl;
    return m_pNodeIDLayer->ReleaseNetNodeID(u32NodeID);
}

VOID CNetConnectionMgr::PostMessage(IN UINT32 u32NodeID, IN UINT32 u32MsgType, IN UINT32 u32MsgLen, IN const CHAR* pcMsg)
{
    boost::shared_ptr<CNetSession> ptrSession;
    do 
    {
        UINT32 u32Ret = m_pNodeIDLayer->GetSession(u32NodeID, ptrSession);
        CHECK_ERR_BREAK(u32Ret == 0, u32Ret, "GetSession Failed. u32Ret = 0x%x\n", u32Ret);
    } while (0);
    ptrSession->PostMessage(u32MsgType, u32MsgLen, pcMsg);
}

