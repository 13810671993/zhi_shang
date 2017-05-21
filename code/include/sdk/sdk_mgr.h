#ifndef __SDK_MGR_H__
#define __SDK_MGR_H__

class CSdkMgr
{
public:
    static CSdkMgr*    GetInstance();
    static VOID        DestroyInstance();

public:
    UINT32  Init();
    UINT32  Connect(IN const CHAR* pcIpAddr, IN UINT16 u16Port, OUT UINT32& u32NodeID);
    UINT32  PostMessage(IN UINT32 u32NodeID, IN UINT32 u32MsgType, IN UINT32 u32MsgLen, IN const CHAR* pcMsg);
    UINT32  RegistRecvMsgCallBack(PFN_SDK_MESSAGE_CALLBACK pFunMsgCB);

protected:
    CSdkMgr();
    ~CSdkMgr();

private:
    static CSdkMgr* m_pSdkMgr;

    PFN_SDK_MESSAGE_CALLBACK    m_pFunMessageCB;
};

#endif // !__SDK_MGR_H__
