#ifndef CTRL_HOME_H
#define CTRL_HOME_H

#include <QObject>
#include <QList>

#include "home/home_common.h"

class CCtrlHome : public QObject
{
    Q_OBJECT

public:
    static CCtrlHome* 	GetInstance();
    static VOID			DestroyInstance();

protected:
    CCtrlHome();
    ~CCtrlHome();

signals:
    void	SIGNAL_UpdateOnlineUser(QList<T_GNRL_ONLINE_USER> tUserList);
    void	SIGNAL_TransmitMessage(QString qstrFrmID, QString qstrMessage);

public:
    VOID	OnUpdateOnlineUserNtf(const CHAR* pcMsg, UINT32 u32MsgLen);
    VOID	OnSendMessageRsp(const CHAR* pcMsg, UINT32 u32MsgLen);
    VOID	OnTransmitMessageAct(const CHAR* pcMsg, UINT32 u32MsgLen);

private:
    static CCtrlHome*	m_pCtrlHome;
};

#endif // CTRL_HOME_H

