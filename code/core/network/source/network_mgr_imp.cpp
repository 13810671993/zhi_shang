#include "network_common.h"

boost::lockfree::queue<CNetMsgLayer*, boost::lockfree::fixed_sized<FALSE>> g_netMsgQueue(0);

CNetworkMgrImp::CNetworkMgrImp()
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

VOID CNetworkMgrImp::PostMessage(IN UINT32 u32NodeID, IN const std::string& strMsg)
{
    m_pNetConnectionMgr->PostMessage(u32NodeID, strMsg);
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
    return m_pNetConnectionMgr->StartListen(u16Port);
}

VOID CNetworkMgrImp::PushMessage2AdptThread(CNetworkMgrImp* pThis)
{
    CNetMsgLayer* pNetMsg = NULL;
    while (1)
    {
        // 从队列中弹出数据 写到adpt中去
        if (g_netMsgQueue.pop(pNetMsg) && pNetMsg != NULL)
        {
            std::cout << pNetMsg->GetMsgBuf() << std::endl;
            CMsgMgr::GetInstance()->PostMessage(pNetMsg->GetNodeID(), pNetMsg->GetMsgBuf());
            delete pNetMsg;
            pNetMsg = NULL;
        }
        else
            BOOST_SLEEP(100);
    }
}

