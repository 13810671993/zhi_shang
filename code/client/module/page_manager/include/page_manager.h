#ifndef PAGE_MANAGER_H
#define PAGE_MANAGER_H

#include <QApplication>
#include <QObject>

class QWidget;
class CPageMgr : QObject
{
    Q_OBJECT

public:
    CPageMgr(const QApplication* pApp);
    ~CPageMgr();

public slots:
    void SLOT_LoginSuccess();

public:
    void StartLogin();

private:
    QWidget*	m_pLoginPage;
    QWidget*	m_pHomePage;
    const QApplication*	m_pApp;

};

#endif // PAGE_MANAGER_H

