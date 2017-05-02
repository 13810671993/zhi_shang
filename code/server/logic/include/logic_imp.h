#ifndef __LOGIC_IMP_H__
#define __LOGIC_IMP_H__

// CLogic: �߼������
// CSubMsgHandler: ������Ϣ�Ĵ�����
// CLogicImp: �߼�ʵ���� ִ�з������߼� ͬʱҲҪ������Ϣ ����ȡ��Ϣ����

static boost::lockfree::queue<VOID*, boost::lockfree::fixed_sized<FALSE>>   msgQueue(0);

class CLogicImp : public CLogic, public CSubMsgHandler
{
public:
    static CLogicImp*   GetInstance();
    static VOID         DestroyInstance();

    UINT32  RecvMessageFromSub();               // ��ȡ��Ϣ CSubMsgHandler �ӿ�

    UINT32  Run();                              // �߼�������� CLogic �ӿ�
    UINT32  Stop();                             // �߼�ֹͣ��� CLogic �ӿ�

private:
    static VOID*    DealMessageThread(VOID* pParam);        // ��Ϣ�����߳�

    UINT32  RegistMessageCB();                  // ע�ᶩ����Ϣ
    UINT32  UnRegistMessageCB();                // ȡ��ע��

private:
    CLogicImp();
    ~CLogicImp();

private:
    static CLogicImp*   m_pLogicImp;

    CMsgMgr*        m_pMsgMgr;
    BOOL            m_bRun;
};

#endif
