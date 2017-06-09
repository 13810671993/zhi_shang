#ifndef __SUBSCRIBER_IMP_H__
#define __SUBSCRIBER_IMP_H__

// 订阅器
// 1. 自身要维护一个线程 用以异步接收adpt发送来的消息 然后分发给订阅者
// 2. 维护一个队列 异步接收网络消息
// 3. 维护一个 信令-操作者集合 映射

class CSubscribersMap;
class CSubMsgHandler;
class CSubInnerMsg;

class CSubscriberImp : public CSubscriber
{
public:
    static CSubscriberImp*  GetInstance();
    static VOID             DestroyInstance();

    UINT32          PushMessage(IN UINT32 u32NodeID, IN UINT32 u32MsgType, IN CHAR* pcMsg, IN UINT32 u32MsgLen);
    UINT32          SubscribeMessage(IN UINT32 u32MsgType, IN CSubMsgHandler* pSubMsgHandler);
private:
    CSubscriberImp();
    ~CSubscriberImp();

private:
    static  VOID    PushMsg2SubscriberThread(IN CSubscriberImp* pThis);
    UINT32          PubMessage(IN CSubInnerMsg* pMsg);

private:
    static CSubscriberImp*  m_pSubscriberImp;

    std::map<UINT32, CSubscribersMap*>      m_msgType_SubscribersMap;   // 所有逻辑模块启动后 该资源以及固定不会更改 即使如此 但还是加个锁吧 保险

    typedef boost::shared_lock<boost::shared_mutex>     TypeReadLock;
    typedef boost::unique_lock<boost::shared_mutex>     TypeWriteLock;
    boost::shared_mutex                                 m_mutex;

#ifdef _MEM_POOL_
    T_MEM_POOL  m_tMemPool;
#else
#endif
};

#endif
