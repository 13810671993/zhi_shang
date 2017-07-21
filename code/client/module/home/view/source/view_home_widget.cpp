#include "home/home_common.h"
#include "ui_view_home_widget.h"

CHomeWidget::CHomeWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CHomeWidget)
{
    ui->setupUi(this);

    BindSignals();
    InitWidget();

    // 向服务器请求 获取在线列表
    OnGetOnlineReq();

    InitWindow();
    InitStyle();

}

CHomeWidget::~CHomeWidget()
{
    delete ui;
}

void CHomeWidget::SLOT_Exit()
{
    hide();
    exit(0);
}

void CHomeWidget::SLOT_SwitchSessionPage(bool bFlag)
{
    ui->CListSession->setVisible(TRUE);
    if (bFlag)
        ui->CStackedWidget->setCurrentIndex(0);
}

void CHomeWidget::SLOT_SwitchMailPage(bool bFlag)
{
    ui->CListMail->setVisible(TRUE);
    if (bFlag)
        ui->CStackedWidget->setCurrentIndex(1);
}

void CHomeWidget::SLOT_CurrentPage(int index)
{
    if (index == 0)
    {
        // session
        ui->CBtnSession->setChecked(TRUE);
    }
    else if (index == 1)
    {
        ui->CBtnMail->setChecked(TRUE);
    }
}

void CHomeWidget::SLOT_OnlineUser(QList<T_GNRL_ONLINE_USER> tUserList)
{
    // 将所有用户插入到CListMail
    UINT32 i = 1;
    m_tUserList = tUserList;
    for (auto it = tUserList.begin(); it != tUserList.end(); ++it, ++i)
    {
        QListWidgetItem* pUser = new QListWidgetItem(it->acUserName, ui->CListMail);
        ui->CListMail->addItem(pUser);
    }
}

void CHomeWidget::SLOT_OpenSession()
{
    ui->CListSession->setVisible(TRUE);
    // 1. 切换到session界面
    ui->CStackedWidget->setCurrentIndex(0);

    // 2. 创建一个新的会话 并插入到会话列表 CListSession
    QListWidgetItem* pUser = ui->CListMail->currentItem();
    QListWidgetItem* pSession = NULL;
    UINT32 u32Index = ui->CListMail->currentRow();
    auto it = m_tSessionMap.find(u32Index);
    if (it == m_tSessionMap.end())
    {
        // 这是一个新的会话

        // 1. 在CListSession中显示新的会话
        pSession = new QListWidgetItem(*pUser);
        ui->CListSession->addItem(pSession);
        // 2. 为新的会话创建对话窗口
        T_GNRL_ONLINE_USER	tOnlineUser = {0};
        memcpy(&tOnlineUser, &(m_tUserList.at(u32Index)), sizeof(tOnlineUser));
        QScrollArea* pSessionArea = CreateSessionArea(tOnlineUser);
        m_tSessionMap.insert(u32Index, pSessionArea);
        pSessionArea->show();
    }
    else
    {
        // 这是一个已有的会话

        (*it)->show();
    }
    // 3. 设置为当前会话条目
    ui->CListSession->setCurrentItem(pSession);
}

void CHomeWidget::SLOT_OpenUserInfo(QListWidgetItem *pUserItem)
{
    // 1. 激活控件
    ui->CBtnSendMessage->setVisible(TRUE);
    ui->CLblUserName->setVisible(TRUE);
    ui->CLblUserInfo->setVisible(TRUE);
    ui->CLblUserName->setText(pUserItem->text());
    ui->CLblUserInfo->setText(pUserItem->text());

    // 2. 切换session按钮按下状态
    ui->CBtnMail->setChecked(TRUE);
}

void CHomeWidget::SLOT_SendMessage()
{
    // 1. 发送消息

    // 2. 张贴消息
    // 获取当前的对话界面
    UINT32 u32Index = ui->CListMail->currentRow();
    auto it = m_tSessionMap.find(u32Index);
    if (it != m_tSessionMap.end())
    {
        // 找到了界面了
        QScrollArea* pSessionArea = *it;
        QLabel* pLabel = new QLabel(m_qstrSendMessage);
        pSessionArea->layout()->count();
        pSessionArea->layout()->addWidget(pLabel);
        pLabel->setAlignment(Qt::AlignRight);
//		pLayout->addStretch();
        pSessionArea->layout();
    }
    else
    {
        // 没找到界面
    }
}

void CHomeWidget::SLOT_GetSendMessage()
{
    m_qstrSendMessage = ui->CTedInput->toPlainText();
}


VOID CHomeWidget::InitWidget()
{
    ui->CListSession->setStyleSheet("QListWidget#CListSession{"
                                    "background-color: #e6e6e6;"
                                    "border: none;"
                                    "outline: none;"
                                    "}"
                                    "QListWidget#CListSession::item{"
                                    "height: 60px;"
                                    "}"
                                    );
    ui->CListMail->setStyleSheet("QListWidget#CListMail{"
                                    "background-color: #e6e6e6;"
                                    "border: none;"
                                    "outline: none;"
                                    "}"
                                    "QListWidget#CListMail::item{"
                                    "height: 60px;"
                                    "}"
                                    );
    ui->CBtnSendMessage->setText(tr("session"));
    ui->CBtnSendMessage->setVisible(FALSE);
    ui->CLblUserName->setVisible(FALSE);
    ui->CLblUserName->setVisible(FALSE);

    ui->CListSession->setVisible(FALSE);
    ui->CListMail->setVisible(FALSE);

    ui->CLedSearch->setPlaceholderText(tr("search"));
    ui->CBtnSession->setCheckable(TRUE);
    ui->CBtnSession->setAutoExclusive(TRUE);
    ui->CBtnMail->setCheckable(TRUE);
    ui->CBtnMail->setAutoExclusive(TRUE);

    ui->CBtnSend->setText(tr("send"));
}

