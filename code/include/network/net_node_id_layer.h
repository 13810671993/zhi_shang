#ifndef __NET_NODE_ID_LAYER_H__
#define __NET_NODE_ID_LAYER_H__

// 维护网络节点ID-网络连接会话映射资源
// 分配节点ID 建立与网络连接会话的映射

class CNetNodeIDLayer
{
public:
    CNetNodeIDLayer();
    ~CNetNodeIDLayer();

public:
    UINT32  GenerateNetNodeID(IN boost::shared_ptr<CNetSession> ptrSession, OUT UINT32& u32NodeID);
    UINT32  ReleaseNetNodeID(IN UINT32 u32NodeID);
    UINT32  GetSession(IN UINT32 u32NodeID, OUT boost::shared_ptr<CNetSession>& ptrSession);

    BOOL    IsConnect();
    UINT32  GetNodeID(OUT UINT32& u32NodeID);

private:
    typedef boost::shared_lock<boost::shared_mutex>     TypeReadLock;       // 读map锁
    typedef boost::unique_lock<boost::shared_mutex>     TypeWriteLock;      // 写map锁

    boost::shared_mutex                                 m_mutex;            // mutex
    std::map<UINT32, boost::shared_ptr<CNetSession>>    m_u32NodeID_ptrSession;
};

#endif
