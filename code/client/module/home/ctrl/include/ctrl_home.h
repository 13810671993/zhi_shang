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
    void	SIGNAL_OnlineUser(QList<T_GNRL_ONLINE_USER> tUserList);

public:
    VOID	OnGetOnlineUserRsp(const CHAR* pcMsg, UINT32 u32MsgLen);

private:
    static CCtrlHome*	m_pCtrlHome;
};

#endif // CTRL_HOME_H

