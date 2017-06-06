#ifndef __MSG_MGR_IMP_H__
#define __MSG_MGR_IMP_H__

// 消息管理者
// 1. 添加一个适配器 记录在内部 后期可发展成记录适配器映射 <适配器类型, 适配器>
// 2. 把消息层添加给适配器 让消息能从适配器流到订阅器
// 3. 让适配器开启监听
// 4. 发送消息

class CSubMsgHandler;
class CSubscriber;
class CMsgTransmitImp;
class CAdpt;

class CMsgMgrImp : public CMsgMgr
{
public:
    static CMsgMgrImp*  GetInstance();
    static VOID         DestroyInstance();
private:
    CMsgMgrImp();
    ~CMsgMgrImp();

public:
    UINT32  AddAdpt(IN CAdpt* pAdpt);
    VOID    SetMsgTransmit2Adpt();
    UINT32  StartLisen(IN UINT16 u16Port);
    VOID    PostMessage(IN UINT32 u32NodeID, IN UINT32 u32MsgType, IN UINT32 u32MsgLen, IN const CHAR* pcMsg);
    UINT32  SubscribeMessage(IN UINT32 u32MsgType, IN CSubMsgHandler* pSubMsgHandler);

private:
    static CMsgMgrImp*  m_pMsgMgrImp;

    CSubscriber*        m_pSubscriber;
    CMsgTransmitImp*    m_pMsgLayer;
    CAdpt*              m_pAdpt;
};

#endif
