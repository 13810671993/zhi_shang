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
    m_pSocket->abort();
    m_pSocket->connectToHost(qstrIp, qstrPort.toInt());
    BOOL bResult = m_pSocket->waitForConnected(3 * 1000);
    qstrError = m_pSocket->errorString();
    return bResult;
}

VOID CNetwork::SendMessage(UINT32 u32MsgType, CHAR *pcMsg, UINT32 u32MsgLen)
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
    QString qstrMessage = m_pSocket->readAll();
    QByteArray arrMsg =  qstrMessage.toLatin1();
    UINT32 u32MsgType = 0;
    UINT32 u32PbLen = 0;
    memcpy(&u32PbLen, arrMsg.data(), sizeof(u32PbLen));
    std::string strStructBuf;
    CAppProtocol::ProtoBuf2Struct(arrMsg.data() + sizeof(u32PbLen), u32PbLen, u32MsgType, strStructBuf);
    PushMessage(u32MsgType, strStructBuf.c_str(), strStructBuf.length());

    qDebug() << qstrMessage;
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

    connect(m_pSocket, SIGNAL(QAbstractSocket::SocketError), this, SLOT(SLOT_Error()));
}

VOID CNetwork::PushMessage(UINT32 u32MSgType, const CHAR *pcMsg, UINT32 u32MsgLen)
{
    switch (u32MSgType)
    {
    case E_APP_MSG_REGIST_USER_RSP:
        CCtrlUser::GetInstance()->OnRegistUserRsp(pcMsg, u32MsgLen);
        break;
    case E_APP_MSG_MODIFY_PASSWD_RSP:
        CCtrlUser::GetInstance()->OnModifyPasswdRsp(pcMsg, u32MsgLen);

        break;
    default:
        break;
    }
}
