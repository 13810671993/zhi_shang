#ifndef __NET_MSG_H__
#define __NET_MSG_H__

#include "common/data_type.h"

class CNetMsg
{
public:
    CNetMsg();
    ~CNetMsg();
    
public:
    UINT32  GetMsgType();
    UINT32  GetMsgLen();
    CHAR*   GetMsgBuf();

private:
    CHAR*   m_pMsg;
    UINT32  m_u32MsgType;
    UINT32  m_u32MsgLen;
};

#endif
