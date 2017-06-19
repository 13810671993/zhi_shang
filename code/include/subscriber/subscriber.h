#ifndef __SUBSCRIBER_H__
#define __SUBSCRIBER_H__

class CSubMsgHandler;
class CSubscriber
{
public:
    static CSubscriber* GetInstance();
    static VOID         DestroyInstance();
public:
    virtual UINT32  PushMessage(IN UINT32 u32NodeID, IN UINT32 u32MsgType, IN CHAR* pcMsg, IN UINT32 u32MsgLen) = 0;
    virtual UINT32  SubscribeMessage(IN UINT32 u32MsgType, IN CSubMsgHandler* pSubMsgHandler) = 0;

protected:
    CSubscriber();
    virtual ~CSubscriber();

};

#endif
