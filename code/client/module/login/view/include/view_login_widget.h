#ifndef VIEW_LOGIN_WIDGET_H
#define VIEW_LOGIN_WIDGET_H

#include <QWidget>
#include "common/data_type.h"

namespace Ui {
class CLoginWidget;
}

class CRegistAccountDialog;
class CModifyPasswdDialog;
class CLoginWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CLoginWidget(QWidget *parent = 0);
    ~CLoginWidget();

public slots:
    void SLOT_Exit();
    void SLOT_SwitchPage();
    void SLOT_Connect2Server();
    void SLOT_Login();

private:
    VOID InitWidget();
    VOID InitWindow();
    VOID InitStyly();
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
