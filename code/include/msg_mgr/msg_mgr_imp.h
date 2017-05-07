#ifndef __MSG_MGR_IMP_H__
#define __MSG_MGR_IMP_H__

// 消息管理者
// 1. 添加一个适配器 记录在内部 后期可发展成记录适配器队列
// 2. 把消息层添加给适配器 让消息能从适配器流到订阅器
// 3. 让适配器开启监听
// 4. 发送消息

class CMsgMgrImp : public CMsgMgr
{
public:
    static CMsgMgrImp*  GetInstance();
    static VOID         DestroyInstance();
private:
    CMsgMgrImp();
    ~CMsgMgrImp();

public:
    VOID    AddAdpt(IN CAdpt* pAdpt);
    VOID    SetMsgTransmitLayer2Adpt();
    UINT32  StartLisen(IN UINT16 u16Port);
    VOID    PostMessage(IN UINT32 u32NodeID, IN const std::string& strMsg);
    UINT32  SubscribeMessage(UINT32 u32MsgType, CSubMsgHandler* pSubMsgHandler);

private:
    static CMsgMgrImp*  m_pMsgMgrImp;

    CSubscriber*        m_pSubscriber;
    CMsgTransmitImp*  m_pMsgLayer;
    CAdpt*              m_pAdpt;
};

#endif
