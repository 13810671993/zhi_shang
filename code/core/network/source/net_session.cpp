#include "network_common.h"

extern boost::lockfree::queue<CNetInnerMsg*, boost::lockfree::fixed_sized<FALSE>> g_netMsgQueue;

#ifdef _MEM_POOL_
CNetSession::CNetSession(IN boost::asio::io_service& ioServer, IN CNetworkMgr* pNetworkMgr) :
    m_socket(ioServer), m_cNetMessageVec(NET_MESSAGE_MAX_SIZE, 0), m_pNetworkMgr(pNetworkMgr), m_tMemPool(MEM_POOL_INITIALIZER)
{
    MemPoolInit_API();
    m_tMemPool = MemPoolCreate_API(NULL, NET_MESSAGE_MAX_SIZE);
}
#elif _POOL_
CNetSession::CNetSession(IN boost::asio::io_service& ioServer, IN CNetworkMgr* pNetworkMgr) :
    m_socket(ioServer), m_cNetMessageVec(NET_MESSAGE_MAX_SIZE, 0), m_pNetworkMgr(pNetworkMgr), m_MemPool(NET_MESSAGE_MAX_SIZE)
{
}

#else
CNetSession::CNetSession(IN boost::asio::io_service& ioServer, IN CNetworkMgr* pNetworkMgr) :
      m_socket(ioServer)
    , m_cNetMessageVec(NET_MESSAGE_MAX_SIZE, 0)
    , m_pNetworkMgr(pNetworkMgr)
{
}
#endif

CNetSession::~CNetSession()
{
    if (m_socket.is_open())
    {
        m_socket.close();
    }
#ifdef _MEM_POOL_
    // ȷ���ڴ������ǰ �����ڴ涼�黹���ڴ��
    BOOST_SLEEP(1 * 1000);
    MemPoolDestroy_API(&m_tMemPool);
    MemPoolFinalize_API();
#elif _POOL_
    //m_MemPool.purge_memory();
#else
#endif
}

VOID CNetSession::StartSession(IN UINT32 u32NodeID)
{
    // boost::asio �����������ķǳ��� ������Խ������ ���ݰ������ʱ�򶼻�ֶ�������� ���Բ��ÿ���Խ������
    m_socket.async_read_some(boost::asio::buffer(m_cNetMessageVec), boost::bind(&CNetSession::MessageHandlerCB, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred, u32NodeID));
}

#ifdef _WIN32_
LARGE_INTEGER  nFreq, t1, t2;
#else
#endif

VOID CNetSession::MessageHandlerCB(IN const boost::system::error_code& ec, IN UINT32 u32MsgLen, IN UINT32 u32NodeID)
{
    if (ec)
    {
        UINT32  u32Ret = 0;
        // �Ͽ����ӽ�������
        // ���ӶϿ� ���սڵ�ID��Դ
        do 
        {
            u32Ret = m_pNetworkMgr->Disconnect(u32NodeID);
            CHECK_ERR_BREAK(u32Ret == 0, u32Ret, "Disconnect Failed. u32Ret = 0x%x. u32NodeID = %u", u32Ret, u32NodeID);
        } while (0);

#ifdef _DEBUG_
        std::cout << ec.message() << std::endl;
#endif
        LogInfo("MessageHandlerCB error. error_code = %d, error: %s", ec.value(), ec.message().c_str());

        return; 
    }
    
    // ���ݰ����� ����
    if (u32MsgLen > NET_MESSAGE_MAX_SIZE)
    {
        LogFatal("Recv message error for out of bounds. u32MsgLen = %d", u32MsgLen);
        return;
    }

    // ���������
    // �����ݷ�װ������ Ȼ��д�����
    UINT32 u32MsgType = 0;
    memcpy(&u32MsgType, m_cNetMessageVec.data(), sizeof(UINT32));
    std::cout << "len: " << u32MsgLen << std::endl
        << "type: " << u32MsgType << std::endl;
    //std::cout << boost::posix_time::second_clock::local_time() << std::endl;;

#ifdef _WIN32_
    QueryPerformanceFrequency(&nFreq);
    QueryPerformanceCounter(&t1);
#else
#endif

#ifdef _MEM_POOL_
    CNetInnerMsg* pNetMsg = new CNetInnerMsg(u32NodeID, u32MsgType, u32MsgLen - sizeof(UINT32), m_cNetMessageVec.data() + sizeof(UINT32), &m_tMemPool);
#elif _POOL_
    CNetInnerMsg* pNetMsg = new CNetInnerMsg(u32NodeID, u32MsgType, u32MsgLen - sizeof(UINT32), m_cNetMessageVec.data() + sizeof(UINT32), m_MemPool);
#else
    CNetInnerMsg* pNetMsg = new CNetInnerMsg(u32NodeID, u32MsgType, u32MsgLen - sizeof(UINT32), m_cNetMessageVec.data() + sizeof(UINT32));
#endif
    g_netMsgQueue.push(pNetMsg);

    //m_cNetMessageVec.clear();
    // ��ջ����� ������������ ���ﲻ����clear �������ѭ��
    memset(m_cNetMessageVec.data(), 0, m_cNetMessageVec.size());
    m_socket.async_read_some(boost::asio::buffer(m_cNetMessageVec), boost::bind(&CNetSession::MessageHandlerCB, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred, u32NodeID));
}

VOID CNetSession::PostMessage(IN UINT32 u32MsgType, IN UINT32 u32MsgLen, IN const CHAR* pcMsg)
{
    if (!m_socket.is_open())
    {
        return;
    }

    boost::system::error_code error;
    // �������첽�������� �첽������������Ҫһ������ ѭ���������ݷ���
    //m_socket.async_write_some(boost::asio::buffer(strMsg), boost::bind(&CNetSession::PostMessage, this, strMsg));
    //m_socket.async_write_some(boost::asio::buffer(strMsg), boost::bind(&CNetSession::Test, this));
    //boost::asio::async_write(m_socket, boost::asio::buffer(strMsg), boost::bind(&CNetSession::Test, this));

    // fix: ����
    // ͬ����������
#if 0
    std::vector<CHAR> cMessageVec(u32MsgLen + sizeof(u32MsgType) + 1, 0);
    memcpy(cMessageVec.data(), &u32MsgType, sizeof(u32MsgType));
    memcpy(cMessageVec.data() + sizeof(u32MsgType), pcMsg, u32MsgLen);
#else
    std::vector<CHAR> cMessageVec(u32MsgLen, 0);
    memcpy(cMessageVec.data(), pcMsg, u32MsgLen);
#endif
    m_socket.write_some(boost::asio::buffer(cMessageVec), error);

    if (error)
    {
#ifdef _DEBUG_
        std::cout << boost::system::system_error(error).what() << std::endl;
#endif
        LogError("write_some error. error_code = %d, error: %s", error.value(), error.message().c_str());
        return;
    }
}

