#ifndef __NETWORK_IMP_H__
#define __NETWORK_IMP_H__

class CAdpt;

class CNetworkMgrImp : public CNetworkMgr
{
public:
    static CNetworkMgrImp*  GetInstance();
    static VOID             DestroyInstance();

protected:
    CNetworkMgrImp();
    ~CNetworkMgrImp();

public:
    VOID            PostMessage(IN UINT32 u32NodeID, IN UINT32 u32MsgType, IN UINT32 u32MsgLen, IN const CHAR* pcMsg);
    UINT32          RegistAdpt(IN CAdpt* pAdpt);
    UINT32          GetRemoteNodeInfo(IN UINT32 u32NodeID, OUT std::string& strIp, OUT UINT16& u16Port);

private:
    // 面向连接
    UINT32          StartListen(IN UINT16 u16Port);
    UINT32          DoAccept();         // 启动接受连接
    VOID            AcceptHandlerCB(IN const boost::system::error_code& ec, IN boost::shared_ptr<CNetSession>& ptrSession);      // 连接回调
    UINT32          Connected(IN boost::shared_ptr<CNetSession>& ptrSession, OUT UINT32& u32NodeID);
    UINT32          Disconnected(IN UINT32 u32NodeID);

    static VOID     ListenThread(IN CNetworkMgrImp* pThis, IN UINT16 u16Port);
    static VOID     PushMessage2AdptThread(IN CNetworkMgrImp* pThis);
private:
    static CNetworkMgrImp*          m_pNetworkMgrImp;
    CAdpt*                          m_pAdpt;
    CNetNodeIDLayer*                m_pNodeIDLayer;

    boost::asio::io_service         m_ioServer;
    boost::asio::ip::tcp::acceptor  m_acceptor;
};

#endif
