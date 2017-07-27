#include "session_mgr_common.h"

CSessionMgr::CSessionMgr()
{

}

CSessionMgr::~CSessionMgr()
{

}

CSessionMgr* CSessionMgr::GetInstance()
{
    return CSessionMgrImp::GetInstance();
}

VOID CSessionMgr::DestroyInstance()
{
    CSessionMgrImp::DestroyInstance();
}

