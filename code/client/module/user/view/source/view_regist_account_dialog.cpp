#include "user/user_operation_common.h"
#include "ui_view_regist_account_dialog.h"

CRegistAccountDialog::CRegistAccountDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CRegistAccountDialog)
    , m_pParentWidget(parent)
    , m_bPageExist(FALSE)
    , m_bSex(TRUE)
{
    ui->setupUi(this);

    InitWidget();
    InitWindow();
    InitStyly();
    BindSignals();
}

CRegistAccountDialog::~CRegistAccountDialog()
{
    delete ui;
}

void CRegistAccountDialog::SLOT_PopRegistPage()
{
    if (!m_bPageExist)
    {
        move(m_pParentWidget->pos());
        show();
        m_bPageExist = TRUE;
    }
}

void CRegistAccountDialog::SLOT_GetUserName(QString qstrUserName)
{
    QRegExp regexUserName("[a-zA-Z0-9_]{6,30}");
    if (!regexUserName.exactMatch(qstrUserName))
    {
        ui->CLblUserError_Regist->setStyleSheet("color: red;");
        ui->CLblUserError_Regist->setText(tr("length greater 6"));
        m_qstrUserName.clear();
    }
    else
    {
        ui->CLblUserError_Regist->setStyleSheet("color: green;");
        ui->CLblUserError_Regist->setText(tr("correct"));
        m_qstrUserName = qstrUserName;
    }
}

void CRegistAccountDialog::SLOT_GetPasswd(QString qstrPasswd)
{
    QRegExp regexPasswd("[^\u4E00-\u9FA5]{6,20}");
    if (!regexPasswd.exactMatch(qstrPasswd))
    {
        ui->CLblPasswdError_Regist->setStyleSheet("color: red;");
        ui->CLblPasswdError_Regist->setText(tr("passwd error"));
        m_qstrPasswd.clear();
    }
    else
    {
        ui->CLblPasswdError_Regist->setStyleSheet("color: green;");
        ui->CLblPasswdError_Regist->setText(tr("correct"));
    }
}

void CRegistAccountDialog::SLOT_GetSecondpasswd(QString qstrPasswd)
{
    if (ui->CLedPasswd_Regist->text() == qstrPasswd)
    {
        ui->CLblPasswdAgainError_Regist->setStyleSheet("color: green;");
        ui->CLblPasswdAgainError_Regist->setText(tr("correct"));
        m_qstrPasswd = qstrPasswd;
    }
    else
    {
        ui->CLblPasswdAgainError_Regist->setStyleSheet("color: red;");
        ui->CLblPasswdAgainError_Regist->setText(tr("passwd different"));
        m_qstrPasswd.clear();
    }
}

void CRegistAccountDialog::SLOT_FinishedInputPasswd()
{
    if (ui->CLedPasswd_Regist->text() == ui->CLedPasswdAgain_Regist->text())
    {
        ui->CLblPasswdAgainError_Regist->setStyleSheet("color: green;");
        ui->CLblPasswdAgainError_Regist->setText(tr("correct"));
        m_qstrPasswd = ui->CLedPasswdAgain_Regist->text();
    }
    else
    {
        ui->CLblPasswdAgainError_Regist->setStyleSheet("color: red;");
        ui->CLblPasswdAgainError_Regist->setText(tr("passwd different"));
        m_qstrPasswd.clear();
    }
}

void CRegistAccountDialog::SLOT_GetSex(bool bSex)
{
    m_bSex = bSex;
}

VOID CRegistAccountDialog::InitWidget()
{
    ui->CBtnCancel_Regist->setText(tr("cancel"));
    ui->CBtnConfirm_Regist->setText(tr("confirm"));
    ui->CLedUser_Regist->setPlaceholderText(tr("user name"));
    ui->CLedPasswd_Regist->setPlaceholderText(tr("passwd"));
    ui->CLedPasswdAgain_Regist->setPlaceholderText(tr("passwd again"));
    ui->CRbtnMan->setChecked(TRUE);
    QRegExp regexUserName("[a-zA-Z0-9_]{6,30}");
    QValidator* pValidatorUser = new QRegExpValidator(regexUserName, this);
    ui->CLedUser_Regist->setValidator(pValidatorUser);
    QRegExp regexPasswd("[^\u4E00-\u9FA5]{6,20}");
    QValidator* pValidatorPasswd = new QRegExpValidator(regexPasswd, this);
    ui->CLedPasswd_Regist->setValidator(pValidatorPasswd);
}

VOID CRegistAccountDialog::InitWindow()
{
    // 隐藏边框
    setWindowOpacity(1);
    setWindowFlags(Qt::Tool | Qt::WindowStaysOnTopHint | Qt::X11BypassWindowManagerHint | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
}

VOID CRegistAccountDialog::InitStyly()
{
    QFile styleSheet(":/user_operation/resource/regist_account.qss");
    if (styleSheet.open(QFile::ReadOnly))
    {
        this->setStyleSheet(styleSheet.readAll());
        styleSheet.close();
    }
}

VOID CRegistAccountDialog::BindSignals()
{
    connect(ui->CBtnCancel_Regist, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->CLedUser_Regist, SIGNAL(textEdited(QString)), this, SLOT(SLOT_GetUserName(QString)));
    connect(ui->CLedPasswd_Regist, SIGNAL(textEdited(QString)), this, SLOT(SLOT_GetPasswd(QString)));
    connect(ui->CLedPasswd_Regist, SIGNAL(editingFinished()), this, SLOT(SLOT_FinishedInputPasswd()));
    connect(ui->CLedPasswdAgain_Regist, SIGNAL(textChanged(QString)), this, SLOT(SLOT_GetSecondpasswd(QString)));
    connect(ui->CLedPasswdAgain_Regist, SIGNAL(editingFinished()), this, SLOT(SLOT_FinishedInputPasswd()));
    connect(ui->CRbtnMan, SIGNAL(clicked(bool)), this, SLOT(SLOT_GetSex(bool)));
}


void CRegistAccountDialog::mousePressEvent(QMouseEvent* pEvent)
{
    if (pEvent->button() == Qt::LeftButton)
    {
        m_bMoving = true;

        // 记录当前位置
        m_dragPosition = pEvent->globalPos() - frameGeometry().topLeft();
        pEvent->accept();
    }
}

void CRegistAccountDialog::mouseReleaseEvent(QMouseEvent* pEvent)
{
    if(pEvent->button() == Qt::LeftButton)
    {
        m_bMoving = false;
        pEvent->accept();
    }
}

void CRegistAccountDialog::mouseMoveEvent(QMouseEvent* pEvent)
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

void CRegistAccountDialog::closeEvent(QCloseEvent *)
{
    m_bPageExist = FALSE;
}
