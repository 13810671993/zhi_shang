#ifndef __NET_SESSION_H__
#define __NET_SESSION_H__

class CNetConnectionMgr;
class CNetSession
{
public:
    CNetSession(boost::asio::io_service& ioServer, CNetConnectionMgr* pNetConnectionMgr);
    ~CNetSession();

public:
    // 面向会话
    VOID            StartSession(IN UINT32 u32NodeID);
    VOID            MessageHandlerCB(IN const boost::system::error_code& ec, IN UINT32 u32NodeID);     // 消息回调
    VOID            SendMessage(IN UINT32 u32MsgType, IN UINT32 u32MsgLen, IN const CHAR* pcMsg);

    UINT32          Connect(IN const CHAR* pcIpAddr, IN UINT16 u16Port);
    UINT32          RecvMessage(OUT UINT32& u32MsgType, OUT std::string& strMsg);

    boost::asio::ip::tcp::socket& GetSocket();

private:
    boost::asio::ip::tcp::socket m_socket;
    std::vector<CHAR> m_cNetMessageVec;
    CNetConnectionMgr* m_pNetConnectionMgr;
};

#endif // !__NET_SESSION_MGR_H__

