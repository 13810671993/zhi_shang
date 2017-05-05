#ifndef __ADPT_H__
#define __ADPT_H__

// 消息传输 虚基类
class CMsgTransmit
{
public:
    CMsgTransmit()      {}
    ~CMsgTransmit()     {}

    virtual UINT32  PushMessage(UINT32 u32NodeID, UINT32 u32MsgType, CHAR* pcMsg, UINT32 u32MsgLen) = 0;
};


// 适配器 虚基类
class CAdpt
{
public:
    CAdpt()             {}
    virtual ~CAdpt()    {}

    virtual VOID    SetMsgTransmitLayer(CMsgTransmit* pMsgTransmitLayer) = 0;
    virtual UINT32  StartListen(IN UINT16 u16Port) = 0;
    virtual UINT32  RegistAdpt(CAdpt* pAdpt) = 0;
    virtual UINT32  PushMessage(UINT32 u32NodeID, UINT32 u32MsgType, CHAR* pcMsg, UINT32 u32MsgLen) = 0;
    virtual VOID    PostMessage(IN UINT32 u32NodeID, IN const std::string& strMsg) = 0;
};

#endif

