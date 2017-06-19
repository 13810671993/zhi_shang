#include "svr_adpt_common.h"

CSvrAdpt::CSvrAdpt() : 
    m_pSubscriber(NULL)
{

}

CSvrAdpt::~CSvrAdpt()
{

}

CSvrAdpt* CSvrAdpt::m_pSvrAdpt = NULL;

CSvrAdpt* CSvrAdpt::GetInstance()
{
    if (m_pSvrAdpt == NULL)
        m_pSvrAdpt = new CSvrAdpt();
    return m_pSvrAdpt;
}

VOID CSvrAdpt::DestroyInstance()
{
    if (m_pSvrAdpt != NULL)
    {
        delete m_pSvrAdpt;
        m_pSvrAdpt = NULL;
    }
}

VOID CSvrAdpt::SetSubscriber(IN CSubscriber* pSubscriber)
{
    m_pSubscriber = pSubscriber;
}

UINT32 CSvrAdpt::StartListen(IN UINT16 u16Port)
{
    // ¿ªÆôÄ³Ò»¶Ë¿Ú¼àÌý
    // adpt²ãÖ±½ÓÏòÍøÂçµ×²ã×¢²á
	return CNetworkMgr::GetInstance()->StartListen(u16Port);
}

UINT32 CSvrAdpt::RegistAdpt(IN CAdpt* pAdpt)
{
    UINT32  u32Ret = 0;
    return CNetworkMgr::GetInstance()->RegistAdpt(pAdpt);
}

UINT32 CSvrAdpt::PushMessage(IN UINT32 u32NodeID, IN UINT32 u32MsgType, IN UINT32 u32MsgLen, IN CHAR* pcMsg)
{
    return m_pSubscriber->PushMessage(u32NodeID, u32MsgType, pcMsg, u32MsgLen);
}

VOID CSvrAdpt::PostMessage(IN UINT32 u32NodeID, IN UINT32 u32MsgType, IN UINT32 u32MsgLen, IN const CHAR* pcMsg)
{
    CNetworkMgr::GetInstance()->PostMessage(u32NodeID, u32MsgType, u32MsgLen, pcMsg);
}

