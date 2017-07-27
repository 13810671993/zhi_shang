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
//    OnGetOnlineReq();

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
    if (ui->CListSession->currentItem() != NULL)
    {
        ui->CLblObjID->setText(ui->CListSession->currentItem()->text());
    }
    if (bFlag)
        ui->CStackedWidget->setCurrentIndex(0);
}

void CHomeWidget::SLOT_SwitchMailPage(bool bFlag)
{
    ui->CListMail->setVisible(TRUE);
    ui->CLblObjID->clear();
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

void CHomeWidget::SLOT_UpdateOnlineUser(QList<T_GNRL_ONLINE_USER> tUserList)
{
    // 将所有用户插入到CListMail
    UINT32 i = 1;
    m_tUserList = tUserList;
    ui->CListMail->clear();
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
    UINT32 u32Key;
    u32Key = FindIndex(m_tSessionList, &(m_tUserList.at(u32Index)));

    auto it = m_tSessionMap.find(u32Key);
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
        static UINT32 u32ID = 0;
        m_tSessionMap.insert(u32ID, pSessionArea);
        ++u32ID;
        pSessionArea->show();
        m_tSessionList.push_back(m_tUserList.at(u32Index));
    }
    else
    {
        // 这是一个已有的会话
        pSession = ui->CListSession->item(u32Key);
        (*it)->show();
    }

    // 3. 设置为当前会话条目
    ui->CListSession->setCurrentItem(pSession);

    // 4. 显示对方ID
    ui->CLblObjID->setText(pSession->text());
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
    UINT32 u32Index = ui->CListSession->currentRow();
    // 1. 发送消息
    T_APP_SEND_MESSAGE_REQ tReq = {0};
    tReq.u64Context = 1;
//    memcpy(tReq.acMessage, m_qstrSendMessage.toStdString().c_str(), sizeof(tReq.acMessage));
//    memcpy(tReq.acObjID, m_tSessionList.at(u32Index).acUserName, sizeof(tReq.acObjID));
    strcpy(tReq.acMessage, m_qstrSendMessage.toStdString().c_str());
    strcpy(tReq.acObjID, m_tSessionList.at(u32Index).acUserName);
    CNetwork::GetInstance()->PostMessage(E_APP_MSG_SEND_MESSAGE_REQ, (CHAR*)&tReq, sizeof(tReq));

    // 2. 张贴消息
    // 获取当前的对话界面
    auto it = m_tSessionMap.find(u32Index);
    if (it != m_tSessionMap.end())
    {
        // 找到了界面了
        QScrollArea* pSessionArea = *it;
        QLabel* pLabel = new QLabel(m_qstrSendMessage);
        pLabel->setMaximumWidth(300);
        pLabel->setMinimumHeight(40);
        pLabel->adjustSize();
        pLabel->setAlignment(Qt::AlignCenter);
        pLabel->setStyleSheet("QLabel"
                              "{"
                              "background-color: #a0e664;"
                              "border-radius: 5px;"
                              "}");
        pSessionArea->widget()->layout()->addWidget(pLabel);
        pSessionArea->widget()->layout()->setAlignment(pLabel, Qt::AlignRight);
        pSessionArea->verticalScrollBar()->setValue(pSessionArea->verticalScrollBar()->maximum());
        qDebug() << pSessionArea->widget();
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

void CHomeWidget::SLOT_SwitchSession(QListWidgetItem* pItem)
{
    UINT32 u32Index = ui->CListSession->row(pItem);
    auto it = m_tSessionMap.find(u32Index);
    if (it != m_tSessionMap.end())
    {
        // 找到了
        QScrollArea* pSessionArea = *it;
        pSessionArea->raise();
        qDebug() << u32Index;

        ui->CLblObjID->setText(pItem->text());
    }
    else
    {
        // 没找到
    }
}

void CHomeWidget::SLOT_TransmitMessage(QString qstrFrmID, QString qstrMessage)
{
    T_GNRL_ONLINE_USER tUser = {0};
    strcpy(tUser.acUserName, qstrFrmID.toStdString().c_str());
    UINT32 u32Index = FindIndex(m_tSessionList, &tUser);
    if (u32Index >= 0)
    {
        // 找到了
        auto it = m_tSessionMap.find(u32Index);
        if (it != m_tSessionMap.end())
        {
            // 找到了
            // 1. 切换界面到会话界面
            emit ui->CStackedWidget->currentChanged(0);

            // 2. 切换到对应的会话item
            ui->CListSession->setCurrentRow(u32Index);

            // 3. 张贴消息
            QScrollArea* pSessionArea = *it;
            QLabel* pLabel = new QLabel(qstrMessage);
            pLabel->setMaximumWidth(300);
            pLabel->setMinimumHeight(40);
            pLabel->adjustSize();
            pLabel->setAlignment(Qt::AlignCenter);
            pLabel->setStyleSheet("QLabel"
                                  "{"
                                  "background-color: white;"
                                  "border-radius: 5px;"
                                  "}");
            pSessionArea->widget()->layout()->addWidget(pLabel);
            pSessionArea->widget()->layout()->setAlignment(pLabel, Qt::AlignLeft);
            pSessionArea->verticalScrollBar()->setValue(pSessionArea->verticalScrollBar()->maximum());
        }
        else
        {
            // 没找到
        }
    }
    else
    {
        // 没找到
    }
}

VOID CHomeWidget::InitWidget()
{
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
//    setWindowFlags(Qt::Widget | Qt::WindowStaysOnTopHint | Qt::X11BypassWindowManagerHint | Qt::FramelessWindowHint);
    setWindowFlags(Qt::Widget | Qt::X11BypassWindowManagerHint | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
}

VOID CHomeWidget::InitStyle()
{
    QFile styleSheetHome(":/home/resource/home.qss");
    if (styleSheetHome.open(QFile::ReadOnly))
    {
        this->setStyleSheet(styleSheetHome.readAll());
        styleSheetHome.close();
    }
    QFile styleSheetMail(":/home/resource/mail.qss");
    if (styleSheetMail.open(QFile::ReadOnly))
    {
        ui->CMailListPage->setStyleSheet(styleSheetMail.readAll());
        styleSheetMail.close();
    }
    QFile styleSheetSession(":/home/resource/session.qss");
    if (styleSheetSession.open(QFile::ReadOnly))
    {
        ui->CSessionListPage->setStyleSheet(styleSheetSession.readAll());
        styleSheetSession.close();
    }
}

VOID CHomeWidget::BindSignals()
{
    connect(ui->CBtnClose, SIGNAL(clicked()), this, SLOT(SLOT_Exit()));
    connect(ui->CBtnMinimum, SIGNAL(clicked()), this, SLOT(showMinimized()));
    connect(ui->CBtnSession, SIGNAL(clicked(bool)), this, SLOT(SLOT_SwitchSessionPage(bool)));
    connect(ui->CBtnMail, SIGNAL(clicked(bool)), this, SLOT(SLOT_SwitchMailPage(bool)));

    qRegisterMetaType< QList<T_GNRL_ONLINE_USER> >("QList<T_GNRL_ONLINE_USER>");
    connect(CCtrlHome::GetInstance(), SIGNAL(SIGNAL_UpdateOnlineUser(QList<T_GNRL_ONLINE_USER>)), this, SLOT(SLOT_UpdateOnlineUser(QList<T_GNRL_ONLINE_USER>)));
    connect(CCtrlHome::GetInstance(), SIGNAL(SIGNAL_TransmitMessage(QString,QString)), this, SLOT(SLOT_TransmitMessage(QString,QString)));
    connect(ui->CListMail, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(SLOT_OpenUserInfo(QListWidgetItem*)));
    connect(ui->CStackedWidget, SIGNAL(currentChanged(int)), this, SLOT(SLOT_CurrentPage(int)));
    connect(ui->CBtnSendMessage, SIGNAL(clicked()), this, SLOT(SLOT_OpenSession()));
    connect(ui->CBtnSend, SIGNAL(clicked()), this, SLOT(SLOT_SendMessage()));
    connect(ui->CTedInput, SIGNAL(textChanged()), this, SLOT(SLOT_GetSendMessage()));
    connect(ui->CListSession, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(SLOT_SwitchSession(QListWidgetItem*)));
}

VOID CHomeWidget::OnGetOnlineReq()
{
    T_APP_GET_ONLINE_USER_REQ	tReq = {0};
    tReq.u64Context = 1;
    CNetwork::GetInstance()->PostMessage(E_APP_MSG_GET_ONLINE_USER_REQ, (CHAR*)&tReq, sizeof(tReq));
}

QScrollArea* CHomeWidget::CreateSessionArea(T_GNRL_ONLINE_USER &tOnlineUser)
{
    QScrollArea* pSessionArea = new QScrollArea(ui->CFrmBackground);
    pSessionArea->setMinimumSize(550, 430);
    pSessionArea->move(0, 0);
    pSessionArea->setStyleSheet("QScrollArea{background-color: #f5f5f5;"
                                "border-top: 1px solid #e7e7e7;"
                                "}");

    QVBoxLayout* pLayout = new QVBoxLayout();
    pLayout->addStretch();

    QWidget* pWidget = new QWidget();
    pWidget->setLayout(pLayout);

    pSessionArea->setWidget(pWidget);
    pSessionArea->setWidgetResizable(TRUE);

    return pSessionArea;
}

UINT32 CHomeWidget::FindIndex(QList<T_GNRL_ONLINE_USER> &list, const T_GNRL_ONLINE_USER* pDest)
{
    UINT32 u32Index = 0;
    for (auto it = list.begin(); it != list.end(); ++it, ++u32Index)
    {
        T_GNRL_ONLINE_USER* p = &(*it);
        if (memcmp(pDest, p, sizeof(*pDest)) == 0)	// 找到相同的了
            return u32Index;
    }

    return -1;
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
