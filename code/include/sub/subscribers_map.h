#ifndef __SUBSCRIBERS_MAP_H__
#define __SUBSCRIBERS_MAP_H__

// 管理 订阅者集合
// 1. 添加删除订阅者
// 2. 为每个订阅者发送消息

class CSubscribersMap
{
public:
    CSubscribersMap();
    ~CSubscribersMap();

public:
    UINT32  AddMsgHandler(CSubMsgHandler* pSubMsgHandler);

private:
    std::vector<CSubMsgHandler*> m_subMsgHandlerVec;
};

#endif
