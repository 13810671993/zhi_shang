#include "subscriber_common.h"


CSubInnerMsgLayer::CSubInnerMsgLayer(UINT32 u32NodeID, UINT32 u32MsgType, CHAR* pcMsg, UINT32 u32MsgLen)
{
    m_u32NodeID = u32NodeID;
    m_u32MsgType = u32MsgType;
    //m_pMsg = pcMsg;
    m_pcMsg = new CHAR[u32MsgLen + 1];
    memset(m_pcMsg, 0, u32MsgLen + 1);
    memcpy(m_pcMsg, pcMsg, u32MsgLen);
    m_u32MsgLen = u32MsgLen;
}

CSubInnerMsgLayer::~CSubInnerMsgLayer()
{
    delete[] m_pcMsg;
}

UINT32 CSubInnerMsgLayer::GetMsgType()
{
    return m_u32MsgType;
}

UINT32 CSubInnerMsgLayer::GetMsgLen()
{
    return m_u32MsgLen;
}

UINT32 CSubInnerMsgLayer::GetNodeID()
{
    return m_u32NodeID;
}

CHAR* CSubInnerMsgLayer::GetMsgBuf()
{
    return m_pcMsg;
}
