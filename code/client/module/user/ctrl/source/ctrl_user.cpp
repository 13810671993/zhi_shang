#include "user/user_operation_common.h"

CCtrlUser::CCtrlUser()
{

}

CCtrlUser::~CCtrlUser()
{


}

CCtrlUser* CCtrlUser::m_pCtrlUser = NULL;

CCtrlUser *CCtrlUser::GetInstance()
{
    if (m_pCtrlUser == NULL)
        m_pCtrlUser = new CCtrlUser();
    return m_pCtrlUser;
}

VOID CCtrlUser::DestroyInstance()
{
    if (m_pCtrlUser != NULL)
    {
        delete m_pCtrlUser;
        m_pCtrlUser = NULL;
    }
}

VOID CCtrlUser::OnRegistUserRsp(const CHAR *pcMsg, UINT32 u32MsgLen)
{
    T_APP_REGIST_USER_RSP* ptRsp = (T_APP_REGIST_USER_RSP*)pcMsg;
    qDebug() << "context: " << ptRsp->u64Context << "  result: " << ptRsp->u32Result;
}

VOID CCtrlUser::OnModifyPasswdRsp(const CHAR *pcMsg, UINT32 u32MsgLen)
{
    T_APP_MODIFY_PASSWD_RSP* ptRsp = (T_APP_MODIFY_PASSWD_RSP*)pcMsg;
    qDebug() << "context: " << ptRsp->u64Context << "  result: " << ptRsp->u32Result;
}
