#include "network_common.h"

CNetworkMgrImp::CNetworkMgrImp() : m_acceptor(m_ioServer)
{
    m_pNodeIDLayer = new CNetNodeIDLayer();
}

CNetworkMgrImp::~CNetworkMgrImp()
{

}

UINT32 CNetworkMgrImp::RegistAdpt(CAdpt* pAdpt)
{
    m_pAdpt = pAdpt;
    return COMERR_OK;
}

CNetworkMgrImp* CNetworkMgrImp::m_pNetworkMgrImp = NULL;

CNetworkMgrImp* CNetworkMgrImp::GetInstance()
{
    if (m_pNetworkMgrImp == NULL)
        m_pNetworkMgrImp = new CNetworkMgrImp();
    return m_pNetworkMgrImp;
}

VOID CNetworkMgrImp::DestroyInstance()
{
    if (m_pNetworkMgrImp != NULL)
    {
        delete m_pNetworkMgrImp;
        m_pNetworkMgrImp = NULL;
    }
}

VOID* CNetworkMgrImp::NetworkMsgThread(VOID* pParam)
{
    // ����̱߳������е��׽ӿ� ���ĸ��׽ӿ�������?

    return NULL;
}

UINT32 CNetworkMgrImp::StartListen(IN const CHAR* pcIpAddr, IN UINT16 u16Port, CAdpt* pAdpt)
{
    UINT32  u32Ret = 0;
    boost::asio::ip::tcp::endpoint  end_point(boost::asio::ip::address_v4::from_string(pcIpAddr), u16Port);
	m_acceptor.open(boost::asio::ip::tcp::v4());
    m_acceptor.bind(end_point);
    m_acceptor.listen();

    u32Ret = DoAccept();

	m_pAdpt = pAdpt;

    // ��������connect
    RunIOServer();
    return u32Ret;
}

UINT32 CNetworkMgrImp::DoAccept()
{
    // ���������׽ӿ���Դ
    std::shared_ptr<boost::asio::ip::tcp::socket> ptrSock(new boost::asio::ip::tcp::socket(m_ioServer));

    // ע��AcceptHandler
    m_acceptor.async_accept(*ptrSock, boost::bind(&CNetworkMgrImp::AcceptHandler, this, boost::asio::placeholders::error, ptrSock));

    return COMERR_OK;
}

VOID CNetworkMgrImp::RunIOServer()
{
    m_ioServer.run();
}

VOID CNetworkMgrImp::AcceptHandler(const boost::system::error_code& ec, std::shared_ptr<boost::asio::ip::tcp::socket> ptrSock)
{
    if (ec)
        return;
    
    // ��һ���µ�����
    // ��¼��������µ����� Ϊ�����ڵ�ID
    UINT32  u32NodeID = 0;
    m_pNodeIDLayer->GenerateNetNodeID(ptrSock, u32NodeID);

    std::vector<CHAR>   cMessageVec;
    ptrSock->async_read_some(boost::asio::buffer(cMessageVec), boost::bind(&CNetworkMgrImp::MessageHandler, this, boost::asio::placeholders::error, ptrSock, u32NodeID, cMessageVec));

    // ���������µ�����
    DoAccept();
}

VOID CNetworkMgrImp::MessageHandler(const boost::system::error_code& ec, std::shared_ptr<boost::asio::ip::tcp::socket> ptrSock, UINT32 u32NodeID, std::vector<CHAR> cMessageVec)
{
    if (ec)
        return;
    
    // ��������� ����cMessageVec��
    // �����ݴ��ݸ�adpt
	if (cMessageVec.size() != 0)
		m_pAdpt->RecvMessage(u32NodeID, UINT32(cMessageVec.data()), cMessageVec.data() + sizeof(UINT32), cMessageVec.size() - sizeof(UINT32));
    
    // ������������
    //cMessageVec.clear();    // ��������п� http://blog.csdn.net/linfengmove/article/details/17448549
    ptrSock->async_read_some(boost::asio::buffer(cMessageVec), boost::bind(&CNetworkMgrImp::MessageHandler, this, boost::asio::placeholders::error, ptrSock, u32NodeID, cMessageVec));
}

