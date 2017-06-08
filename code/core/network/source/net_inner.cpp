#include "network_common.h"

boost::pool<> memeryPool(NET_MESSAGE_MAX_SIZE);

struct tag 
{
};
typedef boost::singleton_pool<tag, NET_MESSAGE_MAX_SIZE> memPool;


CNetInnerMsg::CNetInnerMsg(IN UINT32 u32NodeID, IN UINT32 u32MsgType, IN INT32 u32MsgLen, IN CHAR* pcMsg) :
                           m_u32NodeID(u32NodeID), m_u32MsgType(u32MsgType), m_u32MsgLen(u32MsgLen), m_pcMsg(NULL)//, m_MemeryPool(memeryPool)
{
#if 0
    m_pcMsg = new CHAR[u32MsgLen + 1];          // new
#else
    //m_pcMsg = (CHAR*)memPool::malloc();       // singleton_pool
    m_pcMsg = (CHAR*)memeryPool.malloc();   // pool
#endif
    memset(m_pcMsg, 0, u32MsgLen + 1);
    memcpy(m_pcMsg, pcMsg, u32MsgLen);
}

CNetInnerMsg::~CNetInnerMsg()
{
#if 0
    delete[] m_pcMsg;               // delete
#else
    //memPool::free(m_pcMsg);       // singleton_pool
    memeryPool.free(m_pcMsg);   // pool
#endif
}

