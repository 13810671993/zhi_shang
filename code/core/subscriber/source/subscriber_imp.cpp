#include "subscriber_common.h"

boost::lockfree::queue<CSubInnerMsg*, boost::lockfree::fixed_sized<FALSE>> g_subInnerMsgQueue(0);

#ifdef _MEM_POOL_
CSubscriberImp::CSubscriberImp() : m_tMemPool(MEM_POOL_INITIALIZER)
{
    boost::thread threadImp(boost::bind(PushMsg2SubscriberThread, this));
    LogInfo("PushMsg2SubscriberThread start.");
    MemPoolInit_API();
    m_tMemPool = MemPoolCreate_API(NULL, NET_MESSAGE_MAX_SIZE);
}

CSubscriberImp::~CSubscriberImp()
{
    MemPoolDestroy_API(&m_tMemPool);
    MemPoolFinalize_API();
}
#else
CSubscriberImp::CSubscriberImp()
{
    boost::thread threadImp(boost::bind(PushMsg2SubscriberThread, this));
    LogInfo("PushMsg2SubscriberThread start.");
}

CSubscriberImp::~CSubscriberImp()
{

}
#endif

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

UINT32 CSubscriberImp::PushMessage(IN UINT32 u32NodeID, IN UINT32 u32MsgType, IN CHAR* pcMsg, IN UINT32 u32MsgLen)
{
#ifdef _MEM_POOL_
    CSubInnerMsg* pMsg = new CSubInnerMsg(u32NodeID, u32MsgType, pcMsg, u32MsgLen, &m_tMemPool);
#else
    CSubInnerMsg* pMsg = new CSubInnerMsg(u32NodeID, u32MsgType, pcMsg, u32MsgLen);
#endif

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

VOID CSubscriberImp::PushMsg2SubscriberThread(IN CSubscriberImp* pThis)
{
    CSubInnerMsg* pMsg = NULL;
    while (1)
    {
        // 1. �ȴ�sub��Ϣ�����л�ȡ��Ϣ
        // 2. ���ݶ��ļ�¼ ��ÿ��������������Ϣ
        if (g_subInnerMsgQueue.pop(pMsg) && pMsg != NULL)
        {
            // �Ӷ����л�ȡ����Ϣ ���ҵ�֪��MsgType
            TypeReadLock lock(pThis->m_mutex);

            // ����Ϣ���͸�������
            pThis->PubMessage(pMsg);
            delete pMsg;
            pMsg = NULL;
        }
        else
            BOOST_SLEEP(100);
    }
}

UINT32 CSubscriberImp::PubMessage(IN CSubInnerMsg* pMsg)
{
    auto it = m_msgType_SubscribersMap.find(pMsg->GetMsgType());
    if (it != m_msgType_SubscribersMap.end())
    {
        // �ж�����
        return it->second->PubMessage(pMsg);
    }
    else
    {
        // û���˶��ĸ���Ϣ 
        // fix: ������Ҫ
        m_msgType_SubscribersMap.begin()->second->PubMessage(pMsg);
        //LogWarning("PubMessage failed. No one subscribe this message. u32MsgType = %u", pMsg->GetMsgType());
        return COMERR_NOT_FOUND;
    }
}
