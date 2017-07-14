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

public slots:
    void SLOT_PopModifyPage();
    void SLOT_GetUserName(QString);
    void SLOT_GetPasswd(QString);
    void SLOT_GetSecondpasswd(QString);
    void SLOT_FinishedInputPasswd();

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
    QString						m_qstrPasswd;
};

#endif // VIEW_MODIFY_PASSWD_DIALOG_H
