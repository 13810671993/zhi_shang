#ifndef __NET_CONNECTION_MGR_H__
#define __NET_CONNECTION_MGR_H__

class CNetConnectionMgr
{
public:
    CNetConnectionMgr();
    ~CNetConnectionMgr();

    // 面向连接
    UINT32          StartListen(IN UINT16 u16Port);
    UINT32          DoAccept();         // 启动接受连接
    VOID            RunIOServer();
    VOID            AcceptHandlerCB(const boost::system::error_code& ec, boost::shared_ptr<CNetSession> ptrSession);      // 连接回调

    UINT32          Disconnect(UINT32 u32NodeID);

    BOOL            IsConnect();
    UINT32          Connect(IN const CHAR* pcIpAddr, IN UINT16 u16Port, OUT UINT32& u32NodeID);     // 目前只有同步
    UINT32          RecvMessage(OUT UINT32& u32NodeID, OUT UINT32& u32MsgType, OUT std::string& strMsg);

public:
    VOID            PostMessage(IN UINT32 u32NodeID, IN UINT32 u32MsgType, IN UINT32 u32MsgLen, IN const CHAR* pcMsg);
private:
    CNetNodeIDLayer*        m_pNodeIDLayer;

    boost::asio::io_service         m_ioServer;
    boost::asio::ip::tcp::acceptor  m_acceptor;
};

#endif // __NET_CONNECTION_MGR_H__

