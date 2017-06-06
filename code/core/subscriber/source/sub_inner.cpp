#include "subscriber_common.h"


CSubInnerMsgLayer::CSubInnerMsgLayer(IN UINT32 u32NodeID, IN UINT32 u32MsgType, IN CHAR* pcMsg, IN UINT32 u32MsgLen)
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
