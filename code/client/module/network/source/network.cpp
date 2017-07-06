#include "network/network_common.h"


CNetwork::CNetwork() : QObject(), m_pSocket(nullptr), m_iPort(0)
{
    InitNetwork();
}

CNetwork::~CNetwork()
{
    m_pSocket->close();
    delete m_pSocket;
}

void CNetwork::SLOT_PortEditFinished(QString qstrPort)
{
    // port编辑完成 获取到port
    m_iPort = qstrPort.toInt();
    qDebug() << m_iPort;
}

void CNetwork::SLOT_Connect()
{
    Connect();
}

void CNetwork::SLOT_SendMessage(QString qstrSendMessage)
{
    T_APP_FIRST_TEST tFirstTest = {0};
    tFirstTest.u32Result = 1;
    tFirstTest.u32Test = 2;
    QString qstrMsgType;
    qstrMsgType.append(QString("%1").arg(sizeof(tFirstTest) + 8, 8, 10));
    qstrMsgType.append(QString("%1").arg(E_APP_MSG_FIRST_TEST, 8, 10));
    qstrMsgType.append((char*)&tFirstTest);
    m_pSocket->write(qstrMsgType.toStdString().data(), 24);
    //m_pSocket->write(qstrSendMessage.toLatin1());
}

void CNetwork::RecvMessage()
{
    QString qstrMessage = m_pSocket->readAll();
    emit SIGNAL_ShowRecvMessage(qstrMessage);
    qDebug() << qstrMessage;
}

void CNetwork::Error(QAbstractSocket::SocketError)
{
    qDebug() << m_pSocket->errorString();
    m_pSocket->close();
}

void CNetwork::InitNetwork()
{
    m_pSocket = new QTcpSocket(this);
    connect(m_pSocket, SIGNAL(readyRead()), this, SLOT(RecvMessage()));

    connect(m_pSocket, SIGNAL(QAbstractSocket::SocketError), this, SLOT(Error()));
}

void CNetwork::Connect()
{
    m_pSocket->abort();
    m_pSocket->connectToHost("192.168.9.51", m_iPort);
}
