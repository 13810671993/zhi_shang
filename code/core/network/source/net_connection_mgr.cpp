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
        // 创建端点
        boost::asio::ip::tcp::endpoint  end_point(boost::asio::ip::tcp::v4(), u16Port);
        // protocol
        m_acceptor.open(boost::asio::ip::tcp::v4());
        // bind
        m_acceptor.bind(end_point);
        // listen
        m_acceptor.listen();
        // 开始接受连接
        u32Ret = DoAccept();
        CHECK_ERR_BREAK(u32Ret == 0, u32Ret, "DoAccept Failed. u32Ret = 0x%x", u32Ret);
    } while (0);

    // 启动接受connect
    LogInfo("Start listen. port = %d", u16Port);
    m_ioServer.run();
    return u32Ret;
}

UINT32 CNetConnectionMgr::DoAccept()
{
    boost::shared_ptr<CNetSession> ptrSession(new CNetSession(m_ioServer, this));
    // 注册AcceptHandler
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

    // 有一个新的连接

    // 记录下来这个新的连接 为其分配节点ID
    UINT32  u32Ret = 0;
    UINT32  u32NodeID = 0;
    do 
    {
        u32Ret = m_pNodeIDLayer->GenerateNetNodeID(ptrSession, u32NodeID);
        CHECK_ERR_BREAK(u32Ret == 0, u32Ret, "GenerateNetNodeID Failed. u32Ret = 0x%x", u32Ret);
    } while (0);
    // 启动这个会话
    ptrSession->StartSession(u32NodeID);

    // 目前还不是很明白这个reset 不过目的是为下一个新的连接准备一个新的CNetSession
    ptrSession.reset(new CNetSession(m_ioServer, this));
    // 继续接受新的连接 没有继续调用 将不再接收其他连接
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

