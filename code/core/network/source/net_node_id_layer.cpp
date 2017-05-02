#include "network_common.h"

CNetNodeIDLayer::CNetNodeIDLayer()
{

}

CNetNodeIDLayer::~CNetNodeIDLayer()
{

}

UINT32 CNetNodeIDLayer::GenerateNetNodeID(IN std::shared_ptr<boost::asio::ip::tcp::socket> ptrSocket, OUT UINT32& u32NodeID)
{
    UINT32  u32Ret = 0;
    static UINT32   u32TempCount = 1;
    
    auto it = m_u32NodeID_ptrSocketMap.begin();
    for (; it != m_u32NodeID_ptrSocketMap.end(); it++)
    {
        if (it->second == ptrSocket)
            break;
    }
    if (it != m_u32NodeID_ptrSocketMap.end())
    {
        // 已存在的NodeID 发生错误
        u32Ret = 1;
    }
    else
    {
        // 这是一个新的连接
        u32NodeID = u32TempCount;
        u32TempCount++;
        m_u32NodeID_ptrSocketMap.insert(std::make_pair(u32NodeID, ptrSocket));
        u32Ret = 0;
    }

    return u32Ret;
}
