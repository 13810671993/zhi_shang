#ifndef __SUB_MSG_LAYER_H__
#define __SUB_MSG_LAYER_H__

//œﬂ≥Ã–›√ﬂ£¨∫¡√Îº∂  
#define  BOOST_SLEEP(n)  boost::thread::sleep(boost::get_system_time()+boost::posix_time::millisec(n))

class CSubInnerMsgLayer
{
public:
    CSubInnerMsgLayer(IN UINT32 u32NodeID, IN UINT32 u32MsgType, IN CHAR* pcMsg, IN UINT32 u32MsgLen);
    ~CSubInnerMsgLayer();

public:
    inline UINT32  GetMsgType();
    inline UINT32  GetMsgLen();
    inline UINT32  GetNodeID();
    inline CHAR*   GetMsgBuf();

private:
    CHAR*   m_pcMsg;
    UINT32  m_u32MsgType;
    UINT32  m_u32MsgLen;
    UINT32  m_u32NodeID;
};

inline UINT32 CSubInnerMsgLayer::GetMsgType()
{
    return m_u32MsgType;
}

inline UINT32 CSubInnerMsgLayer::GetMsgLen()
{
    return m_u32MsgLen;
}

inline UINT32 CSubInnerMsgLayer::GetNodeID()
{
    return m_u32NodeID;
}

inline CHAR* CSubInnerMsgLayer::GetMsgBuf()
{
    return m_pcMsg;
}

#endif