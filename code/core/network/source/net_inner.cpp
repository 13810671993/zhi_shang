#include "network_common.h"

CNetInnerMsg::CNetInnerMsg(IN UINT32 u32NodeID, IN UINT32 u32MsgType, IN INT32 u32MsgLen, IN CHAR* pcMsg) : 
                           m_u32NodeID(0), m_u32MsgType(0), m_u32MsgLen(0), m_pcMsg(NULL)
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

