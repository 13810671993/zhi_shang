#include "msg_mgr_common.h"

CMsgTransmitImp::CMsgTransmitImp()
{

}

CMsgTransmitImp::~CMsgTransmitImp()
{

}

VOID CMsgTransmitImp::SetSubscriber(IN CSubscriber* pSubcriber)
{
    m_pSubscriber = pSubcriber;
}

UINT32 CMsgTransmitImp::PushMessage(UINT32 u32NodeID, UINT32 u32MsgType, CHAR* pcMsg, UINT32 u32MsgLen)
{
    UINT32 u32Ret = 0;
    m_pSubscriber->PushMessage(u32NodeID, u32MsgType, pcMsg, u32MsgLen);

    return u32Ret;
}

