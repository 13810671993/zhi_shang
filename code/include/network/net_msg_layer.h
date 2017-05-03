#ifndef __NET_MSG_LAYER_H__
#define __NET_MSG_LAYER_H__

typedef struct __NET_MSG__
{
    __NET_MSG__() : m_pMsg(NULL), m_u32MsgType(0), m_u32MsgLen(0), m_u32NodeID(0)
    {
    }
    
    CHAR*   m_pMsg;
    UINT32  m_u32MsgType;
    UINT32  m_u32MsgLen;
    UINT32  m_u32NodeID;
}STNetMsg;

class CNetMsgLayer
{
public:
    CNetMsgLayer(UINT32 u32NodeID, UINT32 u32MsgType, CHAR* pcMsg, UINT32 u32MsgLen);
    ~CNetMsgLayer();
    
public:
    UINT32  GetMsgType();
    UINT32  GetMsgLen();
    UINT32  GetNodeID();
    CHAR*   GetMsgBuf();

private:
    CHAR*   m_pMsg;
    UINT32  m_u32MsgType;
    UINT32  m_u32MsgLen;
    UINT32  m_u32NodeID;
};

#endif
