#ifndef __NET_SESSION_H__
#define __NET_SESSION_H__

class CNetConnectionMgr;

class CNetSession
{
public:
    CNetSession(IN boost::asio::io_service& ioServer, IN CNetConnectionMgr* pNetConnectionMgr);
    ~CNetSession();

public:
    // ����Ự
    VOID            StartSession(IN UINT32 u32NodeID);
    VOID            MessageHandlerCB(IN const boost::system::error_code& ec, IN UINT32 u32MsgLen, IN UINT32 u32NodeID);     // ��Ϣ�ص�
    VOID            SendMessage(IN UINT32 u32MsgType, IN UINT32 u32MsgLen, IN const CHAR* pcMsg);

    inline boost::asio::ip::tcp::socket& GetSocket();

private:
    boost::asio::ip::tcp::socket m_socket;
    std::vector<CHAR> m_cNetMessageVec;
    CNetConnectionMgr* m_pNetConnectionMgr;
};

inline boost::asio::ip::tcp::socket& CNetSession::GetSocket()
{
    return m_socket;
}
#endif // !__NET_SESSION_MGR_H__

