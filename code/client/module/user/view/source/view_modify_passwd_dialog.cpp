#include "user/user_operation_common.h"
#include "ui_view_modify_passwd_dialog.h"

CModifyPasswdDialog::CModifyPasswdDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CModifyPasswdDialog)
    , m_pParentWidget(parent)
    , m_bPageExist(FALSE)
{
    ui->setupUi(this);

    InitWidget();
    InitWindow();
    InitStyly();
    BindSignals();
}

CModifyPasswdDialog::~CModifyPasswdDialog()
{
    delete ui;
}

void CModifyPasswdDialog::SLOT_PopModifyPage()
{
    if (!m_bPageExist)
    {
        move(m_pParentWidget->pos());
        show();
        m_bPageExist = TRUE;
    }
}

void CModifyPasswdDialog::SLOT_GetUserName(QString qstrUserName)
{
    if (qstrUserName == "")
        return ;
    QRegExp regexUserName("[a-zA-Z0-9_]{6,31}");
    if (!regexUserName.exactMatch(qstrUserName))
    {
        ui->CLblUserError_Modify->setStyleSheet("color: red;");
        ui->CLblUserError_Modify->setText(tr("length greater 6"));
        m_qstrUserName.clear();
    }
    else
    {
        ui->CLblUserError_Modify->setStyleSheet("color: green;");
        ui->CLblUserError_Modify->setText(tr("correct"));
        m_qstrUserName = qstrUserName;
    }
}

void CModifyPasswdDialog::SLOT_GetOldPasswd(QString qstrPasswd)
{
    if (qstrPasswd == "")
        return ;
    QRegExp regexPasswd("[^\u4E00-\u9FA5]{6,15}");
    if (!regexPasswd.exactMatch(qstrPasswd))
    {
        ui->CLblOldPasswdError_Modify->setStyleSheet("color: red;");
        ui->CLblOldPasswdError_Modify->setText(tr("passwd error"));
        m_qstrOldPasswd.clear();
    }
    else
    {
        ui->CLblOldPasswdError_Modify->setStyleSheet("color: green;");
        ui->CLblOldPasswdError_Modify->setText(tr("correct"));
        m_qstrOldPasswd = qstrPasswd;
    }
}

void CModifyPasswdDialog::SLOT_GetNewPasswd(QString qstrPasswd)
{
    if (qstrPasswd == "")
        return ;
    QRegExp regexPasswd("[^\u4E00-\u9FA5]{6,15}");
    if (!regexPasswd.exactMatch(qstrPasswd))
    {
        ui->CLblNewPasswdError_Modify->setStyleSheet("color: red;");
        ui->CLblNewPasswdError_Modify->setText(tr("passwd error"));
        m_qstrNewPasswd.clear();
    }
    else
    {
        ui->CLblNewPasswdError_Modify->setStyleSheet("color: green;");
        ui->CLblNewPasswdError_Modify->setText(tr("correct"));
    }
}

void CModifyPasswdDialog::SLOT_GetSecondNewPasswd(QString qstrPasswd)
{
    if (qstrPasswd == "")
        return ;
    if (ui->CLedNewPasswd_Modify->text() == qstrPasswd)
    {
        ui->CLblNewPasswdAgainError_Modify->setStyleSheet("color: green;");
        ui->CLblNewPasswdAgainError_Modify->setText(tr("correct"));
    }
    else
    {
        ui->CLblNewPasswdAgainError_Modify->setStyleSheet("color: red;");
        ui->CLblNewPasswdAgainError_Modify->setText(tr("passwd different"));
        m_qstrNewPasswd.clear();
    }
}

void CModifyPasswdDialog::SLOT_FinishedInputNewPasswd()
{
    if (ui->CLedNewPasswdAgain_Modify->text() == "")
        return ;
    if (ui->CLedNewPasswd_Modify->text() == ui->CLedNewPasswdAgain_Modify->text())
    {
        ui->CLblNewPasswdAgainError_Modify->setStyleSheet("color: green;");
        ui->CLblNewPasswdAgainError_Modify->setText(tr("correct"));
        m_qstrNewPasswd = ui->CLedNewPasswdAgain_Modify->text();
    }
    else
    {
        ui->CLblNewPasswdAgainError_Modify->setStyleSheet("color: red;");
        ui->CLblNewPasswdAgainError_Modify->setText(tr("passwd different"));
        m_qstrNewPasswd.clear();
    }
}

void CModifyPasswdDialog::SLOT_ModifyPasswd()
{
    emit SIGNAL_Connect2Server();
    T_APP_MODIFY_PASSWD_REQ tReq = {0};
    tReq.u64Context = 1;
    memcpy(tReq.acUserName, m_qstrUserName.toStdString().data(), m_qstrUserName.length());
    memcpy(tReq.acOldPasswd, m_qstrOldPasswd.toStdString().data(), m_qstrOldPasswd.length());
    memcpy(tReq.acNewPasswd, m_qstrNewPasswd.toStdString().data(), m_qstrNewPasswd.length());
    CNetwork::GetInstance()->PostMessage(E_APP_MSG_MODIFY_PASSWD_REQ, (CHAR*)&tReq, sizeof(tReq));
}

