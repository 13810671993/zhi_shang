#ifndef VIEW_MODIFY_PASSWD_DIALOG_H
#define VIEW_MODIFY_PASSWD_DIALOG_H

#include <QDialog>
#include "common/data_type.h"

namespace Ui {
class CModifyPasswdDialog;
}

class CModifyPasswdDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CModifyPasswdDialog(QWidget *parent = 0);
    ~CModifyPasswdDialog();

signals:
    void SIGNAL_Connect2Server();

public slots:
    void SLOT_PopModifyPage();
    void SLOT_GetUserName(QString);
    void SLOT_GetOldPasswd(QString);
    void SLOT_GetNewPasswd(QString);
    void SLOT_GetSecondNewPasswd(QString);
    void SLOT_FinishedInputNewPasswd();
    void SLOT_ModifyPasswd();

private:
    VOID InitWidget();
    VOID InitWindow();
    VOID InitStyly();
    VOID BindSignals();

    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void closeEvent(QCloseEvent *);

private:
    Ui::CModifyPasswdDialog *ui;

private:
    QWidget*					m_pParentWidget;
    QPoint						m_dragPosition;
    BOOL						m_bMoving;
    BOOL						m_bPageExist;		// TRUE: 存在 FALSE: 不存在
    QString						m_qstrUserName;
    QString						m_qstrOldPasswd;
    QString						m_qstrNewPasswd;
};

#endif // VIEW_MODIFY_PASSWD_DIALOG_H
