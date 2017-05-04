#include "network_common.h"

boost::lockfree::queue<CNetMsgLayer*, boost::lockfree::fixed_sized<FALSE>> g_netMsgQueue(0);

CNetSession::CNetSession(boost::asio::io_service& ioServer, CNetConnectionMgr* pNetConnectionMgr) : m_socket(ioServer), m_cNetMessageVec(2048, 0), m_pNetConnectionMgr(pNetConnectionMgr)
{
    boost::thread threadImp(boost::bind(&CNetSession::PushMessage2AdptThread, this));
}

CNetSession::~CNetSession()
{

}

VOID CNetSession::PushMessage2AdptThread(VOID* pParam)
{
    CNetSession* pThis = (CNetSession*)pParam;
    CNetMsgLayer* pNetMsg = NULL;
    while (1)
    {
        // �Ӷ����е������� д��adpt��ȥ
        if (g_netMsgQueue.pop(pNetMsg) && pNetMsg != NULL)
        {
            std::cout << pNetMsg->GetMsgBuf() << std::endl;
            pThis->PostMessage(pNetMsg->GetMsgBuf());
            delete pNetMsg;
            pNetMsg = NULL;
        }
        else
            BOOST_SLEEP(100);
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
    //CNetMsgLayer* pNetMsg = new CNetMsgLayer(u32NodeID, (UINT32)m_cNetMessageVec.data(), m_cNetMessageVec.data(), m_cNetMessageVec.size() - sizeof(UINT32));
    g_netMsgQueue.push(pNetMsg);

    // ��ջ����� ���½�������
    memset(m_cNetMessageVec.data(), 0, m_cNetMessageVec.size());
    m_socket.async_read_some(boost::asio::buffer(m_cNetMessageVec), boost::bind(&CNetSession::MessageHandlerCB, this, boost::asio::placeholders::error, u32NodeID));
}

VOID CNetSession::PostMessage(IN const std::string& strMsg)
{
    //std::vector<CHAR> cMessageVec(strMsg.size() + 1, 0);
    //memcpy(cMessageVec.data(), strMsg.data(), strMsg.size());
    //m_socket.async_write_some(boost::asio::buffer(strMsg), boost::bind(&CNetSession::PostMessage, this, strMsg));
    //m_socket.async_write_some(boost::asio::buffer(strMsg), boost::bind(&CNetSession::Test, this));
    //m_socket.async_send(boost::asio::buffer(strMsg), boost::bind(&CNetSession::Test, this));

    // TMD �첽�������ݻ�TM������
    //boost::system::error_code error;
    //m_socket.write_some(boost::asio::buffer(strMsg), error);
}

VOID CNetSession::Test()
{
    std::cout << "Test" << std::endl;
}

boost::asio::ip::tcp::socket& CNetSession::GetSocket()
{
    return m_socket;
}
