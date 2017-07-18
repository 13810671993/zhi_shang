#ifndef CTRL_LOGIN_H
#define CTRL_LOGIN_H

#include "common/data_type.h"

class CCtrlLogin
{
public:
    static CCtrlLogin* 	GetInstance();
    static VOID			DestroyInstance();

protected:
    CCtrlLogin();
    ~CCtrlLogin();

public:
    VOID OnLoginRsp(const CHAR* pcMsg, UINT32 u32MsgLen);

private:
    static CCtrlLogin* m_pCtrlUser;
};

#endif // CTRL_LOGIN_H

