#include "msg_mgr_common.h"

CMsgMgr::CMsgMgr()
{

}

CMsgMgr::~CMsgMgr()
{

}

CMsgMgr* CMsgMgr::GetInstance()
{
    return CMsgMgrImp::GetInstance();
}

VOID CMsgMgr::DestroyInstance()
{
    CMsgMgrImp::DestroyInstance();
}

