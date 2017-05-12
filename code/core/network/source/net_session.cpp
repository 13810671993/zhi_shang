#include "network_common.h"

extern boost::lockfree::queue<CNetInnerMsg*, boost::lockfree::fixed_sized<FALSE>> g_netMsgQueue;

CNetSession::CNetSession(boost::asio::io_service& ioServer, CNetConnectionMgr* pNetConnectionMgr) : m_socket(ioServer), m_cNetMessageVec(2048, 0), m_pNetConnectionMgr(pNetConnectionMgr)
{
}

CNetSession::~CNetSession()
{
    if (m_socket.is_open())
    {
        m_socket.close();
    }
}

VOID CNetSession::StartSession(IN UINT32 u32NodeID)
{
    m_socket.async_read_some(boost::asio::buffer(m_cNetMessageVec), boost::bind(&CNetSession::MessageHandlerCB, this, boost::asio::placeholders::error, u32NodeID));
}

VOID CNetSession::MessageHandlerCB(IN const boost::system::error_code& ec, IN UINT32 u32NodeID)
{
    if (ec)
    {
        UINT32  u32Ret = 0;
        // 断开连接进到这里
        // 连接断开 回收节点ID资源
        do 
        {
            u32Ret = m_pNetConnectionMgr->Disconnect(u32NodeID);
            CHECK_ERR_BREAK(u32Ret == 0, u32Ret, "Disconnect Failed. u32Ret = 0x%x\n", u32Ret);
        } while (0);
        return; 
    }
    
    // 如果有数据

    // 将数据封装到类中 然后写入队列
    UINT32 u32MsgType = 0;
    UINT32 u32MsgLen = 0;
    std::string strMsg;
    memcpy(&u32MsgType, m_cNetMessageVec.data(), sizeof(UINT32));
    strMsg.assign(m_cNetMessageVec.data() + sizeof(UINT32));
    u32MsgLen = strMsg.length();
    CNetInnerMsg* pNetMsg = new CNetInnerMsg(u32NodeID, u32MsgType, (CHAR*)strMsg.data(), u32MsgLen);
    g_netMsgQueue.push(pNetMsg);

    // 清空缓冲区 持续接收数据
    memset(m_cNetMessageVec.data(), 0, m_cNetMessageVec.size());
    m_socket.async_read_some(boost::asio::buffer(m_cNetMessageVec), boost::bind(&CNetSession::MessageHandlerCB, this, boost::asio::placeholders::error, u32NodeID));
}

VOID CNetSession::SendMessage(IN UINT32 u32MsgType, IN UINT32 u32MsgLen, IN const CHAR* pcMsg)
{
    if (!m_socket.is_open())
    {
        return;
    }

    boost::system::error_code error;
    // 不可以异步发送数据 异步发送数据是需要一个队列 循环弹出数据发送
    //m_socket.async_write_some(boost::asio::buffer(strMsg), boost::bind(&CNetSession::PostMessage, this, strMsg));
    //m_socket.async_write_some(boost::asio::buffer(strMsg), boost::bind(&CNetSession::Test, this));
    //boost::asio::async_write(m_socket, boost::asio::buffer(strMsg), boost::bind(&CNetSession::Test, this));

    // 同步发送数据
    //CHAR acTemp = {0};
    CHAR* pcTemp = new CHAR[u32MsgLen + sizeof(u32MsgType) + 1];
    memset(pcTemp, 0, u32MsgLen + sizeof(u32MsgType) + 1);
    memcpy(pcTemp, &u32MsgType, sizeof(u32MsgType));
    memcpy(pcTemp + sizeof(u32MsgType), pcMsg, u32MsgLen);
    
    std::string strMsg(pcTemp);
    m_socket.write_some(boost::asio::buffer((const std::string)strMsg), error);
    delete[] pcTemp;
    if (error)
    {
        std::cout << boost::system::system_error(error).what() << std::endl;
        return;
    }
}

boost::asio::ip::tcp::socket& CNetSession::GetSocket()
{
    return m_socket;
}
