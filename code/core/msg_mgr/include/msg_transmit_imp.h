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
    UINT32  PushMessage(IN UINT32 u32NodeID, IN UINT32 u32MsgType, IN CHAR* pcMsg, IN UINT32 u32MsgLen);

private:
    CSubscriber*    m_pSubscriber;
};

#endif
