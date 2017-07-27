#ifndef __LOGIC_IMP_H__
#define __LOGIC_IMP_H__

// CLogic: �߼������
// CSubMsgHandler: ������Ϣ�Ĵ�����
// CLogicImp: �߼�ʵ���� ִ�з������߼� ͬʱҲҪ������Ϣ ����ȡ��Ϣ����

class CMsgMgr;

class CLogicImp : public CLogic, public CSubMsgHandler
{
public:
    static CLogicImp*   GetInstance();
    static VOID         DestroyInstance();

    UINT32  RecvMessageFromSub(IN UINT32 u32NodeID, IN UINT32 u32MsgType, IN UINT32 u32MsgLen, IN CHAR* pcMsg); // ��ȡ��Ϣ CSubMsgHandler �ӿ�

    UINT32  Run();                              // �߼�������� 
    UINT32  Stop();                             // �߼�ֹͣ��� 

    UINT32  Connected(IN UINT32 u32NodeID, IN const std::string& strIp, IN UINT16 u16Port);
    UINT32  Disconnected(IN UINT32 u32NodeID);

private:
    static VOID     DealMessageThread(IN CLogicImp* pThis, IN UINT32 u32ThreadNum);        // ��Ϣ�����߳�

    UINT32  RegistMessageCB();                  // ע�ᶩ����Ϣ
    UINT32  UnRegistMessageCB();                // ȡ��ע��

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
