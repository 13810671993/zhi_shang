#include "network_common.h"

boost::lockfree::queue<STNetMsg*, boost::lockfree::fixed_sized<FALSE>> g_netMsgQueue(0);
//boost::lockfree::queue<STNetMsg> g_netMsgQueue(1024);

CNetworkMgrImp::CNetworkMgrImp() : m_acceptor(m_ioServer), cMessageVec(100, 0)
{
    m_pNodeIDLayer = new CNetNodeIDLayer();
    boost::thread threadImp(boost::bind(&PushNetMsgThread, (VOID*)this));
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

VOID* CNetworkMgrImp::PushNetMsgThread(VOID* pParam)
{
    // 从网络消息队列中读取数据
    STNetMsg* pNetMsg = NULL;
    while (1)
    {
        if (g_netMsgQueue.pop(pNetMsg))
        {
            std::cout << pNetMsg->m_pMsg << std::endl;
            if (std::string(pNetMsg->m_pMsg) != "1")
            {
                std::cout << "error" << std::endl;
                getchar();
            }
            delete[] pNetMsg->m_pMsg;
            delete pNetMsg;
        }
        else
            BOOST_SLEEP(100);
    }
    return NULL;
}

UINT32 CNetworkMgrImp::StartListen(IN const CHAR* pcIpAddr, IN UINT16 u16Port, CAdpt* pAdpt)
{
    UINT32  u32Ret = 0;
    boost::asio::ip::tcp::endpoint  end_point(boost::asio::ip::address::from_string(pcIpAddr), u16Port);
	m_acceptor.open(boost::asio::ip::tcp::v4());
    m_acceptor.bind(end_point);
    m_acceptor.listen();
    u32Ret = DoAccept();

	m_pAdpt = pAdpt;

    // 启动接受connect
    RunIOServer();
    return u32Ret;
}

UINT32 CNetworkMgrImp::DoAccept()
{
    // 创建数据套接口资源
    std::shared_ptr<boost::asio::ip::tcp::socket> ptrSock(new boost::asio::ip::tcp::socket(m_ioServer));

    // 注册AcceptHandler
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
    
    // 有一个新的连接
    // 记录下来这个新的连接 为其分配节点ID
    UINT32  u32NodeID = 0;
    m_pNodeIDLayer->GenerateNetNodeID(ptrSock, u32NodeID);

    // 新来一个连接 创建缓冲区
	std::vector<CHAR>* pcMessageVec = new std::vector<CHAR>(1024, 0);

    //ptrSock->async_read_some(boost::asio::buffer(cMessageVec), boost::bind(&CNetworkMgrImp::MessageHandler, this, boost::asio::placeholders::error, ptrSock, u32NodeID));
    ptrSock->async_read_some(boost::asio::buffer(*pcMessageVec), boost::bind(&CNetworkMgrImp::MessageHandler, this, boost::asio::placeholders::error, ptrSock, u32NodeID, pcMessageVec));

    // 继续接受新的连接
    DoAccept();     // 没有继续调用 将不再接收其他连接
}

//VOID CNetworkMgrImp::MessageHandler(const boost::system::error_code& ec, std::shared_ptr<boost::asio::ip::tcp::socket> ptrSock, UINT32 u32NodeID)
VOID CNetworkMgrImp::MessageHandler(const boost::system::error_code& ec, std::shared_ptr<boost::asio::ip::tcp::socket> ptrSock, UINT32 u32NodeID, std::vector<CHAR>* pcMessageVec)
{
    if (ec)
        return;
    
    // 如果有数据 放在cMessageVec中
    // 把数据传递给adpt
	//if (cMessageVec.size() != 0)
	//	m_pAdpt->RecvMessage(u32NodeID, UINT32(cMessageVec.data()), cMessageVec.data() + sizeof(UINT32), cMessageVec.size() - sizeof(UINT32));
    
#if 0
    // 直接将数据写入队列?
    // 将数据封装到类中 然后写入队列
    STNetMsg* pNetMsg = NULL;
    pNetMsg = new STNetMsg();
    pNetMsg->m_u32NodeID = u32NodeID;
    pNetMsg->m_u32MsgType = UINT32(cMessageVec.data());
    pNetMsg->m_pMsg = new CHAR[cMessageVec.size() + 1];
    memset(pNetMsg->m_pMsg, 0, cMessageVec.size() + 1);
    memcpy(pNetMsg->m_pMsg, cMessageVec.data(), cMessageVec.size());
    pNetMsg->m_u32MsgLen = cMessageVec.size() - sizeof(UINT32);
    g_netMsgQueue.push(pNetMsg);
    //std::cout << cMessageVec.data() << std::endl;
    memset(cMessageVec.data(), 0, cMessageVec.size());
    //cMessageVec.clear();    // 这里有坑 http://blog.csdn.net/linfengmove/article/details/17448549
#endif
    //ptrSock->async_read_some(boost::asio::buffer(cMessageVec), boost::bind(&CNetworkMgrImp::MessageHandler, this, boost::asio::placeholders::error, ptrSock, u32NodeID, pcMessageVec));
	std::cout << pcMessageVec->data() << std::endl;
	memset(pcMessageVec->data(), 0, sizeof(pcMessageVec->size()));
    ptrSock->async_read_some(boost::asio::buffer(*pcMessageVec), boost::bind(&CNetworkMgrImp::MessageHandler, this, boost::asio::placeholders::error, ptrSock, u32NodeID, pcMessageVec));
	boost::system::error_code error_code;
	if (error_code == boost::asio::error::eof)
	{
		std::cout << "连接断开?" << std::endl;
		getchar();
	}
}

