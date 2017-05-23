#ifndef CTRL_NETWORK_H
#define CTRL_NETWORK_H

class CNetwork
{
public:
    CNetwork();
    ~CNetwork();

private slots:
    void RecvMessage();
    void Error(QAbstractSocket::SocketError);

private:
    void InitNetwork();
    void NewConnect();

private:
    QTcpSocket* pSocket;
};

#endif // CTRL_NETWORK_H

