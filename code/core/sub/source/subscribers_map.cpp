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
    // ά����Ϣ�����߼��� m_SubMsgHandlerVec

    auto it = m_subMsgHandlerVec.begin();
    for (; it != m_subMsgHandlerVec.end(); it++)
    {
        // �ҵ���������
        if (pSubMsgHandler == *it)
            break;
    }
    // ������ ����һ���µĶ�����
    if (it == m_subMsgHandlerVec.end())
    {
        m_subMsgHandlerVec.push_back(pSubMsgHandler);
    }

    return u32Ret;
}
