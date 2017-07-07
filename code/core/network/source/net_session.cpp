#include "network_common.h"

#ifdef _LOCK_FREE_QUEUE_
extern boost::lockfree::queue<CNetInnerMsg*, boost::lockfree::fixed_sized<FALSE>> g_netMsgQueue;
#else
extern boost::lockfree::spsc_queue< CNetInnerMsg*, boost::lockfree::capacity<NET_MESSAGE_BODY_MAX_SIZE> > g_netMsgSpscQueue;
#endif

#ifdef _MEM_POOL_
CNetSession::CNetSession(IN boost::asio::io_service& ioServer, IN CNetworkMgr* pNetworkMgr) :
    m_socket(ioServer), m_acMessageBody(NET_MESSAGE_BODY_MAX_SIZE, 0), m_pNetworkMgr(pNetworkMgr), m_tMemPool(MEM_POOL_INITIALIZER)
{
    MemPoolInit_API();
    m_tMemPool = MemPoolCreate_API(NULL, NET_MESSAGE_BODY_MAX_SIZE);
}
#else
CNetSession::CNetSession(IN boost::asio::io_service& ioServer, IN CNetworkMgr* pNetworkMgr) :
      m_socket(ioServer)
    , m_pNetworkMgr(pNetworkMgr)
{
}
#endif

CNetSession::~CNetSession()
{
    if (m_socket.is_open())
    {
        m_socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
        m_socket.close();
    }
#ifdef _MEM_POOL_
    // 确保内存池销毁前 所有内存都归还给内存池
    BOOST_SLEEP(1 * 1);
    MemPoolDestroy_API(&m_tMemPool);
    MemPoolFinalize_API();
#else
#endif
}

VOID CNetSession::DoRecvMessage(IN UINT32 u32NodeID)
{
    // 启动这个连接会话 开始异步接收数据
    // 先接受固定长度的包头 成功读出包体长度后固定接收定长包体
    // 每次都是精准接收 所以不用考虑粘包
    if (m_socket.is_open())
    {
#ifdef _REQ_
        // 精准接收8个字节的包头
        boost::asio::async_read(m_socket, boost::asio::buffer(m_acMessageHead), boost::asio::transfer_exactly(NET_MESSAGE_HEAD_SIZE), boost::bind(&CNetSession::RecvMessageHeadCB, this, boost::asio::placeholders::error, u32NodeID));
#else
        m_socket.async_read_some(boost::asio::buffer(m_acMessageBody), boost::bind(&CNetSession::MessageHandlerCB, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred, u32NodeID));
#endif
    }
}

VOID CNetSession::RecvMessageHeadCB(IN const boost::system::error_code& ec, IN UINT32 u32NodeID)
{
    UINT32  u32Ret = 0;
    if (!ec)
    {
        // 读取包头成功
        // 获取包头数据 ->包体的长度
        UINT32 u32MsgBodyLen = 0;
        memcpy(&u32MsgBodyLen, m_acMessageHead, sizeof(u32MsgBodyLen));
        if (u32MsgBodyLen > NET_MESSAGE_BODY_MAX_SIZE || u32MsgBodyLen == 0)
        {
            LogError("Message body length error, message is illegal, disconnect. u32MsgBodyLen = %d", u32MsgBodyLen);
            // 连接断开 回收节点ID资源
            do
            {
                u32Ret = m_pNetworkMgr->Disconnect(u32NodeID);
                CHECK_ERR_BREAK(u32Ret == 0, u32Ret, "Disconnect Failed. u32Ret = 0x%x. u32NodeID = %u", u32Ret, u32NodeID);
            } while (0);
        }
        else
        {
            boost::asio::async_read(m_socket, boost::asio::buffer(m_acMessageBody), boost::asio::transfer_exactly(u32MsgBodyLen), boost::bind(&CNetSession::RecvMessageBodyCB, this, boost::asio::placeholders::error, u32MsgBodyLen, u32NodeID));
        }

    }
    else
    {
        // 其他原因导致读取失败 连接可能断开
        // 连接断开 回收节点ID资源
        do 
        {
            u32Ret = m_pNetworkMgr->Disconnect(u32NodeID);
            CHECK_ERR_BREAK(u32Ret == 0, u32Ret, "Disconnect Failed. u32Ret = 0x%x. u32NodeID = %u", u32Ret, u32NodeID);
        } while (0);

        LogInfo("RecvMessageHeadCB error. error = %d, error: %s", ec.value(), ec.message().c_str());
#ifdef _DEBUG_
        std::cout << ec.message() << std::endl;
#endif
    }
}

