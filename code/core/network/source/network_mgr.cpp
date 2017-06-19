#include "network_common.h"

CNetworkMgr::CNetworkMgr()
{

}

CNetworkMgr::~CNetworkMgr()
{

}

CNetworkMgr* CNetworkMgr::GetInstance()
{
    return CNetworkMgrImp::GetInstance();
}

VOID CNetworkMgr::DestroyInstance()
{
    CNetworkMgrImp::DestroyInstance();
}

