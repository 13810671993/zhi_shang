#include "page_manager/page_manager_common.h"

CPageMgr::CPageMgr(const QApplication* pApp) : QObject()
    , m_pLoginPage(NULL)
    , m_pHomePage(NULL)
    , m_pApp(pApp)
{

}

CPageMgr::~CPageMgr()
{

}

void CPageMgr::SLOT_LoginSuccess()
{
    // 登录成功后 先把登录界面隐藏起来 然后显示主界面
    m_pLoginPage->hide();
    m_pHomePage = new CHomeWidget();

    m_pHomePage->show();
#if 0
    // 是否显示过场动画
    QPixmap pixmap(":/login/resource/image/label_background_up_server.png");
    QSplashScreen splash(pixmap);
    splash.show();
    m_pApp->processEvents();

    m_pApp->thread()->sleep(3);

    m_pHomePage->show();
    splash.finish(m_pHomePage);
#endif
}

void CPageMgr::StartLogin()
{
    m_pLoginPage = new CLoginWidget();
    connect(m_pLoginPage, SIGNAL(SIGNAL_LoginSuccess()), this, SLOT(SLOT_LoginSuccess()));
    m_pLoginPage->show();
}
