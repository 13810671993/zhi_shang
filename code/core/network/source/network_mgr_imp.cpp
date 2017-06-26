#include "network_common.h"

boost::lockfree::queue<CNetInnerMsg*, boost::lockfree::fixed_sized<FALSE>> g_netMsgQueue(0);

CNetworkMgrImp::CNetworkMgrImp() : 
      m_pAdpt(NULL)
    , m_pNodeIDLayer(NULL)
    , m_ioServer()
    , m_acceptor(m_ioServer)
{
    m_pNodeIDLayer = new CNetNodeIDLayer();

    boost::thread threadImp(boost::bind(&CNetworkMgrImp::PushMessage2AdptThread, this));
#ifdef _DEBUG_
    std::cout << "启动网络线程" << std::endl;
#endif
    LogInfo("PushMessage2AdptThread start.");
}

CNetworkMgrImp::~CNetworkMgrImp()
{
    if (m_pNodeIDLayer != NULL)
    {
        delete m_pNodeIDLayer;
        m_pNodeIDLayer = NULL;
    }
}

UINT32 CNetworkMgrImp::RegistAdpt(IN CAdpt* pAdpt)
{
    m_pAdpt = pAdpt;
    return COMERR_OK;
}

VOID CNetworkMgrImp::PostMessage(IN UINT32 u32NodeID, IN UINT32 u32MsgType, IN UINT32 u32MsgLen, IN const CHAR* pcMsg)
{
    boost::shared_ptr<CNetSession> ptrSession;
    do 
    {
        UINT32 u32Ret = m_pNodeIDLayer->GetSession(u32NodeID, ptrSession);
        CHECK_ERR_BREAK(u32Ret == 0, u32Ret, "GetSession Failed. u32Ret = 0x%x", u32Ret);
        ptrSession->PostMessage(u32MsgType, u32MsgLen, pcMsg);
    } while (0);
}

CNetworkMgrImp* CNetworkMgrImp::m_pNetworkMgrImp = NULL;

CNetworkMgrImp* CNetworkMgrImp::GetInstance()
{
    if (m_pNetworkMgrImp == NULL)
        m_pNetworkMgrImp = new CNetworkMgrImp();
    return m_pNetworkMgrImp;
}

VOID CNetworkMgrImp::DestroyInstance()
{
    if (m_pNetworkMgrImp != NULL)
    {
        delete m_pNetworkMgrImp;
        m_pNetworkMgrImp = NULL;
    }
}

UINT32 CNetworkMgrImp::StartListen(IN UINT16 u16Port)
{
    // 在这里 我要新启动一根线程去执行监听
    boost::thread threadImp(boost::bind(&ListenThread, this, u16Port));
    LogInfo("ListenThread start.");
    return COMERR_OK;
}

UINT32 CNetworkMgrImp::DoAccept()
{
    boost::shared_ptr<CNetSession> ptrSession(new CNetSession(m_ioServer, this));
    // 注册AcceptHandler
    m_acceptor.async_accept(ptrSession->GetSocket(), boost::bind(&CNetworkMgrImp::AcceptHandlerCB, this, boost::asio::placeholders::error, ptrSession));

    return COMERR_OK;
}

VOID CNetworkMgrImp::AcceptHandlerCB(IN const boost::system::error_code& ec, IN boost::shared_ptr<CNetSession>& ptrSession)
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
    m_acceptor.async_accept(ptrSession->GetSocket(), boost::bind(&CNetworkMgrImp::AcceptHandlerCB, this, boost::asio::placeholders::error, ptrSession));
}

UINT32 CNetworkMgrImp::Disconnect(IN UINT32 u32NodeID)
{
#ifdef _DEBUG_
    std::cout << u32NodeID << std::endl;
#endif
    LogInfo("Disconnect u32NodeID = %u", u32NodeID);
    return m_pNodeIDLayer->ReleaseNetNodeID(u32NodeID);
}

VOID CNetworkMgrImp::ListenThread(IN CNetworkMgrImp* pThis, IN UINT16 u16Port)
{
    UINT32  u32Ret = 0;
    do
    {
        // 创建端点
        boost::asio::ip::tcp::endpoint  end_point(boost::asio::ip::tcp::v4(), u16Port);
        // protocol
        pThis->m_acceptor.open(boost::asio::ip::tcp::v4());
        // bind
        pThis->m_acceptor.bind(end_point);
        // listen
        pThis->m_acceptor.listen();
        // 开始接受连接
        u32Ret = pThis->DoAccept();
        CHECK_ERR_BREAK(u32Ret == 0, u32Ret, "DoAccept Failed. u32Ret = 0x%x", u32Ret);
    } while (0);

    // 启动接受connect
    LogInfo("Start listen. port = %d", u16Port);
    pThis->m_ioServer.run();
}

#ifdef _WIN32_
extern LARGE_INTEGER  nFreq, t1, t2;
#else
#endif

VOID CNetworkMgrImp::PushMessage2AdptThread(IN CNetworkMgrImp* pThis)
{
    CNetInnerMsg* pNetMsg = NULL;
    while (1)
    {
        // 从队列中弹出数据 写到adpt中去
        if (g_netMsgQueue.pop(pNetMsg) && pNetMsg != NULL)
        {
            pThis->m_pAdpt->PushMessage(pNetMsg->GetNodeID(), pNetMsg->GetMsgType(), pNetMsg->GetMsgLen(), pNetMsg->GetMsgBuf());
            delete pNetMsg;
            pNetMsg = NULL;
#ifdef _WIN32_
            //QueryPerformanceCounter(&t2);
            //double dt = (t2.QuadPart - t1.QuadPart) / (double)nFreq.QuadPart;
            //LogDebug("时间差: %lfus", dt * 1000000);
#else
#endif

        }
        else
        {
            BOOST_SLEEP(10);
        }
    }
}
