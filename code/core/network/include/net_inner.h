#ifndef __NET_MSG_LAYER_H__
#define __NET_MSG_LAYER_H__

//œﬂ≥Ã–›√ﬂ£¨∫¡√Îº∂  
#define  BOOST_SLEEP(n)  boost::thread::sleep(boost::get_system_time()+boost::posix_time::millisec(n))

class CNetInnerMsg
{
public:
#ifdef _MEM_POOL_
    CNetInnerMsg(IN UINT32 u32NodeID, IN UINT32 u32MsgType, IN INT32 u32MsgLen, IN CHAR* pcMsg, IN T_MEM_POOL* ptMemPool);
#else
    CNetInnerMsg(IN UINT32 u32NodeID, IN UINT32 u32MsgType, IN INT32 u32MsgLen, IN const CHAR* pcMsg);
#endif
    ~CNetInnerMsg();
    
public:
    inline UINT32  GetNodeID();
    inline UINT32  GetMsgType();
    inline UINT32  GetMsgLen();
    inline CHAR*   GetMsgBuf();

private:
    UINT32          m_u32NodeID;
    UINT32          m_u32MsgType;
    UINT32          m_u32MsgLen;
    CHAR*           m_pcMsg;

};

inline UINT32 CNetInnerMsg::GetNodeID()
{
    return m_u32NodeID;
}

inline UINT32 CNetInnerMsg::GetMsgType()
{
    return m_u32MsgType;
}

inline UINT32 CNetInnerMsg::GetMsgLen()
{
    return m_u32MsgLen;
}

inline CHAR* CNetInnerMsg::GetMsgBuf()
{
    return m_pcMsg;
}

#endif
