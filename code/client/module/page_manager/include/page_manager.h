#ifndef PAGE_MANAGER_H
#define PAGE_MANAGER_H

#include <QObject>

class QWidget;
class CPageMgr : QObject
{
    Q_OBJECT

public:
    CPageMgr();
    ~CPageMgr();

public slots:
    void SLOT_LoginSuccess();

public:
    void StartLogin();

private:
    QWidget*	m_pLoginPage;
    QWidget*	m_pHomePage;

};

#endif // PAGE_MANAGER_H

