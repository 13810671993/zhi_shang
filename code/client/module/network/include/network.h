#ifndef NETWORK_H
#define NETWORK_H

#include <QString>
#include <QObject>
#include <QDebug>
#include <QtNetwork/QTcpSocket>

#include "common/data_type.h"

class CNetwork : public QObject
{
    Q_OBJECT

public:
    static CNetwork* 	GetInstance();
    static void			DestroyInstance();

protected:
    CNetwork();
    ~CNetwork();

signals:
    void SIGNAL_SendMessage(QString qstrSendMessage);

private slots:
    void SLOT_RecvMessage();
    void SLOT_Error(QAbstractSocket::SocketError);

public:
    BOOL Connect(const QString& qstrIp, const QString& qstrPort, QString& qstrError);
    VOID SendMessage(UINT32 u32MsgType, CHAR* pcMsg, UINT32 u32MsgLen);

private:
    VOID InitNetwork();
    VOID PushMessage(UINT32 u32MSgType, const CHAR* pcMsg, UINT32 u32MsgLen);


private:
    static CNetwork*	m_pNetwork;

    QTcpSocket* m_pSocket;
};

#endif // NETWORK_H

