#include "network_common.h"

boost::lockfree::queue<CNetInnerMsg*, boost::lockfree::fixed_sized<FALSE>> g_netMsgQueue(0);

CNetworkMgrImp::CNetworkMgrImp() : m_pNetConnectionMgr(NULL), m_pAdpt(NULL)
{
    m_pNetConnectionMgr = new CNetConnectionMgr();
    boost::thread threadImp(boost::bind(&CNetworkMgrImp::PushMessage2AdptThread, this));
#ifdef _DEBUG
    std::cout << "启动网络线程" << std::endl;
#endif
    LogInfo("PushMessage2AdptThread start.");
}

CNetworkMgrImp::~CNetworkMgrImp()
{

}

UINT32 CNetworkMgrImp::RegistAdpt(IN CAdpt* pAdpt)
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
    LogInfo("ListenThread start.");
    return COMERR_OK;
}

VOID CNetworkMgrImp::ListenThread(IN CNetworkMgrImp* pThis, IN UINT16 u16Port)
{
    pThis->m_pNetConnectionMgr->StartListen(u16Port);
}

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
        }
        else
            BOOST_SLEEP(100);
    }
}
