#include "subscriber_common.h"

#ifdef _MEM_POOL_
CSubInnerMsg::CSubInnerMsg(IN UINT32 u32NodeID, IN UINT32 u32MsgType, IN CHAR* pcMsg, IN UINT32 u32MsgLen, IN T_MEM_POOL* ptMemPool) :
    m_u32NodeID(u32NodeID), m_u32MsgType(u32MsgType), m_u32MsgLen(u32MsgLen)
{
    m_pcMsg = (CHAR*)MemPoolAlloc_API(ptMemPool);
    if (m_pcMsg != NULL)
    {
        memset(m_pcMsg, 0, u32MsgLen + 1);
        memcpy(m_pcMsg, pcMsg, u32MsgLen);
    }
}

CSubInnerMsg::~CSubInnerMsg()
{
    if (m_pcMsg != NULL)
    {
        MemPoolFree_API(m_pcMsg);
        m_pcMsg = NULL;
    }
}
#else
CSubInnerMsg::CSubInnerMsg(IN UINT32 u32NodeID, IN UINT32 u32MsgType, IN CHAR* pcMsg, IN UINT32 u32MsgLen) : 
    m_u32NodeID(u32NodeID), m_u32MsgType(u32MsgType), m_u32MsgLen(u32MsgLen)
{
    m_pcMsg = new CHAR[u32MsgLen + 1];
    if (m_pcMsg != NULL)
    {
        memset(m_pcMsg, 0, u32MsgLen + 1);
        memcpy(m_pcMsg, pcMsg, u32MsgLen);
    }
}

CSubInnerMsg::~CSubInnerMsg()
{
    if (m_pcMsg != NULL)
    {
        delete[] m_pcMsg;
        m_pcMsg = NULL;
    }
}
#endif
