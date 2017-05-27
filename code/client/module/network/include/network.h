#ifndef NETWORK_H
#define NETWORK_H

#include <QString>
#include <QObject>
#include <QDebug>
#include <QtNetwork/QTcpSocket>

class CNetwork : public QObject
{
    Q_OBJECT

public:
    CNetwork();
    ~CNetwork();

signals:
    void SIGNAL_ShowRecvMessage(QString qstrMessage);
    void SIGNAL_SendMessage(QString qstrSendMessage);

public slots:
    void SLOT_PortEditFinished(QString qstrPort);
    void SLOT_Connect();
    void SLOT_SendMessage(QString qstrSendMessage);

private slots:
    void RecvMessage();
    void Error(QAbstractSocket::SocketError);

private:
    void InitNetwork();
    void Connect();

private:
    QTcpSocket* m_pSocket;
    int			m_iPort;
};

#endif // NETWORK_H

