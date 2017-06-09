#include "subscriber_common.h"

CSubscribersMap::CSubscribersMap()
{

}

CSubscribersMap::~CSubscribersMap()
{

}

UINT32 CSubscribersMap::AddMsgHandler(IN CSubMsgHandler* pSubMsgHandler)
{
    TypeWriteLock lock(m_mutex);
    UINT32  u32Ret = 0;
    // 维护消息处理者集合 m_SubMsgHandlerVec

    auto it = m_subMsgHandlerVec.begin();
    for (; it != m_subMsgHandlerVec.end(); ++it)
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

UINT32 CSubscribersMap::PubMessage(IN CSubInnerMsg* pMsg)
{
    TypeReadLock lock(m_mutex);
    for (auto it = m_subMsgHandlerVec.begin(); it != m_subMsgHandlerVec.end(); ++it)
    {
        (*it)->RecvMessageFromSub(pMsg->GetNodeID(), pMsg->GetMsgType(), pMsg->GetMsgLen(), pMsg->GetMsgBuf());
    }
    return COMERR_OK;
}
