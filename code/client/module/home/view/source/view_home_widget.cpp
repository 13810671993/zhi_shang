#include "view_home_widget.h"
#include "ui_view_home_widget.h"

CHomeWidget::CHomeWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CHomeWidget)
{
    ui->setupUi(this);
}

CHomeWidget::~CHomeWidget()
{
    delete ui;
}
