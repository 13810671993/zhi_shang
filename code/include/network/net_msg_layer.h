#ifndef __NET_MSG_LAYER_H__
#define __NET_MSG_LAYER_H__

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
