#ifndef __SVR_ADPT_H__
#define __SVR_ADPT_H__

// adpt层直接面向网络消息底层
// 1. 开启端口监听
// 2. 注册回调
// 3. 消息接收\发送

class CSvrAdpt : public CAdpt
{
public:
    static CSvrAdpt*    GetInstance();
    static void         DestroyInstance();

private:
    CSvrAdpt();
    ~CSvrAdpt();
public:
    VOID    SetMsgTransmitLayer(CMsgTransmit* pMsgTransmitLayer);
    UINT32  StartListen(IN UINT16 u16Port);
    UINT32  RegistAdpt(CAdpt* pAdpt);
    UINT32  PushMessage(UINT32 u32NodeID, UINT32 u32MsgType, CHAR* pcMsg, UINT32 u32MsgLen);
    VOID    PostMessage(IN UINT32 u32NodeID, IN const std::string& strMsg);

private:
    static CSvrAdpt*    m_pSvrAdpt;

    CMsgTransmit*      m_pMsgTransmitLayer;
};

#endif
