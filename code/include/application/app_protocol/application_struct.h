#ifndef __APPLICATION_STRUCT_H__
#define __APPLICATION_STRUCT_H__

typedef struct
{
    UINT32 u32Result;
    UINT32 u32Test;
}T_APP_FIRST_TEST_REQ;

typedef struct
{
    UINT32 u32Result;
    UINT32 u32Test;
}T_APP_FIRST_TEST_RSP;


typedef struct
{
    UINT64  u64Context;
    CHAR    acUserName[APP_MAX_NAME_LEN];
    CHAR    acPasswd[APP_MAX_PASSWD_LEN];
    UINT32  u32Sex;
}T_APP_REGIST_USER_REQ;

typedef struct  
{
    UINT64  u64Context;
    UINT32  u32Result;
}T_APP_REGIST_USER_RSP;


typedef struct  
{
    UINT64  u64Context;
    CHAR    acUserName[APP_MAX_NAME_LEN];
    CHAR    acPasswd[APP_MAX_PASSWD_LEN];
}T_APP_LOGIN_REQ;

typedef struct  
{
    UINT64  u64Context;
    UINT32  u32Result;
}T_APP_LOGIN_RSP;


typedef struct  
{
    UINT64  u64Context;
    CHAR    acUserName[APP_MAX_NAME_LEN];
    CHAR    acOldPasswd[APP_MAX_PASSWD_LEN];
    CHAR    acNewPasswd[APP_MAX_PASSWD_LEN];
}T_APP_MODIFY_PASSWD_REQ;

typedef struct  
{
    UINT64  u64Context;
    UINT32  u32Result;
}T_APP_MODIFY_PASSWD_RSP;


typedef struct  
{
    UINT64  u64Context;
}T_APP_GET_ONLINE_USER_REQ;

typedef struct  
{
    UINT64  u64Context;
    UINT32  u32Result;
    UINT32  u32UserNum;
    T_GNRL_ONLINE_USER  atOnlineUser[APP_MAX_USER_NUM];
}T_APP_GET_ONLINE_USER_RSP;
#endif // !__APPLICATION_STRUCT_H__
