#include "msg_mgr_common.h"

CMsgMgrImp::CMsgMgrImp() :
      m_pSubscriber(NULL)
    , m_pMsgLayer(NULL)
    , m_pAdpt(NULL)
{
    m_pSubscriber       = CSubscriber::GetInstance();
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

UINT32 CMsgMgrImp::AddAdpt(IN CAdpt* pAdpt)
{
    UINT32 u32Ret = 0;
    m_pAdpt = pAdpt;
    u32Ret = m_pAdpt->RegistAdpt(pAdpt);
    m_pAdpt->SetSubscriber(m_pSubscriber);

    return u32Ret;
}

UINT32 CMsgMgrImp::StartLisen(IN UINT16 u16Port)
{
    // 向底层去执行 开启监听某一端口
    return m_pAdpt->StartListen(u16Port);
}

VOID CMsgMgrImp::PostMessage(IN UINT32 u32NodeID, IN UINT32 u32MsgType, IN UINT32 u32MsgLen, IN const CHAR* pcMsg)
{
    m_pAdpt->PostMessage(u32NodeID, u32MsgType, u32MsgLen, pcMsg);
}

UINT32 CMsgMgrImp::SubscribeMessage(IN UINT32 u32MsgType, IN CSubMsgHandler* pSubMsgHandler)
{
    return m_pSubscriber->SubscribeMessage(u32MsgType, pSubMsgHandler);
}
