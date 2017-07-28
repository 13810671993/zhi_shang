#ifndef VIEW_HOME_WIDGET_H
#define VIEW_HOME_WIDGET_H

#include <QWidget>
#include <QListWidgetItem>
#include <QMap>
#include <QScrollArea>
#include "home/home_common.h"

namespace Ui {
class CHomeWidget;
}

class CPageMgr;
class CHomeWidget : public CPageMgr
{
    Q_OBJECT

public:
    explicit CHomeWidget(QString qstrUserInfo);
    ~CHomeWidget();

public slots:
    void SLOT_Exit();
    void SLOT_SwitchSessionPage(bool);
    void SLOT_SwitchMailPage(bool);
    void SLOT_CurrentPage(int);
    void SLOT_UpdateOnlineUser(QList<T_GNRL_ONLINE_USER> tUserList);
    void SLOT_OpenSession();
    void SLOT_OpenUserInfo(QListWidgetItem* pUserItem);
    void SLOT_SendMessage();
    void SLOT_GetSendMessage();
    void SLOT_SwitchSession(QListWidgetItem*);
    void SLOT_TransmitMessage(QString, QString);
    void SLOT_SendMessageError(QString);

private:
    VOID InitWidget(QString qstrUserInfo);
    VOID InitWindow();
    VOID InitStyle();
    VOID BindSignals();

    VOID OnGetOnlineReq();
    QScrollArea* 	CreateSessionArea();
    UINT32			FindIndex(QList<T_GNRL_ONLINE_USER>& list, const T_GNRL_ONLINE_USER* pDest);
    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);

private:
    Ui::CHomeWidget *ui;
    QPoint									m_dragPosition;
    BOOL									m_bMoving;
    QList<T_GNRL_ONLINE_USER>				m_tUserList;
    QList<T_GNRL_ONLINE_USER>				m_tSessionList;
    QMap<UINT32, QScrollArea*>				m_tSessionMap;
    QString 								m_qstrSendMessage;

};

#endif // VIEW_HOME_WIDGET_H
