#ifndef __SUBSCRIBER_H__
#define __SUBSCRIBER_H__

class CSubscriber
{
public:
    static CSubscriber* GetInstance();
    static VOID         DestroyInstance();
public:
    virtual UINT32  PushMessage(UINT32 u32NodeID, UINT32 u32MsgType, CHAR* pcMsg, UINT32 u32MsgLen) = 0;
    virtual UINT32  SubscribeMessage(IN UINT32 u32MsgType, IN CSubMsgHandler* pSubMsgHandler) = 0;

protected:
    CSubscriber();
    virtual ~CSubscriber();

private:
    static CSubscriber* m_pSubscriber;
};

#endif