VOID CNetSession::RecvMessageBodyCB(IN const boost::system::error_code& ec, IN UINT32 u32MsgLen, IN UINT32 u32NodeID)
{
    UINT32 u32Ret = 0;
    if (!ec)
    {
        // 接收包体成功
        UINT32 u32MsgType = 0;
        std::string strStructBuf;
        // pb -> struct 获取u32MsgType
        u32Ret = CAppProtocol::ProtoBuf2Struct(m_acMessageBody, u32MsgLen, u32MsgType, strStructBuf);
#ifdef _MEM_POOL_
        CNetInnerMsg* pNetMsg = new CNetInnerMsg(u32NodeID, u32MsgType, u32MsgLen - sizeof(UINT32), m_acMessageBody.data() + sizeof(UINT32), &m_tMemPool);
#else
        // 只要这个数据包的长度正确了 那么所有的元素都是正确的
        CNetInnerMsg* pNetMsg = new CNetInnerMsg(u32NodeID, u32MsgType, strStructBuf.length(), strStructBuf.c_str());
#endif

#ifdef _LOCK_FREE_QUEUE_
        if (!g_netMsgQueue.push(pNetMsg))
#else
        if (!g_netMsgSpscQueue.push(pNetMsg))
#endif
        {
            delete pNetMsg;
        }

        // 不清空缓存 持续接收数据 这里不能用clear 否则会死循环
        DoRecvMessage(u32NodeID);
    }
    else
    {
        // 其他原因导致读取失败 连接可能断开
        // 连接断开 回收节点ID资源
        do 
        {
            u32Ret = m_pNetworkMgr->Disconnect(u32NodeID);
            CHECK_ERR_BREAK(u32Ret == 0, u32Ret, "Disconnect Failed. u32Ret = 0x%x. u32NodeID = %u", u32Ret, u32NodeID);
        } while (0);

        LogInfo("RecvMessageBodyCB error. error = %d, error: %s", ec.value(), ec.message().c_str());
#ifdef _DEBUG_
        std::cout << ec.message() << std::endl;
#endif
    }
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
        // 断开连接进到这里
        // 连接断开 回收节点ID资源
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
    
    // 数据包过大 丢弃
    if (u32MsgLen > NET_MESSAGE_BODY_MAX_SIZE)
    {
        LogFatal("Recv message error for out of bounds. u32MsgLen = %d", u32MsgLen);
        return;
    }

    // 如果有数据
    // 将数据封装到类中 然后写入队列
    UINT32 u32MsgType = 0;
    memcpy(&u32MsgType, m_acMessageBody, sizeof(UINT32));
#ifdef _DEBUG_
    std::cout << "len: " << u32MsgLen << std::endl;
#endif

#ifdef _WIN32_
    //QueryPerformanceFrequency(&nFreq);
    //QueryPerformanceCounter(&t1);
#else
#endif

#ifdef _MEM_POOL_
    CNetInnerMsg* pNetMsg = new CNetInnerMsg(u32NodeID, u32MsgType, u32MsgLen - sizeof(UINT32), m_acMessageBody.data() + sizeof(UINT32), &m_tMemPool);
#else
    CNetInnerMsg* pNetMsg = new CNetInnerMsg(u32NodeID, u32MsgType, u32MsgLen, m_acMessageBody);
#endif
#ifdef _WIN32_
    //QueryPerformanceFrequency(&nFreq);
    //QueryPerformanceCounter(&t1);
#else
#endif

#ifdef _LOCK_FREE_QUEUE_
    if (!g_netMsgQueue.push(pNetMsg))
#else
    if (!g_netMsgSpscQueue.push(pNetMsg))
#endif
    {
        delete pNetMsg;
    }

    //m_cNetMessageVec.clear();
    // 清空缓冲区 持续接收数据 这里不能用clear 否则会死循环 暂时不清空试试看
    //memset(m_cMessageBodyVec.data(), 0, m_cMessageBodyVec.size());
    m_socket.async_read_some(boost::asio::buffer(m_acMessageBody), boost::bind(&CNetSession::MessageHandlerCB, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred, u32NodeID));
}

VOID CNetSession::PostMessage(IN UINT32 u32MsgType, IN UINT32 u32MsgLen, IN const CHAR* pcMsg)
{
    boost::system::error_code error;
    // 不可以异步发送数据 异步发送数据是需要一个队列 循环弹出数据发送
    //m_socket.async_write_some(boost::asio::buffer(strMsg), boost::bind(&CNetSession::PostMessage, this, strMsg));
    //m_socket.async_write_some(boost::asio::buffer(strMsg), boost::bind(&CNetSession::Test, this));
    //boost::asio::async_write(m_socket, boost::asio::buffer(strMsg), boost::bind(&CNetSession::Test, this));

    // fix: 调试
    // 同步发送数据
#if 0
    std::vector<CHAR> cMessageVec(u32MsgLen + sizeof(u32MsgType) + 1, 0);
    memcpy(cMessageVec.data(), &u32MsgType, sizeof(u32MsgType));
    memcpy(cMessageVec.data() + sizeof(u32MsgType), pcMsg, u32MsgLen);
#else
    std::vector<CHAR> cMessageVec(u32MsgLen, 0);
    memcpy(cMessageVec.data(), pcMsg, u32MsgLen);
#endif

    if (m_socket.is_open())
    {
        m_socket.write_some(boost::asio::buffer(cMessageVec), error);
    }

    if (error)
    {
#ifdef _DEBUG_
        std::cout << boost::system::system_error(error).what() << std::endl;
#endif
        LogError("write_some error. error_code = %d, error: %s", error.value(), error.message().c_str());
        return;
    }
}

