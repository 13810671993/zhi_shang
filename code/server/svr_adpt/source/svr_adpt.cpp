#include "svr_adpt_common.h"

CSvrAdpt::CSvrAdpt()
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

void CSvrAdpt::DestroyInstance()
{
    if (m_pSvrAdpt != NULL)
    {
        delete m_pSvrAdpt;
        m_pSvrAdpt = NULL;
    }
}

VOID CSvrAdpt::SetMsgTransimit(IN CMsgTransmit* pMsgTransmit)
{
    m_pMsgTransmit = pMsgTransmit;
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
    return m_pMsgTransmit->PushMessage(u32NodeID, u32MsgType, pcMsg, u32MsgLen);
}

VOID CSvrAdpt::PostMessage(IN UINT32 u32NodeID, IN UINT32 u32MsgType, IN UINT32 u32MsgLen, IN const CHAR* pcMsg)
{
    CNetworkMgr::GetInstance()->SendMessage(u32NodeID, u32MsgType, u32MsgLen, pcMsg);
}

