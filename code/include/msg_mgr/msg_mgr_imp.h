#ifndef __MSG_MGR_IMP_H__
#define __MSG_MGR_IMP_H__

// ��Ϣ������
// 1. ���һ�������� ��¼���ڲ� ���ڿɷ�չ�ɼ�¼����������
// 2. ����Ϣ����Ӹ������� ����Ϣ�ܴ�����������������
// 3. ����������������
// 4. ������Ϣ

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
