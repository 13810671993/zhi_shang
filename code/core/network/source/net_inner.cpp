#include "network_common.h"

CNetInnerMsg::CNetInnerMsg(UINT32 u32NodeID, UINT32 u32MsgType, CHAR* pcMsg, UINT32 u32MsgLen)
{
    m_u32NodeID = u32NodeID;
    m_u32MsgType = u32MsgType;
    //m_pMsg = pcMsg;
    m_pcMsg = new CHAR[u32MsgLen + 1];
    memset(m_pcMsg, 0, u32MsgLen + 1);
    memcpy(m_pcMsg, pcMsg, u32MsgLen);
    m_u32MsgLen = u32MsgLen;
}

CNetInnerMsg::~CNetInnerMsg()
{
    delete[] m_pcMsg;
}

UINT32 CNetInnerMsg::GetMsgType()
{
    return m_u32MsgType;
}

UINT32 CNetInnerMsg::GetMsgLen()
{
    return m_u32MsgLen;
}

UINT32 CNetInnerMsg::GetNodeID()
{
    return m_u32NodeID;
}

CHAR* CNetInnerMsg::GetMsgBuf()
{
    return m_pcMsg;
}
