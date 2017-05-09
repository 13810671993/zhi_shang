#ifndef __SDK_PROTOCOL_H__
#define __SDK_PROTOCOL_H__

// req: >= 0x10000
typedef enum
{
    E_PTCL_MSG_LOGIN_REQ                                        = 0x10000,
}E_PTCL_SDK_TYPE;

// rsp: >= 0x20000
typedef enum
{
    E_PTCL_MSG_LOGIN_RSP                                        = 0x20000,
}E_PTCL_SVR_TYPE;

#endif // !__SDK_PROTOCOL_H__

