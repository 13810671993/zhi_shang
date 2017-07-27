#ifndef __APPLICATION_H__
#define __APPLICATION_H__

typedef enum
{
    E_APP_MSG_REGIST_USER_REQ       = 0xA001,       // ע���û�
    E_APP_MSG_LOGIN_REQ             = 0xA002,       // ��¼
    E_APP_MSG_MODIFY_PASSWD_REQ     = 0xA003,       // �޸�����
    E_APP_MSG_GET_ONLINE_USER_REQ   = 0xA004,       // ��ȡ�����û�
    E_APP_MSG_SEND_MESSAGE_REQ      = 0xA005,       // ������Ϣ
}E_APP_MSG_REQ_TYPE;


typedef enum
{
    E_APP_MSG_REGIST_USER_RSP       = 0xC001,       // ע���û�
    E_APP_MSG_LOGIN_RSP             = 0xC002,       // ��¼
    E_APP_MSG_MODIFY_PASSWD_RSP     = 0xC003,       // �޸�����
    E_APP_MSG_GET_ONLINE_USER_RSP   = 0xC004,       // ��ȡ�����û�
    E_APP_MSG_SEND_MESSAGE_RSP      = 0xC005,       // ������Ϣ
}E_APP_MSG_RSP_TYPE;



typedef enum 
{
    E_APP_MSG_TRANSMIT_MESSAGE_ACT      = 0xE001,       // ������Ϣ
}E_APP_MSG_ACTION_TYPE;



typedef enum 
{
    E_APP_MSG_UPDATE_ONLINE_USER_NTF    = 0xF001,
}E_APP_MSG_NTF_TYPE;

#endif // !__APPLICATION_H__
