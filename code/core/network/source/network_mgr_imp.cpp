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
    std::cout << "���������߳�" << std::endl;
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
    // ������ ��Ҫ������һ���߳�ȥִ�м���
    boost::thread threadImp(boost::bind(&ListenThread, this, u16Port));
    LogInfo("ListenThread start.");
    return COMERR_OK;
}

UINT32 CNetworkMgrImp::DoAccept()
{
    boost::shared_ptr<CNetSession> ptrSession(new CNetSession(m_ioServer, this));
    // ע��AcceptHandler
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
        // �����˵�
        boost::asio::ip::tcp::endpoint  end_point(boost::asio::ip::tcp::v4(), u16Port);
        // protocol
        pThis->m_acceptor.open(boost::asio::ip::tcp::v4());
        // bind
        pThis->m_acceptor.bind(end_point);
        // listen
        pThis->m_acceptor.listen();
        // ��ʼ��������
        u32Ret = pThis->DoAccept();
        CHECK_ERR_BREAK(u32Ret == 0, u32Ret, "DoAccept Failed. u32Ret = 0x%x", u32Ret);
    } while (0);

    // ��������connect
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
        // �Ӷ����е������� д��adpt��ȥ
        if (g_netMsgQueue.pop(pNetMsg) && pNetMsg != NULL)
        {
            pThis->m_pAdpt->PushMessage(pNetMsg->GetNodeID(), pNetMsg->GetMsgType(), pNetMsg->GetMsgLen(), pNetMsg->GetMsgBuf());
            delete pNetMsg;
            pNetMsg = NULL;
#ifdef _WIN32_
            //QueryPerformanceCounter(&t2);
            //double dt = (t2.QuadPart - t1.QuadPart) / (double)nFreq.QuadPart;
            //LogDebug("ʱ���: %lfus", dt * 1000000);
#else
#endif

        }
        else
        {
            BOOST_SLEEP(10);
        }
    }
}
