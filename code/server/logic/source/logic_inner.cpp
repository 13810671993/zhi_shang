#include "logic_common.h"

#ifdef _SINGLETON_POOL_
typedef boost::singleton_pool<struct tag, NET_MESSAGE_BODY_MAX_SIZE> memPool;
#else
#endif

#ifdef _MEM_POOL_
CLogicInnerMsg::CLogicInnerMsg(IN UINT32 u32NodeID, IN UINT32 u32MsgType, IN UINT32 u32MsgLen, IN CHAR* pcMsg, IN T_MEM_POOL* ptMemPool) :
    m_u32NodeID(u32NodeID), m_u32MsgType(u32MsgType), m_u32MsgLen(u32MsgLen)
{
    m_pcMsg = (CHAR*)MemPoolAlloc_API(ptMemPool);
    if (m_pcMsg != NULL)
    {
        memset(m_pcMsg, 0, u32MsgLen + 1);
        memcpy(m_pcMsg, pcMsg, u32MsgLen);
    }
    else
        LogFatal("Alloc memery error. CLogicInnerMsg");
}

CLogicInnerMsg::~CLogicInnerMsg()
{
    if (m_pcMsg != NULL)
    {
        MemPoolFree_API(m_pcMsg);
        m_pcMsg = NULL;
    }
}
#else
CLogicInnerMsg::CLogicInnerMsg(IN UINT32 u32NodeID, IN UINT32 u32MsgType, IN UINT32 u32MsgLen, IN CHAR* pcMsg) :
      m_u32NodeID(u32NodeID)
    , m_u32MsgType(u32MsgType)
    , m_u32MsgLen(u32MsgLen)
    , m_pcMsg(NULL)
{
#ifdef _SINGLETON_POOL_
    m_pcMsg = (CHAR*)memPool::malloc();
    if (m_pcMsg != NULL)
    {
        memset(m_pcMsg, 0, u32MsgLen + 1);
        memcpy(m_pcMsg, pcMsg, u32MsgLen);
    }
#else
    m_pcMsg = new CHAR[u32MsgLen];
    if (m_pcMsg != NULL)
    {
        memset(m_pcMsg, 0, u32MsgLen);
        memcpy(m_pcMsg, pcMsg, u32MsgLen);
    }
    else
        LogFatal("New memery error. CLogicInnerMsg");
#endif
}

CLogicInnerMsg::~CLogicInnerMsg()
{
#ifdef _SINGLETON_POOL_
    if (m_pcMsg != NULL)
    {
        memPool::free(m_pcMsg);
        m_pcMsg = NULL;
    }
#else
    if (m_pcMsg != NULL)
    {
        delete[] m_pcMsg;
        m_pcMsg = NULL;
    }
#endif
}
#endif

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
