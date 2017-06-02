#ifndef __ADPT_H__
#define __ADPT_H__

// 衔接adpt <-> sub
// 消息传输 虚基类
class CMsgTransmit
{
public:
    CMsgTransmit()      {}
    ~CMsgTransmit()     {}

    virtual UINT32  PushMessage(IN UINT32 u32NodeID, IN UINT32 u32MsgType, IN CHAR* pcMsg, IN UINT32 u32MsgLen) = 0;
};


// 适配器 虚基类
class CAdpt
{
public:
    CAdpt()             {}
    virtual ~CAdpt()    {}

    virtual VOID    SetMsgTransimit(IN CMsgTransmit* pMsgTransmit) = 0;
    virtual UINT32  StartListen(IN UINT16 u16Port) = 0;
    virtual UINT32  RegistAdpt(IN CAdpt* pAdpt) = 0;
    virtual UINT32  PushMessage(IN UINT32 u32NodeID, IN UINT32 u32MsgType, IN UINT32 u32MsgLen, IN CHAR* pcMsg) = 0; 
    virtual VOID    PostMessage(IN UINT32 u32NodeID, IN UINT32 u32MsgType, IN UINT32 u32MsgLen, IN const CHAR* pcMsg) = 0;
};

#endif

