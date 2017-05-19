#include "network_common.h"

boost::lockfree::queue<CNetInnerMsg*, boost::lockfree::fixed_sized<FALSE>> g_netMsgQueue(0);

CNetworkMgrImp::CNetworkMgrImp() : m_pNetConnectionMgr(NULL), m_pAdpt(NULL), m_pFunMessageCallback(NULL)
{
    m_pNetConnectionMgr = new CNetConnectionMgr();
    boost::thread threadImp(boost::bind(&CNetworkMgrImp::PushMessage2AdptThread, this));
    std::cout << "创建线程" << std::endl;
}

CNetworkMgrImp::~CNetworkMgrImp()
{

}

UINT32 CNetworkMgrImp::RegistAdpt(CAdpt* pAdpt)
{
    m_pAdpt = pAdpt;
    return COMERR_OK;
}

VOID CNetworkMgrImp::SendMessage(IN UINT32 u32NodeID, IN UINT32 u32MsgType, IN UINT32 u32MsgLen, IN const CHAR* pcMsg)
{
    m_pNetConnectionMgr->PostMessage(u32NodeID, u32MsgType, u32MsgLen, pcMsg);
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
    return COMERR_OK;
}

VOID CNetworkMgrImp::ListenThread(CNetworkMgrImp* pThis, UINT16 u16Port)
{
    pThis->m_pNetConnectionMgr->StartListen(u16Port);
}

VOID CNetworkMgrImp::PushMessage2AdptThread(CNetworkMgrImp* pThis)
{
    CNetInnerMsg* pNetMsg = NULL;
    while (1)
    {
        // 从队列中弹出数据 写到adpt中去
        if (g_netMsgQueue.pop(pNetMsg) && pNetMsg != NULL)
        {
            pThis->m_pAdpt->PushMessage(pNetMsg->GetNodeID(), pNetMsg->GetMsgType(), pNetMsg->GetMsgBuf(), pNetMsg->GetMsgLen());
            delete pNetMsg;
            pNetMsg = NULL;
        }
        else
            BOOST_SLEEP(100);
    }
}

UINT32 CNetworkMgrImp::Init()
{
    boost::thread threadImp(boost::bind(&RecvMessageFromServerThread, this));
    return COMERR_OK;
}

UINT32 CNetworkMgrImp::Connect(IN const CHAR* pcIpAddr, IN UINT16 u16Port, OUT UINT32& u32NodeID)
{
    // 1. 创建一个空会话
    // 2. 建立连接
    m_pNetConnectionMgr->Connect(pcIpAddr, u16Port, u32NodeID);
    return COMERR_OK;
}

UINT32 CNetworkMgrImp::RegistRecvMsgCallBack(PFUN_MESSAGE_CALLBACK pFunMessageCallback)
{
    m_pFunMessageCallback = pFunMessageCallback;
    return COMERR_OK;
}

VOID CNetworkMgrImp::RecvMessageFromServerThread(CNetworkMgrImp* pThis)
{
    UINT32 u32NodeID = 0;
    UINT32 u32MsgType = 0;
    std::string strMsg;
    UINT32 u32Ret = 0;
    while (1)
    {
        if (pThis->m_pNetConnectionMgr->IsConnect())
        {
            // 如果客户端连接上了 然后就读取数据
            do 
            {
                u32Ret = pThis->m_pNetConnectionMgr->RecvMessage(u32NodeID, u32MsgType, strMsg);
                CHECK_ERR_BREAK(u32Ret == 0, u32Ret, "RecvMessage Failed. u32Ret = 0x%x\n", u32Ret);
            } while (0);
            std::cout << strMsg << std::endl;

            // 然后把读取来的数据通过回调返回给客户端
            pThis->m_pFunMessageCallback(u32NodeID, u32MsgType, strMsg.length(), strMsg.data());

        }
        else // 没有连接 休息
            BOOST_SLEEP(1000);
    }
}

