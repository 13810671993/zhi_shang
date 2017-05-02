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
    VOID    SetMsgTransmitLayer(CMsgTransmit* pMsgTransmitLayer);
    UINT32  StartListen(IN const CHAR* pcIpAddr, IN UINT16 u16Port);
    UINT32  RegistAdpt(CAdpt* pAdpt);
    UINT32  RecvMessage(UINT32 u32NodeID, UINT32 u32MsgType, CHAR* pcMsg, UINT32 u32MsgLen);
    UINT32  SendMessage();

private:
    static CSvrAdpt*    m_pSvrAdpt;

    CMsgTransmit*      m_pMsgTransmitLayer;
};

#endif
