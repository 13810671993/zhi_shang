#include "logic_common.h"

CLogicInnerMsg::CLogicInnerMsg(IN UINT32 u32NodeID, IN UINT32 u32MsgType, IN UINT32 u32MsgLen, IN CHAR* pcMsg)
{
    m_u32NodeID = u32NodeID;
    m_u32MsgType = u32MsgType;
    //m_pMsg = pcMsg;
    m_pcMsg = new CHAR[u32MsgLen + 1];
    memset(m_pcMsg, 0, u32MsgLen + 1);
    memcpy(m_pcMsg, pcMsg, u32MsgLen);
    m_u32MsgLen = u32MsgLen;
}

CLogicInnerMsg::~CLogicInnerMsg()
{
    delete[] m_pcMsg;
}

UINT32 CLogicInnerMsg::GetMsgType()
{
    return m_u32MsgType;
}

UINT32 CLogicInnerMsg::GetMsgLen()
{
    return m_u32MsgLen;
}

UINT32 CLogicInnerMsg::GetNodeID()
{
    return m_u32NodeID;
}

CHAR* CLogicInnerMsg::GetMsgBuf()
{
    return m_pcMsg;
}
