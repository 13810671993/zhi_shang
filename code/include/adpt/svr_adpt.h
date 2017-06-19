#ifndef __SVR_ADPT_H__
#define __SVR_ADPT_H__

// adpt层直接面向网络消息底层
// 1. 开启端口监听
// 2. 注册回调
// 3. 消息接收\发送

class CSubscriber;

class CSvrAdpt : public CAdpt
{
public:
    static CSvrAdpt*    GetInstance();
    static VOID         DestroyInstance();

private:
    CSvrAdpt();
    ~CSvrAdpt();
public:
    VOID    SetSubscriber(IN CSubscriber* pSubscriber);
    UINT32  StartListen(IN UINT16 u16Port);
    UINT32  RegistAdpt(IN CAdpt* pAdpt);
    UINT32  PushMessage(IN UINT32 u32NodeID, IN UINT32 u32MsgType, IN UINT32 u32MsgLen, IN CHAR* pcMsg);
    VOID    PostMessage(IN UINT32 u32NodeID, IN UINT32 u32MsgType, IN UINT32 u32MsgLen, IN const CHAR* pcMsg);

private:
    static CSvrAdpt*    m_pSvrAdpt;

    CSubscriber*        m_pSubscriber;
};

#endif
