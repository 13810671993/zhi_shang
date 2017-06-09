#ifndef __SUB_MSG_HANDLER_H__
#define __SUB_MSG_HANDLER_H__

// 消息处理者 实体逻辑类继承

class CSubMsgHandler
{
public:
    virtual UINT32  RecvMessageFromSub(IN UINT32 u32NodeID, IN UINT32 u32MsgType, IN UINT32 u32MsgLen, IN CHAR* pcMsg) = 0;
};

#endif
