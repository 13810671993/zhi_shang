#include "network_common.h"

CNetNodeIDLayer::CNetNodeIDLayer()
{

}

CNetNodeIDLayer::~CNetNodeIDLayer()
{

}

UINT32 CNetNodeIDLayer::GenerateNetNodeID(IN boost::shared_ptr<CNetSession> ptrSession, OUT UINT32& u32NodeID)
{
    CNetNodeIDLayer::TypeWriteLock writeLock(m_mutex);
    static UINT32   u32TempCount = 1;
    
    auto it = m_u32NodeID_ptrSession.begin();
    for (; it != m_u32NodeID_ptrSession.end(); it++)
    {
        if (it->second == ptrSession)
            break;
    }
    if (it != m_u32NodeID_ptrSession.end())
    {
        // �Ѵ��ڵ�NodeID  ��������
        return COMERR_NODEID_EXIT;
    }
    else
    {
        // ����һ���µ�����
        u32NodeID = u32TempCount;
        u32TempCount++;
        m_u32NodeID_ptrSession.insert(std::make_pair(u32NodeID, ptrSession));
        return COMERR_OK;
    }
}

UINT32 CNetNodeIDLayer::ReleaseNetNodeID(IN UINT32 u32NodeID)
{
    CNetNodeIDLayer::TypeWriteLock writeLock(m_mutex);
    auto it = m_u32NodeID_ptrSession.find(u32NodeID);
    if (it != m_u32NodeID_ptrSession.end())
    {
        // �ҵ�����ڵ�ID�� �������session
        m_u32NodeID_ptrSession.erase(it);
        u32NodeID = 0;
    }
    // ���û�ҵ� u32NodeID��0;
    return u32NodeID;
}

UINT32 CNetNodeIDLayer::GetSession(IN UINT32 u32NodeID, OUT boost::shared_ptr<CNetSession>& ptrSession)
{
    CNetNodeIDLayer::TypeReadLock readLock(m_mutex);
    auto it = m_u32NodeID_ptrSession.find(u32NodeID);
    if (it != m_u32NodeID_ptrSession.end())
    {
        // �ҵ���
        ptrSession = it->second;
        return COMERR_OK;
    }
    else
    {
        // δ�ҵ�
        return COMERR_NOT_FOUND;
    }
}

BOOL CNetNodeIDLayer::IsConnect()
{
    if (m_u32NodeID_ptrSession.empty())
        return FALSE;
    else
        return TRUE;
}