VOID CHomeWidget::InitWindow()
{
    // 隐藏边框
    setWindowOpacity(1);
    setWindowFlags(Qt::Widget | Qt::WindowStaysOnTopHint | Qt::X11BypassWindowManagerHint | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
}

VOID CHomeWidget::InitStyle()
{
    QFile styleSheet(":/home/resource/home.qss");
    if (styleSheet.open(QFile::ReadOnly))
    {
        this->setStyleSheet(styleSheet.readAll());
        styleSheet.close();
    }
}

VOID CHomeWidget::BindSignals()
{
    connect(ui->CBtnClose, SIGNAL(clicked()), this, SLOT(SLOT_Exit()));
    connect(ui->CBtnMinimum, SIGNAL(clicked()), this, SLOT(showMinimized()));
    connect(ui->CBtnSession, SIGNAL(clicked(bool)), this, SLOT(SLOT_SwitchSessionPage(bool)));
    connect(ui->CBtnMail, SIGNAL(clicked(bool)), this, SLOT(SLOT_SwitchMailPage(bool)));

    qRegisterMetaType< QList<T_GNRL_ONLINE_USER> >("QList<T_GNRL_ONLINE_USER>");
    connect(CCtrlHome::GetInstance(), SIGNAL(SIGNAL_OnlineUser(QList<T_GNRL_ONLINE_USER>)), this, SLOT(SLOT_OnlineUser(QList<T_GNRL_ONLINE_USER>)));
    connect(ui->CListMail, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(SLOT_OpenUserInfo(QListWidgetItem*)));
    connect(ui->CStackedWidget, SIGNAL(currentChanged(int)), this, SLOT(SLOT_CurrentPage(int)));
//    connect(ui->CListMail, SIGNAL()
    connect(ui->CBtnSendMessage, SIGNAL(clicked()), this, SLOT(SLOT_OpenSession()));
    connect(ui->CBtnSend, SIGNAL(clicked()), this, SLOT(SLOT_SendMessage()));
    connect(ui->CTedInput, SIGNAL(textChanged()), this, SLOT(SLOT_GetSendMessage()));
}

VOID CHomeWidget::OnGetOnlineReq()
{
    T_APP_GET_ONLINE_USER_REQ	tReq = {0};
    tReq.u64Context = 1;
    CNetwork::GetInstance()->PostMessage(E_APP_MSG_GET_ONLINE_USER_REQ, (CHAR*)&tReq, sizeof(tReq));
}

QScrollArea* CHomeWidget::CreateSessionArea(T_GNRL_ONLINE_USER &tOnlineUser)
{
    QScrollArea* pSessionArea = new QScrollArea(ui->CSessionListPage);
    pSessionArea->setMinimumSize(550, 430);
    pSessionArea->move(250, 0);
    pSessionArea->setStyleSheet("background-color: red");
    QVBoxLayout* pLayout = new QVBoxLayout();
    pLayout->addStretch();
    pSessionArea->setLayout(pLayout);
    return pSessionArea;
}

void CHomeWidget::mousePressEvent(QMouseEvent* pEvent)
{
    if (pEvent->button() == Qt::LeftButton)
    {
        m_bMoving = true;

        // 记录当前位置
        m_dragPosition = pEvent->globalPos() - frameGeometry().topLeft();
        pEvent->accept();
    }
}

void CHomeWidget::mouseMoveEvent(QMouseEvent* pEvent)
{
    if (pEvent->buttons() & Qt::LeftButton)
    {
        if (m_bMoving)
        {
            //方法1：
            QDesktopWidget* desktop = QApplication::desktop();
            QRect windowRect(desktop->screenGeometry(desktop->primaryScreen()));
            QRect widgetRect(this->geometry());
            QPoint point(pEvent->globalPos() - m_dragPosition);

            //以下是防止窗口拖出可见范围外
            //左边
            if (point.x() <= 0)
            {
                point = QPoint(0,point.y());
            }
            //右边
            int y = windowRect.bottomRight().y() - this->size().height();
            if (point.y() >= y && widgetRect.topLeft().y() >= y)
            {
                point = QPoint(point.x(),y);
            }
            //上边
            if (point.y() <= 0)
            {
                point = QPoint(point.x(),0);
            }
            //下边
            int x = windowRect.bottomRight().x() - this->size().width();
            if (point.x() >= x && widgetRect.topLeft().x() >= x)
            {
                point = QPoint(x,point.y());
            }
            move(point);
        }
        pEvent->accept();
    }
}


void CHomeWidget::mouseReleaseEvent(QMouseEvent* pEvent)
{
    if(pEvent->button() == Qt::LeftButton)
    {
        m_bMoving = false;
        pEvent->accept();
    }
}
