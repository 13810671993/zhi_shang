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
    void ShowRecvMessage(QString qstrMessage);
    void SendMessage(QString qstrSendMessage);

public slots:
    void PortEditFinished(QString qstrPort);
    void DoConnect();
    void DoSendMessage(QString qstrSendMessage);

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

