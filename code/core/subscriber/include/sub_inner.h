#ifndef __SUB_MSG_LAYER_H__
#define __SUB_MSG_LAYER_H__

//œﬂ≥Ã–›√ﬂ£¨∫¡√Îº∂  
#define  BOOST_SLEEP(n)  boost::thread::sleep(boost::get_system_time()+boost::posix_time::millisec(n))

class CSubInnerMsgLayer
{
public:
    CSubInnerMsgLayer(UINT32 u32NodeID, UINT32 u32MsgType, CHAR* pcMsg, UINT32 u32MsgLen);
    ~CSubInnerMsgLayer();

public:
    UINT32  GetMsgType();
    UINT32  GetMsgLen();
    UINT32  GetNodeID();
    CHAR*   GetMsgBuf();

private:
    CHAR*   m_pcMsg;
    UINT32  m_u32MsgType;
    UINT32  m_u32MsgLen;
    UINT32  m_u32NodeID;
};

#endif