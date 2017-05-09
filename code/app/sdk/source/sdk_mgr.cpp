#include "sdk_common.h"

CSdkMgr::CSdkMgr()
{

}

CSdkMgr::~CSdkMgr()
{

}

CSdkMgr* CSdkMgr::m_pSdkMgr = NULL;

CSdkMgr* CSdkMgr::GetInstance()
{
    if (m_pSdkMgr == NULL)
        m_pSdkMgr = new CSdkMgr();
    return m_pSdkMgr;
}

VOID CSdkMgr::DestroyInstance()
{
    if (m_pSdkMgr != NULL)
    {
        delete m_pSdkMgr;
        m_pSdkMgr = NULL;
    }
}

UINT32 CSdkMgr::Init()
{
    return 0;
}

UINT32 CSdkMgr::Connect(IN const CHAR* pcIpAddr, IN UINT16 u16Port, OUT UINT32& u32NodeID)
{
    return 0;
}

UINT32 CSdkMgr::SendMessage(IN UINT32 u32NodeID, IN UINT32 u32MsgType, IN UINT32 u32MsgLen, IN const CHAR* pcMsg)
{
    return 0;
}

UINT32 CSdkMgr::RegistRecvMsgCallBack(PFN_SDK_MESSAGE_CALLBACK pFunMsgCB)
{
    return 0;
}

