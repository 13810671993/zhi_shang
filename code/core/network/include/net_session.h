#ifndef __NET_SESSION_H__
#define __NET_SESSION_H__

class CNetConnectionMgr;
class CNetSession
{
public:
    CNetSession(boost::asio::io_service& ioServer, CNetConnectionMgr* pNetConnectionMgr);
    ~CNetSession();

public:
    static VOID     PushMessage2AdptThread(VOID* pParam);
    // 面向会话
    VOID            StartSession(IN UINT32 u32NodeID);
    VOID            MessageHandlerCB(IN const boost::system::error_code& ec, IN UINT32 u32NodeID);     // 消息回调
    VOID            PostMessage(IN const std::string& strMsg);
    VOID            Test();

    boost::asio::ip::tcp::socket& GetSocket();

private:
    boost::asio::ip::tcp::socket m_socket;
    std::vector<CHAR> m_cNetMessageVec;
    CNetConnectionMgr*  m_pNetConnectionMgr;
};

#endif // !__NET_SESSION_MGR_H__

