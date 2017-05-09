#ifndef __SVR_ADPT_H__
#define __SVR_ADPT_H__

// adpt��ֱ������������Ϣ�ײ�
// 1. �����˿ڼ���
// 2. ע��ص�
// 3. ��Ϣ����\����

class CSvrAdpt : public CAdpt
{
public:
    static CSvrAdpt*    GetInstance();
    static void         DestroyInstance();

private:
    CSvrAdpt();
    ~CSvrAdpt();
public:
    VOID    SetMsgTransimit(CMsgTransmit* pMsgTransmit);
    UINT32  StartListen(IN UINT16 u16Port);
    UINT32  RegistAdpt(CAdpt* pAdpt);
    UINT32  PushMessage(UINT32 u32NodeID, UINT32 u32MsgType, CHAR* pcMsg, UINT32 u32MsgLen);
    VOID    PostMessage(IN UINT32 u32NodeID, IN UINT32 u32MsgType, IN UINT32 u32MsgLen, IN const CHAR* pcMsg);

private:
    static CSvrAdpt*    m_pSvrAdpt;

    CMsgTransmit*      m_pMsgTransmit;
};

#endif
