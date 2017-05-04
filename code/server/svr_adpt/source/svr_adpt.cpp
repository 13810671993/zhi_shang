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

VOID CSvrAdpt::SetMsgTransmitLayer(CMsgTransmit* pMsgTransmitLayer)
{
    m_pMsgTransmitLayer = pMsgTransmitLayer;
}

UINT32 CSvrAdpt::StartListen(IN UINT16 u16Port)
{
    // ¿ªÆôÄ³Ò»¶Ë¿Ú¼àÌý
    // adpt²ãÖ±½ÓÏòÍøÂçµ×²ã×¢²á
	return CNetworkMgr::GetInstance()->StartListen(u16Port);
}

UINT32 CSvrAdpt::RegistAdpt(CAdpt* pAdpt)
{
    UINT32  u32Ret = 0;
    return CNetworkMgr::GetInstance()->RegistAdpt(pAdpt);
    return u32Ret;
}

UINT32 CSvrAdpt::RecvMessage(UINT32 u32NodeID, UINT32 u32MsgType, CHAR* pcMsg, UINT32 u32MsgLen)
{
    return m_pMsgTransmitLayer->PushMessage(u32NodeID, u32MsgType, pcMsg, u32MsgLen);
}

UINT32 CSvrAdpt::SendMessage()
{
    UINT32  u32Ret = 0;

    return u32Ret;
}

