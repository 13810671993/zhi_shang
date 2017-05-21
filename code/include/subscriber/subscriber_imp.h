#ifndef __SUBSCRIBER_IMP_H__
#define __SUBSCRIBER_IMP_H__

// ������
// 1. ����Ҫά��һ���߳� �����첽����adpt����������Ϣ Ȼ��ַ���������
// 2. ά��һ������ �첽����������Ϣ
// 3. ά��һ�� ����-�����߼��� ӳ��

class CSubscriberImp : public CSubscriber
{
public:
    static CSubscriberImp*  GetInstance();
    static VOID             DestroyInstance();

    UINT32          PushMessage(UINT32 u32NodeID, UINT32 u32MsgType, CHAR* pcMsg, UINT32 u32MsgLen);
    UINT32          SubscribeMessage(IN UINT32 u32MsgType, IN CSubMsgHandler* pSubMsgHandler);
private:
    CSubscriberImp();
    ~CSubscriberImp();

private:
    static  VOID    PushMsg2SubscriberThread(CSubscriberImp* pThis);

private:
    static CSubscriberImp*  m_pSubscriberImp;

    std::map<UINT32, CSubscribersMap*>      m_msgType_SubscribersMap;   // �����߼�ģ�������� ����Դ�Լ��̶�������� ��ʹ��� �����ǼӸ����� ����

    typedef boost::shared_lock<boost::shared_mutex>     TypeReadLock;
    typedef boost::unique_lock<boost::shared_mutex>     TypeWriteLock;
    boost::shared_mutex                                 m_mutex;
};

#endif