VOID CModifyPasswdDialog::InitWidget()
{
    ui->CBtnCancel_Modify->setText(tr("cancel"));
    ui->CBtnModify_Modify->setText(tr("modify"));
    ui->CLedUser_Modify->setPlaceholderText(tr("user name"));
    ui->CLedOldPasswd_Modify->setPlaceholderText(tr("old passwd"));
    ui->CLedNewPasswd_Modify->setPlaceholderText(tr("new passwd"));
    ui->CLedNewPasswdAgain_Modify->setPlaceholderText(tr("new passwd again"));
    QRegExp regexUserName("[a-zA-Z0-9_]{6,31}");
    QValidator* pValidatorUser = new QRegExpValidator(regexUserName, this);
    ui->CLedUser_Modify->setValidator(pValidatorUser);
    QRegExp regexPasswd("[^\u4E00-\u9FA5]{6,15}");
    QValidator* pValidatorPasswd = new QRegExpValidator(regexPasswd, this);
    ui->CLedOldPasswd_Modify->setValidator(pValidatorPasswd);
    ui->CLedNewPasswd_Modify->setValidator(pValidatorPasswd);
    ui->CLedNewPasswdAgain_Modify->setValidator(pValidatorPasswd);

    // http://blog.sina.com.cn/s/blog_a0e483280102vizf.html
    // 无右键菜单
    ui->CLedUser_Modify->setContextMenuPolicy(Qt::NoContextMenu);
    ui->CLedOldPasswd_Modify->setContextMenuPolicy(Qt::NoContextMenu);
    ui->CLedNewPasswd_Modify->setContextMenuPolicy(Qt::NoContextMenu);
    ui->CLedNewPasswdAgain_Modify->setContextMenuPolicy(Qt::NoContextMenu);
    // 设置密码隐藏
    ui->CLedOldPasswd_Modify->setEchoMode(QLineEdit::Password);
    ui->CLedNewPasswd_Modify->setEchoMode(QLineEdit::Password);
    ui->CLedNewPasswdAgain_Modify->setEchoMode(QLineEdit::Password);
}

VOID CModifyPasswdDialog::InitWindow()
{
    // 隐藏边框
    setWindowOpacity(1);
    setWindowFlags(Qt::Tool | Qt::WindowStaysOnTopHint | Qt::X11BypassWindowManagerHint | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
}

VOID CModifyPasswdDialog::InitStyly()
{
    QFile styleSheet(":/user_operation/resource/modify_passwd.qss");
    if (styleSheet.open(QFile::ReadOnly))
    {
        this->setStyleSheet(styleSheet.readAll());
        styleSheet.close();
    }

}

VOID CModifyPasswdDialog::BindSignals()
{
    connect(ui->CBtnCancel_Modify, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->CLedUser_Modify, SIGNAL(textEdited(QString)), this, SLOT(SLOT_GetUserName(QString)));
    connect(ui->CLedOldPasswd_Modify, SIGNAL(textEdited(QString)), this, SLOT(SLOT_GetOldPasswd(QString)));
    connect(ui->CLedNewPasswd_Modify, SIGNAL(textEdited(QString)), this, SLOT(SLOT_GetNewPasswd(QString)));
    connect(ui->CLedNewPasswd_Modify, SIGNAL(editingFinished()), this, SLOT(SLOT_FinishedInputNewPasswd()));
    connect(ui->CLedNewPasswdAgain_Modify, SIGNAL(textChanged(QString)), this, SLOT(SLOT_GetSecondNewPasswd(QString)));
    connect(ui->CLedNewPasswdAgain_Modify, SIGNAL(editingFinished()), this, SLOT(SLOT_FinishedInputNewPasswd()));
    connect(ui->CBtnModify_Modify, SIGNAL(clicked()), this, SLOT(SLOT_ModifyPasswd()));
    connect(this, SIGNAL(SIGNAL_Connect2Server()), m_pParentWidget, SLOT(SLOT_Connect2Server()));
}

void CModifyPasswdDialog::mousePressEvent(QMouseEvent* pEvent)
{
    if (pEvent->button() == Qt::LeftButton)
    {
        m_bMoving = true;

        // 记录当前位置
        m_dragPosition = pEvent->globalPos() - frameGeometry().topLeft();
        pEvent->accept();
    }
}

void CModifyPasswdDialog::mouseReleaseEvent(QMouseEvent* pEvent)
{
    if(pEvent->button() == Qt::LeftButton)
    {
        m_bMoving = false;
        pEvent->accept();
    }
}

void CModifyPasswdDialog::mouseMoveEvent(QMouseEvent* pEvent)
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

void CModifyPasswdDialog::closeEvent(QCloseEvent *)
{
    m_bPageExist = FALSE;
}
