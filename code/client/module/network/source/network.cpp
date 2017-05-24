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

void CNetwork::PortEditFinished(QString qstrPort)
{
    // port编辑完成 获取到port
    m_iPort = qstrPort.toInt();
    qDebug() << m_iPort;
}

void CNetwork::DoConnect()
{
    Connect();
}

void CNetwork::DoSendMessage(QString qstrSendMessage)
{
    // 1. 获取输入框中的发送信息
    // 2.

}

void CNetwork::RecvMessage()
{
    QString qstrMessage = m_pSocket->readAll();
    emit ShowRecvMessage(qstrMessage);
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
