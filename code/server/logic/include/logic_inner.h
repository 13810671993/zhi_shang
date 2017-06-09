#ifndef __LOGIC_INNER_TOOLS_H__
#define __LOGIC_INNER_TOOLS_H__

//线程休眠，毫秒级  
#define  BOOST_SLEEP(n)  boost::thread::sleep(boost::get_system_time()+boost::posix_time::millisec(n))

#define MAX_BUFFER_SIZE			(sizeof(void*))	//配置管理消息Buffer平均长度
#define MAX_BUFFER_NUM			2000			//配置管理消息Buf最大个数

class CLogicInnerMsg
{
public:
#ifdef _MEM_POOL_
    CLogicInnerMsg(IN UINT32 u32NodeID, IN UINT32 u32MsgType, IN UINT32 u32MsgLen, IN CHAR* pcMsg, IN T_MEM_POOL* ptMemPool);
#else
    CLogicInnerMsg(IN UINT32 u32NodeID, IN UINT32 u32MsgType, IN UINT32 u32MsgLen, IN CHAR* pcMsg);
#endif
    ~CLogicInnerMsg();
    
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
