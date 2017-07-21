#include "network/network_common.h"

CNetwork::CNetwork() : QObject(), m_pSocket(nullptr)
{
    InitNetwork();
}

CNetwork::~CNetwork()
{
    m_pSocket->close();
    delete m_pSocket;
}

CNetwork* CNetwork::m_pNetwork = NULL;

CNetwork* CNetwork::GetInstance()
{
    if (m_pNetwork == NULL)
        m_pNetwork = new CNetwork();
    return m_pNetwork;
}

void CNetwork::DestroyInstance()
{
    if (m_pNetwork != NULL)
    {
        delete m_pNetwork;
        m_pNetwork = NULL;
    }
}

BOOL CNetwork::Connect(const QString& qstrIp, const QString& qstrPort, QString& qstrError)
{
    if (m_pSocket->isOpen())
    {
        return TRUE;
    }
    else
    {
        m_pSocket->abort();
        m_pSocket->connectToHost(qstrIp, qstrPort.toInt());
        BOOL bResult = m_pSocket->waitForConnected(3 * 1000);
        qstrError = tr(m_pSocket->errorString().toStdString().data());
        return bResult;
    }
}

VOID CNetwork::PostMessage(UINT32 u32MsgType, CHAR *pcMsg, UINT32 u32MsgLen)
{
    std::string strProtoBuf;
    CAppProtocol::Struct2ProtoBuf(u32MsgType, pcMsg, u32MsgLen, strProtoBuf);
    std::string strMsg;
    UINT32 u32PbLen = strProtoBuf.length();
    strMsg.append((CHAR*)&u32PbLen, sizeof(u32PbLen));
    strMsg += strProtoBuf;

    if (m_pSocket->isOpen())
        m_pSocket->write(strMsg.data(), sizeof(UINT32) + strProtoBuf.length());

}

void CNetwork::SLOT_RecvMessage()
{
    QByteArray qstrMessage = m_pSocket->readAll();
    UINT32 u32MsgType = 0;
    std::string strStructBuf;
    UINT32 u32PbLen = qstrMessage.length();
    CAppProtocol::ProtoBuf2Struct(qstrMessage.data(), qstrMessage.length(), u32MsgType, strStructBuf);
    PushMessage(u32MsgType, strStructBuf.c_str(), strStructBuf.length());
}

void CNetwork::SLOT_Error(QAbstractSocket::SocketError)
{
    qDebug() << m_pSocket->errorString();
    m_pSocket->close();
}

VOID CNetwork::InitNetwork()
{
    m_pSocket = new QTcpSocket(this);
    connect(m_pSocket, SIGNAL(readyRead()), this, SLOT(SLOT_RecvMessage()));

    connect(m_pSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(SLOT_Error(QAbstractSocket::SocketError)));
}

VOID CNetwork::PushMessage(UINT32 u32MsgType, const CHAR *pcMsg, UINT32 u32MsgLen)
{
    switch (u32MsgType)
    {
    case E_APP_MSG_REGIST_USER_RSP:
        CCtrlUser::GetInstance()->OnRegistUserRsp(pcMsg, u32MsgLen);
        break;
    case E_APP_MSG_MODIFY_PASSWD_RSP:
        CCtrlUser::GetInstance()->OnModifyPasswdRsp(pcMsg, u32MsgLen);
        break;
    case E_APP_MSG_LOGIN_RSP:
        CCtrlLogin::GetInstance()->OnLoginRsp(pcMsg, u32MsgLen);
        break;
    case E_APP_MSG_GET_ONLINE_USER_RSP:
        CCtrlHome::GetInstance()->OnGetOnlineUserRsp(pcMsg, u32MsgLen);
        break;


    default:
        break;
    }
}
