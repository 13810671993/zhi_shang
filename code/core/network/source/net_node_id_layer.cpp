#include "network_common.h"

CNetNodeIDLayer::CNetNodeIDLayer() : m_u32Index(0)
{

}

CNetNodeIDLayer::~CNetNodeIDLayer()
{

}

UINT32 CNetNodeIDLayer::GenerateNetNodeID(IN boost::shared_ptr<CNetSession> ptrSession, OUT UINT32& u32NodeID)
{
    CNetNodeIDLayer::TypeWriteLock writeLock(m_mutex);
    
    auto it = m_u32NodeID_ptrSessionMap.begin();
    for (; it != m_u32NodeID_ptrSessionMap.end(); ++it)
    {
        if (it->second == ptrSession)
            break;
    }
    if (it != m_u32NodeID_ptrSessionMap.end())
    {
        // 已存在的NodeID  发生错误
        return COMERR_NODEID_EXIT;
    }
    else
    {
        // 循环使用m_u32Index 防止达到最大数
        if (!(++m_u32Index))
            ++m_u32Index;
        auto it = m_u32NodeID_ptrSessionMap.end();
        while (1)
        {
            it = m_u32NodeID_ptrSessionMap.find(m_u32Index);
            if (it == m_u32NodeID_ptrSessionMap.end())
                break;
            ++m_u32Index;
        }

        // 这是一个新的连接
        u32NodeID = m_u32Index;
        m_u32NodeID_ptrSessionMap.insert(std::make_pair(u32NodeID, ptrSession));
        return COMERR_OK;
    }
}

UINT32 CNetNodeIDLayer::ReleaseNetNodeID(IN UINT32 u32NodeID)
{
    CNetNodeIDLayer::TypeWriteLock writeLock(m_mutex);
    auto it = m_u32NodeID_ptrSessionMap.find(u32NodeID);
    if (it != m_u32NodeID_ptrSessionMap.end())
    {
        // 找到这个节点ID了 擦掉这个session
        m_u32NodeID_ptrSessionMap.erase(it);
        return COMERR_OK;
    }
    // 如果没找到 u32NodeID非0;
    return COMERR_NOT_FOUND;
}

UINT32 CNetNodeIDLayer::GetSession(IN UINT32 u32NodeID, OUT boost::shared_ptr<CNetSession>& ptrSession)
{
    CNetNodeIDLayer::TypeReadLock readLock(m_mutex);
    auto it = m_u32NodeID_ptrSessionMap.find(u32NodeID);
    if (it != m_u32NodeID_ptrSessionMap.end())
    {
        // 找到了
        ptrSession = it->second;
        return COMERR_OK;
    }
    else
    {
        // 未找到
        return COMERR_NOT_FOUND;
    }
}
