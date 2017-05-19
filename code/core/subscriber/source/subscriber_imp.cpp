#include "subscriber_common.h"

boost::lockfree::queue<CSubInnerMsgLayer*, boost::lockfree::fixed_sized<FALSE>> g_subInnerMsgQueue(0);

CSubscriberImp::CSubscriberImp()
{
    boost::thread threadImp(boost::bind(PushMsg2SubscriberThread, this));
    //threadImp.join();
}

CSubscriberImp::~CSubscriberImp()
{

}

CSubscriberImp* CSubscriberImp::m_pSubscriberImp = NULL;

CSubscriberImp* CSubscriberImp::GetInstance()
{
    if (m_pSubscriberImp == NULL)
        m_pSubscriberImp = new CSubscriberImp();
    return m_pSubscriberImp;
}

VOID CSubscriberImp::DestroyInstance()
{
    if (m_pSubscriberImp != NULL)
    {
        delete m_pSubscriberImp;
        m_pSubscriberImp = NULL;
    }
}

UINT32 CSubscriberImp::PushMessage(UINT32 u32NodeID, UINT32 u32MsgType, CHAR* pcMsg, UINT32 u32MsgLen)
{
    CSubInnerMsgLayer* pMsg = new CSubInnerMsgLayer(u32NodeID, u32MsgType, pcMsg, u32MsgLen);

    // д��sub���ض���
    g_subInnerMsgQueue.push(pMsg);
    
    return COMERR_OK;
}

UINT32 CSubscriberImp::SubscribeMessage(IN UINT32 u32MsgType, IN CSubMsgHandler* pSubMsgHandler)
{
    TypeWriteLock lock(m_mutex);
    UINT32  u32Ret = 0;
    // ��Ӷ��� ά��msgType-subscriberMap
    // 1. ����u32MsgType�Ƿ��Ѿ�������
    auto it = m_msgType_SubscribersMap.find(u32MsgType);
    if (it != m_msgType_SubscribersMap.end())
    {
        // u32MsgType�Ѿ�������
        u32Ret = it->second->AddMsgHandler(pSubMsgHandler);
    }
    else
    {
        // �µ�u32MsgType
        CSubscribersMap* pSubscribersMap = new CSubscribersMap();
        u32Ret = pSubscribersMap->AddMsgHandler(pSubMsgHandler);
        m_msgType_SubscribersMap.insert(std::make_pair(u32MsgType, pSubscribersMap));
    }

    return u32Ret;
}

VOID CSubscriberImp::PushMsg2SubscriberThread(CSubscriberImp* pThis)
{
    CSubInnerMsgLayer* pMsg = NULL;
    while (1)
    {
        // 1. �ȴ�sub��Ϣ�����л�ȡ��Ϣ
        // 2. ���ݶ��ļ�¼ ��ÿ��������������Ϣ
        if (g_subInnerMsgQueue.pop(pMsg) && pMsg != NULL)
        {
            // �Ӷ����л�ȡ����Ϣ ���ҵ�֪��MsgType
            TypeReadLock lock(pThis->m_mutex);
            auto it = pThis->m_msgType_SubscribersMap.find(pMsg->GetMsgType());
            if (it != pThis->m_msgType_SubscribersMap.end())
            {
                // �ж�����
                it->second->PubMessage(pMsg);
            }
            else
            {
                // û���˶��ĸ���Ϣ 
                // fix: ������Ҫ
                pThis->m_msgType_SubscribersMap.begin()->second->PubMessage(pMsg);
            }
            delete pMsg;
            pMsg = NULL;
        }
        else
            BOOST_SLEEP(100);
    }
}
