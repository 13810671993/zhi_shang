#include "msg_mgr_common.h"

CMsgMgrImp::CMsgMgrImp()
{
    m_pSubscriber       = CSubscriber::GetInstance();
    m_pMsgLayer         = new CMsgTransmitImp();
    m_pMsgLayer->SetSubscriber(m_pSubscriber);
}

CMsgMgrImp::~CMsgMgrImp()
{

}

CMsgMgrImp* CMsgMgrImp::m_pMsgMgrImp = NULL;

CMsgMgrImp* CMsgMgrImp::GetInstance()
{
    if (m_pMsgMgrImp == NULL)
        m_pMsgMgrImp = new CMsgMgrImp();
    return m_pMsgMgrImp;
}

VOID CMsgMgrImp::DestroyInstance()
{
    if (m_pMsgMgrImp != NULL)
    {
        delete m_pMsgMgrImp;
        m_pMsgMgrImp = NULL;
    }
}

VOID CMsgMgrImp::AddAdpt(IN CAdpt* pAdpt)
{
    m_pAdpt = pAdpt;
    m_pAdpt->RegistAdpt(pAdpt);
	SetMsgTransmitLayer2Adpt();
}

VOID CMsgMgrImp::SetMsgTransmitLayer2Adpt()
{
    m_pAdpt->SetMsgTransmitLayer(m_pMsgLayer);
}

UINT32 CMsgMgrImp::StartLisen(IN UINT16 u16Port)
{
    // 向底层去执行 开启监听某一端口
    return m_pAdpt->StartListen(u16Port);
}

VOID CMsgMgrImp::PostMessage(IN UINT32 u32NodeID, IN const std::string& strMsg)
{
    m_pAdpt->PostMessage(u32NodeID, strMsg);
}

UINT32 CMsgMgrImp::SubscribeMessage(UINT32 u32MsgType, CSubMsgHandler* pSubMsgHandler)
{
    UINT32  u32Ret = 0;

    u32Ret = m_pSubscriber->SubscribeMessage(u32MsgType, pSubMsgHandler);

    return u32Ret;
}
