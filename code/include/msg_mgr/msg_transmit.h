#ifndef __MSG_TRANSMIT_H__
#define __MSG_TRANSMIT_H__

// �ν�adpt <-> sub
// ��Ϣ���� �����
class CMsgTransmit
{
public:
    CMsgTransmit()      {}
    ~CMsgTransmit()     {}

    virtual UINT32  PushMessage(IN UINT32 u32NodeID, IN UINT32 u32MsgType, IN CHAR* pcMsg, IN UINT32 u32MsgLen) = 0;
};


#endif
