#include "subscriber_common.h"

CSubscribersMap::CSubscribersMap()
{

}

CSubscribersMap::~CSubscribersMap()
{

}

UINT32 CSubscribersMap::AddMsgHandler(CSubMsgHandler* pSubMsgHandler)
{
    UINT32  u32Ret = 0;
    // 维护消息处理者集合 m_SubMsgHandlerVec

    auto it = m_subMsgHandlerVec.begin();
    for (; it != m_subMsgHandlerVec.end(); it++)
    {
        // 找到跳出检索
        if (pSubMsgHandler == *it)
            break;
    }
    // 不存在 这是一个新的订阅者
    if (it == m_subMsgHandlerVec.end())
    {
        m_subMsgHandlerVec.push_back(pSubMsgHandler);
    }

    return u32Ret;
}
