#include "login/login_common.h"
#include "ui_view_login_widget.h"

CLoginWidget::CLoginWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CLoginWidget)
    , m_bRegistExist(FALSE)
    , m_pRegistAccountDialog(new CRegistAccountDialog(this))
    , m_pModifyPasswdDialog(new CModifyPasswdDialog(this))
{
    ui->setupUi(this);

    InitWidget();
    InitWindow();
    InitStyly();
    BindSignals();
}

CLoginWidget::~CLoginWidget()
{
    delete ui;
    if (m_pRegistAccountDialog != NULL)
    {
        delete m_pRegistAccountDialog;
        m_pRegistAccountDialog = NULL;
    }
    if (m_pModifyPasswdDialog != NULL)
    {
        delete m_pModifyPasswdDialog;
        m_pModifyPasswdDialog = NULL;
    }
}

void CLoginWidget::SwitchPage()
{
    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(500);
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->start();

    UINT32 u32Index = ui->CStackedWidget->currentIndex();
    if (u32Index == 0)	// Login info
        ui->CStackedWidget->setCurrentIndex(1);
    else				// Server info
        ui->CStackedWidget->setCurrentIndex(0);
}

VOID CLoginWidget::Exit()
{
    exit(0);
}

VOID CLoginWidget::InitWidget()
{
    ui->CLblIp_Server->setText(tr("ip addr"));
    ui->CLblPort_Server->setText(tr("port"));
    ui->CBtnCancel_Server->setText(tr("cancel"));
    ui->CBtnConfirm_Server->setText(tr("confirm"));
    ui->CLedPort_Server->setPlaceholderText(tr("port"));
    ui->CCmbIp_Server->setEditable(TRUE);
    ui->CCmbIp_Server->lineEdit()->setPlaceholderText(tr("ip"));
    ui->CLblUser_Login->setText(tr("user"));
    ui->CBtnLogin_Login->setText(tr("login"));
    ui->CLblPasswd_Login->setText(tr("passwd"));
    ui->CChkAutoLogin_Login->setText(tr("auto login"));
    ui->CBtnModifyPasswd_Login->setText(tr("modify"));
    ui->CBtnRegistAccount_Login->setText(tr("regist"));
    ui->CChkRememberPasswd_Login->setText(tr("remember passwd"));
    ui->CLedPasswd_Login->setPlaceholderText(tr("passwd"));
    ui->CCmbUser_Login->setEditable(TRUE);
    ui->CCmbUser_Login->lineEdit()->setPlaceholderText(tr("user name"));

    ui->CStackedWidget->setCurrentIndex(0);
}

VOID CLoginWidget::InitWindow()
{
    // 隐藏边框
    setWindowOpacity(1);
    setWindowFlags(Qt::Widget | Qt::WindowStaysOnTopHint | Qt::X11BypassWindowManagerHint | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
}

VOID CLoginWidget::InitStyly()
{
    QFile styleSheet(":/login/resource/login.qss");
    if (styleSheet.open(QFile::ReadOnly))
    {
        this->setStyleSheet(styleSheet.readAll());
        styleSheet.close();
    }
}

VOID CLoginWidget::BindSignals()
{
    connect(ui->CBtnClose_Login, SIGNAL(clicked()), this, SLOT(Exit()));
    connect(ui->CBtnMinimum_Login, SIGNAL(clicked()), this, SLOT(showMinimized()));
    connect(ui->CBtnSwitch_Login, SIGNAL(clicked()), this, SLOT(SwitchPage()));
    connect(ui->CBtnRegistAccount_Login, SIGNAL(clicked()), m_pRegistAccountDialog, SLOT(SLOT_PopRegistPage()));
    connect(ui->CBtnModifyPasswd_Login, SIGNAL(clicked()), m_pModifyPasswdDialog, SLOT(SLOT_PopModifyPage()));

    connect(ui->CBtnClose_Server, SIGNAL(clicked()), this, SLOT(Exit()));
    connect(ui->CBtnMinimum_Server, SIGNAL(clicked()), this, SLOT(showMinimized()));
    connect(ui->CBtnSwitch_Server, SIGNAL(clicked()), this, SLOT(SwitchPage()));
}


void CLoginWidget::mousePressEvent(QMouseEvent* pEvent)
{
    if (pEvent->button() == Qt::LeftButton)
    {
        m_bMoving = true;

        // 记录当前位置
        m_dragPosition = pEvent->globalPos() - frameGeometry().topLeft();
        pEvent->accept();
    }
}

void CLoginWidget::mouseMoveEvent(QMouseEvent* pEvent)
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


void CLoginWidget::mouseReleaseEvent(QMouseEvent* pEvent)
{
    if(pEvent->button() == Qt::LeftButton)
    {
        m_bMoving = false;
        pEvent->accept();
    }
}