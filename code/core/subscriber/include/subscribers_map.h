#ifndef __SUBSCRIBERS_MAP_H__
#define __SUBSCRIBERS_MAP_H__

// ���� �����߼���
// 1. ���ɾ��������
// 2. Ϊÿ�������߷�����Ϣ

class CSubMsgHandler;
class CSubInnerMsg;

class CSubscribersMap
{
public:
    CSubscribersMap();
    ~CSubscribersMap();

public:
    UINT32  AddMsgHandler(IN CSubMsgHandler* pSubMsgHandler);

    UINT32  PubMessage(IN CSubInnerMsg* pMsg);

private:
    std::vector<CSubMsgHandler*>                        m_subMsgHandlerVec;

    typedef boost::shared_lock<boost::shared_mutex>     TypeReadLock;
    typedef boost::unique_lock<boost::shared_mutex>     TypeWriteLock;
    boost::shared_mutex                                 m_mutex;
};

#endif
