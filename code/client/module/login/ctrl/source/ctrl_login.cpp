#include "login/login_common.h"


CCtrlLogin::CCtrlLogin()
{

}

CCtrlLogin::~CCtrlLogin()
{

}

CCtrlLogin* CCtrlLogin::m_pCtrlUser = NULL;
CCtrlLogin *CCtrlLogin::GetInstance()
{
    if (m_pCtrlUser == NULL)
        m_pCtrlUser = new CCtrlLogin();
    return m_pCtrlUser;
}

VOID CCtrlLogin::DestroyInstance()
{
    if (m_pCtrlUser != NULL)
    {
        delete m_pCtrlUser;
        m_pCtrlUser = NULL;
    }
}

VOID CCtrlLogin::OnLoginRsp(const CHAR *pcMsg, UINT32 u32MsgLen)
{
    T_APP_LOGIN_RSP* ptRsp = (T_APP_LOGIN_RSP*)pcMsg;
    qDebug() << "context: " << ptRsp->u64Context << "  result: " << ptRsp->u32Result;
}
