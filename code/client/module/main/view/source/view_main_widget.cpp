#include "main/main_common.h"
#include "ui_view_main_widget.h"

CMainWidget::CMainWidget(CNetwork* pNetwork, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CMainWidget),
    m_pNetwork(pNetwork)
{
    ui->setupUi(this);

    // 隐藏边框
    setWindowOpacity(1);
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    BindSignals();

    // 读取qss
    QFile file(":/resource/main.qss");
    file.open(QFile::ReadOnly);
    if(file.isOpen())
    {
        setStyleSheet(QString(file.readAll()));
        file.close();
    }
}

CMainWidget::~CMainWidget()
{
    delete ui;
}

void CMainWidget::SLOT_ShowRecvMessage(QString qstrMessage)
{
    ui->textBrowserRecv->setText(qstrMessage);
}

void CMainWidget::SLOT_GetSendMessage()
{
    // 1. 获取要发送的信息
    QString qstrSendMessage;
    qstrSendMessage = ui->textEditSend->toPlainText();
    if (qstrSendMessage == "")
    {
        emit m_pNetwork->SIGNAL_ShowRecvMessage(QString::fromUtf8("发送信息不能为空 "));
    }
    else
    {
        emit m_pNetwork->SIGNAL_SendMessage(qstrSendMessage);
    }
}

void CMainWidget::SLOT_CloseMainWidget()
{
    close();
}

void CMainWidget::BindSignals()
{
    connect(ui->lineEditPort, SIGNAL(textEdited(QString)), m_pNetwork, SLOT(SLOT_PortEditFinished(QString)));
    connect(m_pNetwork, SIGNAL(SIGNAL_ShowRecvMessage(QString)), this, SLOT(SLOT_ShowRecvMessage(QString)));
    connect(ui->btnConnect, SIGNAL(clicked()), m_pNetwork, SLOT(SLOT_Connect()));
    connect(m_pNetwork, SIGNAL(SIGNAL_SendMessage(QString)), m_pNetwork, SLOT(SLOT_SendMessage(QString)));
    connect(ui->btnClose, SIGNAL(clicked()), this, SLOT(SLOT_CloseMainWidget()));
    connect(ui->btnSend, SIGNAL(clicked()), this, SLOT(SLOT_GetSendMessage()));
}
