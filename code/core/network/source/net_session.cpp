#include "network_common.h"

extern boost::lockfree::queue<CNetInnerMsg*, boost::lockfree::fixed_sized<FALSE>> g_netMsgQueue;

CNetSession::CNetSession(IN boost::asio::io_service& ioServer, IN CNetConnectionMgr* pNetConnectionMgr) : 
    m_socket(ioServer), m_cNetMessageVec(NET_MESSAGE_MAX_SIZE, 0), m_pNetConnectionMgr(pNetConnectionMgr)//, m_MemeryPool(NET_MESSAGE_MAX_SIZE)
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
    // boost::asio �����������ķǳ��� ������Խ������ ���ݰ������ʱ�򶼻�ֶ�������� ���Բ��ÿ���Խ������
    m_socket.async_read_some(boost::asio::buffer(m_cNetMessageVec), boost::bind(&CNetSession::MessageHandlerCB, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred, u32NodeID));
}

LARGE_INTEGER  nFreq, t1, t2;

VOID CNetSession::MessageHandlerCB(IN const boost::system::error_code& ec, IN UINT32 u32MsgLen, IN UINT32 u32NodeID)
{
    if (ec)
    {
        UINT32  u32Ret = 0;
        // �Ͽ����ӽ�������
        // ���ӶϿ� ���սڵ�ID��Դ
        do 
        {
            u32Ret = m_pNetConnectionMgr->Disconnect(u32NodeID);
            CHECK_ERR_BREAK(u32Ret == 0, u32Ret, "Disconnect Failed. u32Ret = 0x%x. u32NodeID = %u", u32Ret, u32NodeID);
        } while (0);

#ifdef _DEBUG_
        std::cout << ec.message() << std::endl;
#endif
        LogInfo("MessageHandlerCB error. error_code = %d, error: %s", ec.value(), ec.message().c_str());

        return; 
    }
    
    // Խ������Ӧ�ò������ ������� ����������������
    if (u32MsgLen > m_cNetMessageVec.size())
    {
        LogFatal("Recv message error for out of bounds. u32MsgLen = %d", u32MsgLen);
#ifdef _DEBUG_
        exit(0);
#else
        return;
#endif
    }

    // ���������
    // �����ݷ�װ������ Ȼ��д�����
    UINT32 u32MsgType = 0;
    memcpy(&u32MsgType, m_cNetMessageVec.data(), sizeof(UINT32));
    std::cout << "len: " << u32MsgLen << std::endl
        << "type: " << u32MsgType << std::endl;
    //std::cout << boost::posix_time::second_clock::local_time() << std::endl;;

    QueryPerformanceFrequency(&nFreq);
    QueryPerformanceCounter(&t1);

    // fix: ����
#if 0
    CNetInnerMsg* pNetMsg = new CNetInnerMsg(u32NodeID, u32MsgType, u32MsgLen - sizeof(UINT32), m_cNetMessageVec.data() + sizeof(UINT32));
#else
    CNetInnerMsg* pNetMsg = new CNetInnerMsg(u32NodeID, u32MsgType, u32MsgLen, m_cNetMessageVec.data());
#endif
    g_netMsgQueue.push(pNetMsg);

    //m_cNetMessageVec.clear();
    // ��ջ����� ������������ ���ﲻ����clear �������ѭ��
    memset(m_cNetMessageVec.data(), 0, m_cNetMessageVec.size());
    m_socket.async_read_some(boost::asio::buffer(m_cNetMessageVec), boost::bind(&CNetSession::MessageHandlerCB, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred, u32NodeID));
}

VOID CNetSession::SendMessage(IN UINT32 u32MsgType, IN UINT32 u32MsgLen, IN const CHAR* pcMsg)
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

