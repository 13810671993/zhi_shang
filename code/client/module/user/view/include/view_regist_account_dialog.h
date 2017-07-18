#ifndef VIEW_REGIST_ACCOUNT_DIALOG_H
#define VIEW_REGIST_ACCOUNT_DIALOG_H

#include <QDialog>
#include "common/data_type.h"

namespace Ui {
class CRegistAccountDialog;
}

class CRegistAccountDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CRegistAccountDialog(QWidget *parent = 0);
    ~CRegistAccountDialog();

signals:
    void SIGNAL_Connect2Server();

public slots:
    void SLOT_PopRegistPage();
    void SLOT_GetUserName(QString);
    void SLOT_GetPasswd(QString);
    void SLOT_GetSecondpasswd(QString);
    void SLOT_FinishedInputPasswd();
    void SLOT_GetSex(bool);
    void SLOT_Regist();


private:
    VOID InitWidget();
    VOID InitWindow();
    VOID InitStyly();
    VOID BindSignals();

private:
    Ui::CRegistAccountDialog *ui;

    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void closeEvent(QCloseEvent *);

private:
    QWidget*					m_pParentWidget;
    QPoint						m_dragPosition;
    BOOL						m_bMoving;
    BOOL						m_bPageExist;		// TRUE: 存在 FALSE: 不存在
    BOOL						m_bSex;				// TRUE: 男 FALSE: 女
    QString						m_qstrUserName;
    QString						m_qstrPasswd;

};

#endif // VIEW_REGIST_ACCOUNT_DIALOG_H
