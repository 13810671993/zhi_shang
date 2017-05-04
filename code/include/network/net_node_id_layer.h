#ifndef __NET_NODE_ID_LAYER_H__
#define __NET_NODE_ID_LAYER_H__

// ά������ڵ�ID-�׽ӿ�ӳ����Դ
// ����ڵ�ID �������׽ӿڵ�ӳ��

class CNetNodeIDLayer
{
public:
    CNetNodeIDLayer();
    ~CNetNodeIDLayer();

public:
    UINT32  GenerateNetNodeID(IN std::shared_ptr<CNetSession> ptrSession, OUT UINT32& u32NodeID);
    UINT32  ReleaseNetNodeID(IN UINT32 u32NodeID);

private:
    std::map<UINT32, std::shared_ptr<CNetSession>> m_u32NodeID_ptrSession;
};

#endif
