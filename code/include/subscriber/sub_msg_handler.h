#ifndef __SUB_MSG_HANDLER_H__
#define __SUB_MSG_HANDLER_H__

// ��Ϣ������ ʵ���߼���̳�

class CSubMsgHandler
{
public:
    virtual UINT32  RecvMessageFromSub(IN UINT32 u32NodeID, IN UINT32 u32MsgType, IN CHAR* pcMsg, IN UINT32 u32MsgLen) = 0;
};

#endif
