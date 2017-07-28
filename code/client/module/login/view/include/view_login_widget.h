#ifndef VIEW_LOGIN_WIDGET_H
#define VIEW_LOGIN_WIDGET_H

#include <QWidget>
#include "common/data_type.h"
#include "page_manager/include/page_manager.h"

namespace Ui {
class CLoginWidget;
}

class CRegistAccountDialog;
class CModifyPasswdDialog;
class CPageMgr;
class CLoginWidget : public CPageMgr
{
    Q_OBJECT

public:
    explicit CLoginWidget();
    ~CLoginWidget();

signals:
    void SIGNAL_LoginSuccess(QString);

public slots:
    void SLOT_Exit();
    void SLOT_SwitchPage();
    void SLOT_Connect2Server();
    void SLOT_Login();

private:
    VOID InitWidget();
    VOID InitWindow();
    VOID InitStyle();
    VOID BindSignals();

private:
    Ui::CLoginWidget *ui;

    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);

private:
    QPoint						m_dragPosition;
    BOOL						m_bMoving;
    BOOL						m_bRegistExist;			// TRUE: 窗体已存在 FALSE: 窗体不存在
    CRegistAccountDialog*		m_pRegistAccountDialog;
    CModifyPasswdDialog*		m_pModifyPasswdDialog;


};

#endif // VIEW_LOGIN_WIDGET_H
