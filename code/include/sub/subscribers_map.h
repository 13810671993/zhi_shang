#ifndef __SUBSCRIBERS_MAP_H__
#define __SUBSCRIBERS_MAP_H__

// ���� �����߼���
// 1. ���ɾ��������
// 2. Ϊÿ�������߷�����Ϣ

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
