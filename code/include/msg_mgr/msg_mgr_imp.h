#ifndef __MSG_MGR_IMP_H__
#define __MSG_MGR_IMP_H__

// ��Ϣ������
// 1. ���һ�������� ��¼���ڲ� ���ڿɷ�չ�ɼ�¼������ӳ�� <����������, ������>
// 2. ����Ϣ����Ӹ������� ����Ϣ�ܴ�����������������
// 3. ����������������
// 4. ������Ϣ

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
