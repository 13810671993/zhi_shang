#ifndef __NET_SESSION_H__
#define __NET_SESSION_H__

class CNetworkMgr;
class CNetSession
{
public:
    CNetSession(IN boost::asio::io_service& ioServer, IN CNetworkMgr* pNetworkMgr);
    ~CNetSession();

public:
    // 面向会话
    VOID            StartSession(IN UINT32 u32NodeID);
    VOID            MessageHandlerCB(IN const boost::system::error_code& ec, IN UINT32 u32MsgLen, IN UINT32 u32NodeID);     // 消息回调
    VOID            PostMessage(IN UINT32 u32MsgType, IN UINT32 u32MsgLen, IN const CHAR* pcMsg);

    inline boost::asio::ip::tcp::socket& GetSocket();

private:
    boost::asio::ip::tcp::socket    m_socket;
    std::vector<CHAR>               m_cNetMessageVec;
    CNetworkMgr*                    m_pNetworkMgr;

#ifdef _MEM_POOL_
    T_MEM_POOL m_tMemPool;
#else
#endif
#ifdef _POOL_
    boost::pool<> m_MemPool;
#endif
};

inline boost::asio::ip::tcp::socket& CNetSession::GetSocket()
{
    return m_socket;
}
#endif // !__NET_SESSION_MGR_H__

