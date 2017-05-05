#ifndef __SUBSCRIBER_IMP_H__
#define __SUBSCRIBER_IMP_H__

// 订阅器
// 1. 自身要维护一个线程 用以异步接收adpt发送来的消息 然后分发给订阅者
// 2. 维护一个队列 异步接收网络消息
// 3. 维护一个 信令-操作者集合 映射

class CSubscriberImp : public CSubscriber
{
public:
    static CSubscriberImp*  GetInstance();
    static VOID             DestroyInstance();

    UINT32          PushMessage(UINT32 u32NodeID, UINT32 u32MsgType, CHAR* pcMsg, UINT32 u32MsgLen);
    UINT32          SubscribeMessage(IN UINT32 u32MsgType, IN CSubMsgHandler* pSubMsgHandler);
private:
    CSubscriberImp();
    ~CSubscriberImp();

private:
    static  VOID*   PushMsg2SubscriberThread(VOID* pParm);

private:
    static CSubscriberImp*  m_pSubscriberImp;

    std::map<UINT32, CSubscribersMap*>  m_msgType_SubscribersMap;   // 所有逻辑模块启动后 该资源以及固定不会更改 所以不需要锁
};

#endif
