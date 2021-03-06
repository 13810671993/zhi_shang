#ifndef __LOGIC_IMP_H__
#define __LOGIC_IMP_H__

// CLogic: 逻辑抽象层
// CSubMsgHandler: 订阅消息的处理者
// CLogicImp: 逻辑实例类 执行服务器逻辑 同时也要订阅消息 来获取消息处理

class CMsgMgr;

class CLogicImp : public CLogic, public CSubMsgHandler
{
public:
    static CLogicImp*   GetInstance();
    static VOID         DestroyInstance();

    UINT32  RecvMessageFromSub(IN UINT32 u32NodeID, IN UINT32 u32MsgType, IN UINT32 u32MsgLen, IN CHAR* pcMsg); // 获取消息 CSubMsgHandler 接口

    UINT32  Run();                              // 逻辑触发入口 
    UINT32  Stop();                             // 逻辑停止入口 

    UINT32  Connected(IN UINT32 u32NodeID, IN const std::string& strIp, IN UINT16 u16Port);
    UINT32  Disconnected(IN UINT32 u32NodeID);

private:
    static VOID     DealMessageThread(IN CLogicImp* pThis, IN UINT32 u32ThreadNum);        // 消息处理线程

    UINT32  RegistMessageCB();                  // 注册订阅消息
    UINT32  UnRegistMessageCB();                // 取消注册

    UINT32  NotifyClient(IN UINT32 u32MsgType, IN const CHAR* pcMsg, IN UINT32 u32MsgLen);

    UINT32  OnDealMessage(IN UINT32 u32NodeID, IN UINT32 u32MsgType, IN UINT32 u32MsgLen, IN CHAR* pcMsg);
    UINT32  OnLoginReq(IN UINT32 u32NodeID, IN UINT32 u32MsgLen, IN CHAR* pcMsg);
    UINT32  OnRegistUserReq(IN UINT32 u32NodeID, IN UINT32 u32MsgLen, IN CHAR* pcMsg);
    UINT32  OnModifyPasswdReq(IN UINT32 u32NodeID, IN UINT32 u32MsgLen, IN CHAR* pcMsg);
    UINT32  OnGetOnlineUserReq(IN UINT32 u32NodeID, IN UINT32 u32MsgLen, IN CHAR* pcMsg);
    UINT32  OnSendMessageReq(IN UINT32 u32NodeID, IN UINT32 u32MsgLen, IN CHAR* pcMsg);

private:
    CLogicImp();
    ~CLogicImp();

private:
    static CLogicImp*   m_pLogicImp;

    CSessionMgr*    m_pSessionMgr;
    CMsgMgr*        m_pMsgMgr;
    BOOL            m_bRun;

#ifdef _MEM_POOL_
    T_MEM_POOL  m_tMemPool;
#else
#endif
};

#endif
