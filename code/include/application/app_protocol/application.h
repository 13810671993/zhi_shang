#ifndef __APPLICATION_H__
#define __APPLICATION_H__

typedef enum
{
    E_APP_MSG_REGIST_USER_REQ       = 0xA001,       // 注册用户
    E_APP_MSG_LOGIN_REQ             = 0xA002,       // 登录
    E_APP_MSG_MODIFY_PASSWD_REQ     = 0xA003,       // 修改密码
    E_APP_MSG_GET_ONLINE_USER_REQ   = 0xA004,       // 获取在线用户
    E_APP_MSG_SEND_MESSAGE_REQ      = 0xA005,       // 发送消息
}E_APP_MSG_REQ_TYPE;


typedef enum
{
    E_APP_MSG_REGIST_USER_RSP       = 0xC001,       // 注册用户
    E_APP_MSG_LOGIN_RSP             = 0xC002,       // 登录
    E_APP_MSG_MODIFY_PASSWD_RSP     = 0xC003,       // 修改密码
    E_APP_MSG_GET_ONLINE_USER_RSP   = 0xC004,       // 获取在线用户
    E_APP_MSG_SEND_MESSAGE_RSP      = 0xC005,       // 发送消息
}E_APP_MSG_RSP_TYPE;



typedef enum 
{
    E_APP_MSG_TRANSMIT_MESSAGE_ACT      = 0xE001,       // 发送消息
}E_APP_MSG_ACTION_TYPE;



typedef enum 
{
    E_APP_MSG_UPDATE_ONLINE_USER_NTF    = 0xF001,
}E_APP_MSG_NTF_TYPE;

#endif // !__APPLICATION_H__
