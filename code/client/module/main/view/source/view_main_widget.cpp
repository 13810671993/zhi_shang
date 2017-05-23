#include "main/main_common.h"
#include "ui_view_main_widget.h"

CMainWidget::CMainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CMainWidget)
{
    ui->setupUi(this);
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
