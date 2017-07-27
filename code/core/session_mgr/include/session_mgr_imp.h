#ifndef __SESSION_MGR_IMP_H__
#define __SESSION_MGR_IMP_H__

class CSessionMgr;
class CSessionMgrImp : public CSessionMgr
{
public:
    static CSessionMgrImp*  GetInstance();
    static VOID             DestroyInstance();

protected:
    CSessionMgrImp();
    ~CSessionMgrImp();

public:
    UINT32  SessionAdd(IN T_SESSION& tSession);
    UINT32  SessionDel(IN UINT32 u32NodeID);
    UINT32  SessionQueryByNodeID(IN UINT32 u32NodeID, OUT T_SESSION& tSession);
    UINT32  SessionQueryByObjID(IN const CHAR* pcObjID, OUT T_SESSION& tSession);
    UINT32  SessionGetNetNode(IN const T_SESSION& tSession, OUT UINT32& u32NodeID);
    UINT32  SessionGet(OUT std::vector<T_SESSION>& tSessionVec);

private:
    static CSessionMgrImp* m_pSessionMgrImp;

    typedef boost::shared_lock<boost::shared_mutex>     TypeReadLock;       // ¶ÁmapËø
    typedef boost::unique_lock<boost::shared_mutex>     TypeWriteLock;      // Ð´mapËø
    boost::shared_mutex                                 m_mutex;            // mutex

    std::map<UINT32, T_SESSION>   m_u32NodeID_tSessionMap;

};
#endif // !__SESSION_MGR_IMP_H__

