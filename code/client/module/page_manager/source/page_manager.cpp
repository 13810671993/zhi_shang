#include "page_manager/page_manager_common.h"

CPageMgr::CPageMgr() : QObject()
    , m_pLoginPage(NULL)
    , m_pHomePage(NULL)
{

}

CPageMgr::~CPageMgr()
{

}

void CPageMgr::SLOT_LoginSuccess()
{
    // 登录成功后 先把登录界面隐藏起来 然后显示主界面
    m_pLoginPage->hide();

    // 是否显示过场动画

    m_pHomePage = new CHomeWidget();
    m_pHomePage->show();
}

void CPageMgr::StartLogin()
{
    m_pLoginPage = new CLoginWidget();
    connect(m_pLoginPage, SIGNAL(SIGNAL_LoginSuccess()), this, SLOT(SLOT_LoginSuccess()));
    m_pLoginPage->show();
}
