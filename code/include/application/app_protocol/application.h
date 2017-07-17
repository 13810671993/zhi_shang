#ifndef __APPLICATION_H__
#define __APPLICATION_H__

typedef enum
{
    E_APP_MSG_FIRST_TEST_REQ        = 0xA000,
    E_APP_MSG_REGIST_USER_REQ       = 0xA001,
    E_APP_MSG_LOGIN_REQ             = 0xA002,
    E_APP_MSG_MODIFY_PASSWD_REQ     = 0xA003,
}E_APP_MSG_REQ_TYPE;


typedef enum
{
    E_APP_MSG_FIRST_TEST_RSP        = 0xC000,
    E_APP_MSG_REGIST_USER_RSP       = 0xC001,
    E_APP_MSG_LOGIN_RSP             = 0xC002,
    E_APP_MSG_MODIFY_PASSWD_RSP     = 0xC003,
}E_APP_MSG_RSP_TYPE;

#endif // !__APPLICATION_H__
