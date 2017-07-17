#ifndef __COMMON_DEFINE_H__
#define __COMMON_DEFINE_H__

#ifndef NET_MESSAGE_BODY_MAX_SIZE
//#define NET_MESSAGE_MAX_SIZE (512)
#define NET_MESSAGE_BODY_MAX_SIZE       (1024)
#endif

#ifndef NET_MESSAGE_HEAD_MAX_SIZE
#define NET_MESSAGE_HEAD_MAX_SIZE       64
#endif

#ifndef NET_MESSAGE_HEAD_SIZE
#define NET_MESSAGE_HEAD_SIZE           sizeof(UINT32)
#endif

#ifndef NET_MESSAGE_TYPE_SIZE
#define NET_MESSAGE_TYPE_SIZE           sizeof(UINT32)
#endif

#ifndef APP_MAX_NAME_LEN
#define APP_MAX_NAME_LEN			    32
#endif
#ifndef APP_MAX_PASSWD_LEN
#define APP_MAX_PASSWD_LEN			    16
#endif
#ifndef APP_MAX_ID_LEN
#define APP_MAX_ID_LEN				    32
#endif


#endif