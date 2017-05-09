#include "sdk_common.h"

UINT32 Sdk_Init()
{
    CSdkMgr* p = CSdkMgr::GetInstance();
    //return CSdkMgr::GetInstance()->Init();
}

UINT32 Sdk_Connect(IN const CHAR* pcIpAddr, IN UINT16 u16Port, OUT UINT32& u32NodeID)
{
    return CSdkMgr::GetInstance()->Connect(pcIpAddr, u16Port, u32NodeID);
}

UINT32 Sdk_SendMessage(IN UINT32 u32NodeID, IN UINT32 u32MsgType, IN UINT32 u32MsgLen, IN const CHAR* pcMsg)
{
    return CSdkMgr::GetInstance()->SendMessage(u32NodeID, u32MsgType, u32MsgLen, pcMsg);
}

UINT32 Sdk_RegistRecvMsgCallBack(PFN_SDK_MESSAGE_CALLBACK pFunMsgCB)
{
    return CSdkMgr::GetInstance()->RegistRecvMsgCallBack(pFunMsgCB);
}

