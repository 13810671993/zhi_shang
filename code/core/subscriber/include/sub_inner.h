#ifndef __SUB_MSG_LAYER_H__
#define __SUB_MSG_LAYER_H__

//œﬂ≥Ã–›√ﬂ£¨∫¡√Îº∂  
#define  BOOST_SLEEP(n)  boost::thread::sleep(boost::get_system_time()+boost::posix_time::millisec(n))

class CSubInnerMsg
{
public:
#ifdef _MEM_POOL_
    CSubInnerMsg(IN UINT32 u32NodeID, IN UINT32 u32MsgType, IN CHAR* pcMsg, IN UINT32 u32MsgLen, IN T_MEM_POOL* ptMemPool);
#elif _POOL_
    CSubInnerMsg(IN UINT32 u32NodeID, IN UINT32 u32MsgType, IN CHAR* pcMsg, IN UINT32 u32MsgLen, IN boost::pool<>& MemPool);
#else
    CSubInnerMsg(IN UINT32 u32NodeID, IN UINT32 u32MsgType, IN CHAR* pcMsg, IN UINT32 u32MsgLen);
#endif
    ~CSubInnerMsg();

public:
    inline UINT32  GetNodeID();
    inline UINT32  GetMsgType();
    inline UINT32  GetMsgLen();
    inline CHAR*   GetMsgBuf();

private:
    UINT32  m_u32NodeID;
    UINT32  m_u32MsgType;
    UINT32  m_u32MsgLen;
    CHAR*   m_pcMsg;
#ifdef _POOL_
    boost::pool<>& m_MemPool;
#endif
};

inline UINT32 CSubInnerMsg::GetNodeID()
{
    return m_u32NodeID;
}

inline UINT32 CSubInnerMsg::GetMsgType()
{
    return m_u32MsgType;
}

inline UINT32 CSubInnerMsg::GetMsgLen()
{
    return m_u32MsgLen;
}

inline CHAR* CSubInnerMsg::GetMsgBuf()
{
    return m_pcMsg;
}

#endif