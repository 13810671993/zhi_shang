#include "network_common.h"

extern boost::lockfree::queue<CNetMsgLayer*, boost::lockfree::fixed_sized<FALSE>> g_netMsgQueue;

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
        // �Ͽ����ӽ�������
        // ���ӶϿ� ���սڵ�ID��Դ
        do 
        {
            u32Ret = m_pNetConnectionMgr->Disconnect(u32NodeID);
            CHECK_ERR_BREAK(u32Ret == 0, u32Ret, "Disconnect Failed. u32Ret = 0x%x\n", u32Ret);
        } while (0);
        return; 
    }
    
    // ���������

    // �����ݷ�װ������ Ȼ��д�����
    CNetMsgLayer* pNetMsg = new CNetMsgLayer(u32NodeID, (UINT32)m_cNetMessageVec.data(), m_cNetMessageVec.data() + sizeof(UINT32), m_cNetMessageVec.size() - sizeof(UINT32));
    g_netMsgQueue.push(pNetMsg);

    // ��ջ����� ������������
    memset(m_cNetMessageVec.data(), 0, m_cNetMessageVec.size());
    m_socket.async_read_some(boost::asio::buffer(m_cNetMessageVec), boost::bind(&CNetSession::MessageHandlerCB, this, boost::asio::placeholders::error, u32NodeID));
}

VOID CNetSession::PostMessage(IN const std::string& strMsg)
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

    // ͬ����������
    m_socket.write_some(boost::asio::buffer(strMsg), error);
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
