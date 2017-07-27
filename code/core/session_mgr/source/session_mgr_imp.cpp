#include "session_mgr_common.h"

CSessionMgrImp::CSessionMgrImp()
{

}

CSessionMgrImp::~CSessionMgrImp()
{

}

CSessionMgrImp* CSessionMgrImp::m_pSessionMgrImp = NULL;
CSessionMgrImp* CSessionMgrImp::GetInstance()
{
    if (m_pSessionMgrImp == NULL)
        m_pSessionMgrImp = new CSessionMgrImp();
    return m_pSessionMgrImp;
}

VOID CSessionMgrImp::DestroyInstance()
{
    if (m_pSessionMgrImp != NULL)
    {
        delete m_pSessionMgrImp;
        m_pSessionMgrImp = NULL;
    }
}

UINT32 CSessionMgrImp::SessionAdd(IN T_SESSION& tSession)
{
    CSessionMgrImp::TypeWriteLock writeLock(m_mutex);
    auto it = m_u32NodeID_tSessionMap.find(tSession.u32NodeID);
    if (it != m_u32NodeID_tSessionMap.end())
    {
        // 找到了
        //LogInfo("AddSession. Session is exist, cover it. Old session");
        LogError("AddSession Failed. u32NodeID is repeated. u32NodeID = %d", tSession.u32NodeID);
        return COMERR_UNKOWN;
    }
    else
    {
        // 未找到
        m_u32NodeID_tSessionMap.insert(std::make_pair(tSession.u32NodeID, tSession));
        LogInfo("AddSession success. acObjID: %s, u32NodeID = %d", tSession.tSessionUOID.acObjID, tSession.u32NodeID);
        return COMERR_OK;
    }
}

UINT32 CSessionMgrImp::SessionDel(IN UINT32 u32NodeID)
{
    CSessionMgrImp::TypeWriteLock writeLock(m_mutex);
    auto it = m_u32NodeID_tSessionMap.find(u32NodeID);
    if (it != m_u32NodeID_tSessionMap.end())
    {
        // 找到了
        LogInfo("DelSession Success. acObjID: %s", it->second.tSessionUOID.acObjID);
        m_u32NodeID_tSessionMap.erase(it);

        return COMERR_OK;
    }
    else
    {
        LogError("DelSession Failed. u32NodeID = %d", u32NodeID);
        return COMERR_NOT_FOUND;
    }

}

UINT32 CSessionMgrImp::SessionQueryByNodeID(IN UINT32 u32NodeID, OUT T_SESSION& tSession)
{
    CSessionMgrImp::TypeReadLock readlock(m_mutex);
    auto it = m_u32NodeID_tSessionMap.find(u32NodeID);
    if (it != m_u32NodeID_tSessionMap.end())
    {
        // 找到了
        //memcpy(&tSession, &(it->second), sizeof(tSession));
        tSession = it->second;
        LogInfo("FindSessionByNodeID Success. acObjID: %s", tSession.tSessionUOID.acObjID);

        return COMERR_OK;
    }
    else
    {
        // 未找到
        LogError("FindSessionByNodeID Failed. u32NodeID = %d", u32NodeID);
        return COMERR_NOT_FOUND;
    }
}

UINT32 CSessionMgrImp::SessionQueryByObjID(IN const CHAR* pcObjID, OUT T_SESSION& tSession)
{
    CSessionMgrImp::TypeReadLock readLock(m_mutex);
    for (auto it = m_u32NodeID_tSessionMap.begin(); it != m_u32NodeID_tSessionMap.end(); ++it)
    {
        if (strcmp(it->second.tSessionUOID.acObjID, pcObjID) == 0)
        {
            // 找到了
            tSession = it->second;
            return COMERR_OK;
        }
    }
    return COMERR_NOT_FOUND;
}

UINT32 CSessionMgrImp::SessionGetNetNode(IN const T_SESSION& tSession, OUT UINT32& u32NodeID)
{
    CSessionMgrImp::TypeReadLock readLock(m_mutex);
    auto it = m_u32NodeID_tSessionMap.find(tSession.u32NodeID);
    if (it != m_u32NodeID_tSessionMap.end())
    {
        // 找到了
        u32NodeID = it->first;
        return COMERR_OK;
    }
    else
    {
        // 未找到
        return COMERR_NOT_FOUND;
    }
}

UINT32 CSessionMgrImp::SessionGet(OUT std::vector<T_SESSION>& tSessionVec)
{
    tSessionVec.clear();
    CSessionMgrImp::TypeReadLock readLock(m_mutex);
    for (auto it = m_u32NodeID_tSessionMap.begin(); it != m_u32NodeID_tSessionMap.end(); ++it)
    {
        tSessionVec.push_back(it->second);
    }

    return COMERR_OK;
}

