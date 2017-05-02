#include "subscriber_common.h"

CSubscriberImp::CSubscriberImp()
{
    boost::thread threadImp(boost::bind(PushMsg2SubscriberThread, (VOID*)this));
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
    UINT32  u32Ret = 0;

	//std::cout << pcMsg << std:: endl;

	printf(pcMsg);
    
    // ��װ���� д��sub������

    return u32Ret;
}

UINT32 CSubscriberImp::SubscribeMessage(IN UINT32 u32MsgType, IN CSubMsgHandler* pSubMsgHandler)
{
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

VOID* CSubscriberImp::PushMsg2SubscriberThread(VOID* pParm)
{
    while (1)
    {
        BOOST_SLEEP(1000);
    }

    return NULL;
}
