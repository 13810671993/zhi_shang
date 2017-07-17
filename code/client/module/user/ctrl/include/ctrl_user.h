#ifndef CTRL_USER_H
#define CTRL_USER_H

#include "common/data_type.h"

class CCtrlUser
{
public:
    static CCtrlUser* 	GetInstance();
    static VOID			DestroyInstance();

protected:
    CCtrlUser();
    ~CCtrlUser();

public:
    VOID OnRegistUserRsp(const CHAR* pcMsg, UINT32 u32MsgLen);
    VOID OnModifyPasswdRsp(const CHAR* pcMsg, UINT32 u32MsgLen);

private:
    static CCtrlUser* m_pCtrlUser;
};

#endif // CTRL_USER_H

