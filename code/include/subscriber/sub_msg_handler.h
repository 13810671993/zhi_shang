#ifndef __SUB_MSG_HANDLER_H__
#define __SUB_MSG_HANDLER_H__

// ��Ϣ������ ʵ���߼���̳�

class CSubMsgHandler
{
public:
    virtual UINT32  RecvMessageFromSub(IN UINT32 u32NodeID, IN UINT32 u32MsgType, IN UINT32 u32MsgLen, IN CHAR* pcMsg) = 0;
};

#endif
