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
    VOID            DoRecvMessage(IN UINT32 u32NodeID);
    VOID            RecvMessageHeadCB(IN const boost::system::error_code& ec, IN UINT32 u32NodeID);
    VOID            RecvMessageBodyCB(IN const boost::system::error_code& ec, IN UINT32 u32MsgLen, IN UINT32 u32NodeID);
    VOID            MessageHandlerCB(IN const boost::system::error_code& ec, IN UINT32 u32MsgLen, IN UINT32 u32NodeID);     // 消息回调
    VOID            PostMessage(IN UINT32 u32MsgType, IN UINT32 u32MsgLen, IN const CHAR* pcMsg);
    std::string     RemoteAddr();
    UINT16          RemotePort();

    inline boost::asio::ip::tcp::socket& GetSocket();

private:
    boost::asio::ip::tcp::socket                m_socket;
    CHAR                                        m_acMessageBody[NET_MESSAGE_BODY_MAX_SIZE];
    CHAR                                        m_acMessageHead[NET_MESSAGE_HEAD_MAX_SIZE];
    CNetworkMgr*                                m_pNetworkMgr;

#ifdef _MEM_POOL_
    T_MEM_POOL m_tMemPool;
#else
#endif
};

inline boost::asio::ip::tcp::socket& CNetSession::GetSocket()
{
    return m_socket;
}
#endif // !__NET_SESSION_MGR_H__

