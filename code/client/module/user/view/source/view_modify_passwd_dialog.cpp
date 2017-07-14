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
    QRegExp regexUserName("[a-zA-Z0-9_]{6,30}");
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

void CModifyPasswdDialog::SLOT_GetPasswd(QString qstrPasswd)
{
    QRegExp regexPasswd("[^\u4E00-\u9FA5]{6,20}");
    if (!regexPasswd.exactMatch(qstrPasswd))
    {
        ui->CLblPasswdError_Modify->setStyleSheet("color: red;");
        ui->CLblPasswdError_Modify->setText(tr("passwd error"));
        m_qstrPasswd.clear();
    }
    else
    {
        ui->CLblPasswdError_Modify->setStyleSheet("color: green;");
        ui->CLblPasswdError_Modify->setText(tr("correct"));
    }
}

void CModifyPasswdDialog::SLOT_GetSecondpasswd(QString qstrPasswd)
{
    if (ui->CLedPasswd_Modify->text() == qstrPasswd)
    {
        ui->CLblPasswdAgainError_Modify->setStyleSheet("color: green;");
        ui->CLblPasswdAgainError_Modify->setText(tr("correct"));
    }
    else
    {
        ui->CLblPasswdAgainError_Modify->setStyleSheet("color: red;");
        ui->CLblPasswdAgainError_Modify->setText(tr("passwd different"));
        m_qstrPasswd.clear();
    }
}

void CModifyPasswdDialog::SLOT_FinishedInputPasswd()
{
    if (ui->CLedPasswd_Modify->text() == ui->CLedPasswdAgain_Modify->text())
    {
        ui->CLblPasswdAgainError_Modify->setStyleSheet("color: green;");
        ui->CLblPasswdAgainError_Modify->setText(tr("correct"));
        m_qstrPasswd = ui->CLedPasswdAgain_Modify->text();
    }
    else
    {
        ui->CLblPasswdAgainError_Modify->setStyleSheet("color: red;");
        ui->CLblPasswdAgainError_Modify->setText(tr("passwd different"));
        m_qstrPasswd.clear();
    }
}

VOID CModifyPasswdDialog::InitWidget()
{
    ui->CBtnCancel_Modify->setText(tr("cancel"));
    ui->CBtnConfirm_Modify->setText(tr("confirm"));
    ui->CLedUser_Modify->setPlaceholderText(tr("user name"));
    ui->CLedPasswd_Modify->setPlaceholderText(tr("passwd"));
    ui->CLedPasswdAgain_Modify->setPlaceholderText(tr("passwd again"));
    QRegExp regexUserName("[a-zA-Z0-9_]{6,30}");
    QValidator* pValidatorUser = new QRegExpValidator(regexUserName, this);
    ui->CLedUser_Modify->setValidator(pValidatorUser);
    QRegExp regexPasswd("[^\u4E00-\u9FA5]{6,20}");
    QValidator* pValidatorPasswd = new QRegExpValidator(regexPasswd, this);
    ui->CLedPasswd_Modify->setValidator(pValidatorPasswd);
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
    connect(ui->CLedPasswd_Modify, SIGNAL(textEdited(QString)), this, SLOT(SLOT_GetPasswd(QString)));
    connect(ui->CLedPasswd_Modify, SIGNAL(editingFinished()), this, SLOT(SLOT_FinishedInputPasswd()));
    connect(ui->CLedPasswdAgain_Modify, SIGNAL(textChanged(QString)), this, SLOT(SLOT_GetSecondpasswd(QString)));
    connect(ui->CLedPasswdAgain_Modify, SIGNAL(editingFinished()), this, SLOT(SLOT_FinishedInputPasswd()));
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
