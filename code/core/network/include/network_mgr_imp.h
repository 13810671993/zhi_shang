#ifndef __NETWORK_IMP_H__
#define __NETWORK_IMP_H__

class CNetworkMgrImp : public CNetworkMgr
{
public:
    static CNetworkMgrImp*  GetInstance();
    static VOID             DestroyInstance();

protected:
    CNetworkMgrImp();
    ~CNetworkMgrImp();

public:
    UINT32          RegistAdpt(CAdpt* pAdpt);

private:
    static VOID*    NetworkMsgThread(VOID* pParam);

    UINT32          SendMessage();

    UINT32          StartListen(IN const CHAR* pcIpAddr, IN UINT16 u16Port, CAdpt* pAdpt);
    UINT32          DoAccept();         // ������������
    VOID            RunIOServer();
    VOID            AcceptHandler(const boost::system::error_code& ec, std::shared_ptr<boost::asio::ip::tcp::socket> ptrSock);      // ���ӻص�
    VOID            MessageHandler(const boost::system::error_code& ec, std::shared_ptr<boost::asio::ip::tcp::socket> ptrSock, UINT32 u32NodeID, std::vector<CHAR> cMessageVec);     // ��Ϣ�ص�

private:
    static CNetworkMgrImp*  m_pNetworkMgrImp;
    CAdpt*                  m_pAdpt;
    CNetNodeIDLayer*        m_pNodeIDLayer;

    boost::asio::io_service         m_ioServer;
    boost::asio::ip::tcp::acceptor  m_acceptor;
    //acceptor.open(boost::asio::ip::tcp::v4(), ec);
};

#endif
