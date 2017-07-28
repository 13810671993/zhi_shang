#ifndef PAGE_MANAGER_H
#define PAGE_MANAGER_H

#include <QApplication>
#include <QObject>
#include <QWidget>

#include "common/data_type.h"

class CPageMgr : public QWidget
{
    Q_OBJECT

public:
    CPageMgr(const QApplication* pApp = NULL);
    ~CPageMgr();

public slots:
    void SLOT_LoginSuccess(QString);

public:
    void StartLogin();

private:
    CPageMgr*			m_pLoginPage;
    CPageMgr*			m_pHomePage;
    const QApplication*	m_pApp;

};

#endif // PAGE_MANAGER_H

