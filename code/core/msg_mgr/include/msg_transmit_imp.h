#ifndef __MSG_LAYER_H__
#define __MSG_LAYER_H__

// ��Ϣ��
// ����adpt����������Ϣ���͵�sub ��Ҫ����ͨadpt-sub
class CMsgTransmitImp : public CMsgTransmit
{
public:
    CMsgTransmitImp();
    ~CMsgTransmitImp();
public:
    VOID    SetSubscriber(IN CSubscriber* pSubcriber);
    UINT32  PushMessage(UINT32 u32NodeID, UINT32 u32MsgType, CHAR* pcMsg, UINT32 u32MsgLen);

private:
    CSubscriber*    m_pSubscriber;
};

#endif
