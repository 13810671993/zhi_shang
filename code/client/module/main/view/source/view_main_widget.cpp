#include "main/main_common.h"
#include "ui_view_main_widget.h"

CMainWidget::CMainWidget(CNetwork* pNetwork, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CMainWidget),
    m_pNetwork(pNetwork)
{
    ui->setupUi(this);

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

void CMainWidget::DoShowRecvMessage(QString qstrMessage)
{
    ui->textBrowserRecv->setText(qstrMessage);
}

void CMainWidget::DoGetSendMessage()
{
    // 1. 获取要发送的信息
    QString qstrSendMessage;
    qstrSendMessage = ui->textEditSend->toPlainText();
    if (qstrSendMessage == "")
    {
        emit m_pNetwork->ShowRecvMessage(QString("发送信息不能为空."));
    }
    else
    {
        emit m_pNetwork->SendMessage(qstrSendMessage);
    }
}

void CMainWidget::DoCloseMainWidget()
{
    close();
}

void CMainWidget::BindSignals()
{
    connect(ui->lineEditPort, SIGNAL(textEdited(QString)), m_pNetwork, SLOT(PortEditFinished(QString)));
    connect(m_pNetwork, SIGNAL(ShowRecvMessage(QString)), this, SLOT(DoShowRecvMessage(QString)));
    connect(ui->btnConnect, SIGNAL(clicked()), m_pNetwork, SLOT(DoConnect()));
    connect(m_pNetwork, SIGNAL(SendMessage(QString)), m_pNetwork, SLOT(DoSendMessage(QString)));
    connect(ui->btnClose, SIGNAL(clicked()), this, SLOT(DoCloseMainWidget()));
}
