#include "home/home_common.h"

CCtrlHome::CCtrlHome() : QObject()
{

}

CCtrlHome::~CCtrlHome()
{

}

CCtrlHome* CCtrlHome::m_pCtrlHome = NULL;
CCtrlHome *CCtrlHome::GetInstance()
{
    if (m_pCtrlHome == NULL)
        m_pCtrlHome = new CCtrlHome;
    return m_pCtrlHome;
}

VOID CCtrlHome::DestroyInstance()
{
    if (m_pCtrlHome != NULL)
    {
        delete m_pCtrlHome;
        m_pCtrlHome = NULL;
    }
}

VOID CCtrlHome::OnGetOnlineUserRsp(const CHAR *pcMsg, UINT32 u32MsgLen)
{
    T_APP_GET_ONLINE_USER_RSP*	ptRsp = (T_APP_GET_ONLINE_USER_RSP*)pcMsg;

    if (ptRsp->u32Result == 0)
    {
        // 收集在线用户列表
        QList<T_GNRL_ONLINE_USER> tUserList;
        for (auto i = 0; i < ptRsp->u32UserNum; ++i)
        {
            tUserList.push_back(ptRsp->atOnlineUser[i]);
        }
        emit SIGNAL_OnlineUser(tUserList);
    }
}

