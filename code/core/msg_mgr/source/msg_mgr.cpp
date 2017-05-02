#include "msg_mgr_common.h"

CMsgMgr::CMsgMgr()
{

}

CMsgMgr::~CMsgMgr()
{

}

CMsgMgr* CMsgMgr::m_pMsgMgr = NULL;

CMsgMgr* CMsgMgr::GetInstance()
{
    return CMsgMgrImp::GetInstance();
}

VOID CMsgMgr::DestroyInstance()
{
    CMsgMgrImp::DestroyInstance();
}

