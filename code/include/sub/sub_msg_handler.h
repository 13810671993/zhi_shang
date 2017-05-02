#ifndef __SUB_MSG_HANDLER_H__
#define __SUB_MSG_HANDLER_H__

// 消息处理者 实体逻辑类继承

class CSubMsgHandler
{
public:
    virtual UINT32  RecvMessageFromSub() = 0;
};

#endif
