#include "subscriber_common.h"

#ifdef _SINGLETON_POOL_
typedef boost::singleton_pool<struct tag, NET_MESSAGE_BODY_MAX_SIZE> memPool;
#else
#endif

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
#elif _POOL_
CSubInnerMsg::CSubInnerMsg(IN UINT32 u32NodeID, IN UINT32 u32MsgType, IN CHAR* pcMsg, IN UINT32 u32MsgLen, IN boost::pool<>& MemPool) :
    m_u32NodeID(u32NodeID)
    , m_u32MsgType(u32MsgType)
    , m_u32MsgLen(u32MsgLen)
    , m_pcMsg(NULL)
    , m_MemPool(MemPool)
{
    m_pcMsg = (CHAR*)m_MemPool.ordered_malloc();
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
        m_MemPool.ordered_free(m_pcMsg);
        m_pcMsg = NULL;
    }
}
#else
CSubInnerMsg::CSubInnerMsg(IN UINT32 u32NodeID, IN UINT32 u32MsgType, IN CHAR* pcMsg, IN UINT32 u32MsgLen) : 
      m_u32NodeID(u32NodeID)
    , m_u32MsgType(u32MsgType)
    , m_u32MsgLen(u32MsgLen)
    , m_pcMsg(NULL)
{
    if (pcMsg != NULL)
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
#endif
    }
}

CSubInnerMsg::~CSubInnerMsg()
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
