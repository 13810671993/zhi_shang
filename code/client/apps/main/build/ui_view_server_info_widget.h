/********************************************************************************
** Form generated from reading UI file 'view_server_info_widget.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIEW_SERVER_INFO_WIDGET_H
#define UI_VIEW_SERVER_INFO_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CServerInfoWidget
{
public:
    QLabel *CLblBackgroundUp;
    QLabel *CLblBackgroundDown;
    QComboBox *CCmbIp;
    QLineEdit *CLedPort;
    QPushButton *CBtnConfirm;
    QPushButton *CBtnCancel;
    QLabel *CLblIp;
    QLabel *CLblPort;
    QPushButton *CBtnClose;
    QPushButton *CBtnSwitch;
    QPushButton *CBtnMinimum;

    void setupUi(QWidget *CServerInfoWidget)
    {
        if (CServerInfoWidget->objectName().isEmpty())
            CServerInfoWidget->setObjectName(QStringLiteral("CServerInfoWidget"));
        CServerInfoWidget->resize(400, 300);
        CLblBackgroundUp = new QLabel(CServerInfoWidget);
        CLblBackgroundUp->setObjectName(QStringLiteral("CLblBackgroundUp"));
        CLblBackgroundUp->setGeometry(QRect(0, 0, 400, 150));
        CLblBackgroundDown = new QLabel(CServerInfoWidget);
        CLblBackgroundDown->setObjectName(QStringLiteral("CLblBackgroundDown"));
        CLblBackgroundDown->setGeometry(QRect(0, 150, 400, 150));
        CCmbIp = new QComboBox(CServerInfoWidget);
        CCmbIp->setObjectName(QStringLiteral("CCmbIp"));
        CCmbIp->setGeometry(QRect(100, 160, 200, 30));
        CLedPort = new QLineEdit(CServerInfoWidget);
        CLedPort->setObjectName(QStringLiteral("CLedPort"));
        CLedPort->setGeometry(QRect(100, 190, 200, 30));
        CBtnConfirm = new QPushButton(CServerInfoWidget);
        CBtnConfirm->setObjectName(QStringLiteral("CBtnConfirm"));
        CBtnConfirm->setGeometry(QRect(100, 250, 80, 30));
        CBtnCancel = new QPushButton(CServerInfoWidget);
        CBtnCancel->setObjectName(QStringLiteral("CBtnCancel"));
        CBtnCancel->setGeometry(QRect(220, 250, 80, 30));
        CLblIp = new QLabel(CServerInfoWidget);
        CLblIp->setObjectName(QStringLiteral("CLblIp"));
        CLblIp->setGeometry(QRect(50, 160, 50, 30));
        CLblPort = new QLabel(CServerInfoWidget);
        CLblPort->setObjectName(QStringLiteral("CLblPort"));
        CLblPort->setGeometry(QRect(50, 190, 50, 30));
        CBtnClose = new QPushButton(CServerInfoWidget);
        CBtnClose->setObjectName(QStringLiteral("CBtnClose"));
        CBtnClose->setGeometry(QRect(376, 10, 16, 16));
        CBtnSwitch = new QPushButton(CServerInfoWidget);
        CBtnSwitch->setObjectName(QStringLiteral("CBtnSwitch"));
        CBtnSwitch->setGeometry(QRect(328, 10, 16, 16));
        CBtnMinimum = new QPushButton(CServerInfoWidget);
        CBtnMinimum->setObjectName(QStringLiteral("CBtnMinimum"));
        CBtnMinimum->setGeometry(QRect(352, 10, 16, 16));

        retranslateUi(CServerInfoWidget);

        QMetaObject::connectSlotsByName(CServerInfoWidget);
    } // setupUi

    void retranslateUi(QWidget *CServerInfoWidget)
    {
        CServerInfoWidget->setWindowTitle(QApplication::translate("CServerInfoWidget", "Form", 0));
        CLblBackgroundUp->setText(QString());
        CLblBackgroundDown->setText(QString());
        CBtnConfirm->setText(QString());
        CBtnCancel->setText(QString());
        CLblIp->setText(QString());
        CLblPort->setText(QString());
        CBtnClose->setText(QString());
        CBtnSwitch->setText(QString());
        CBtnMinimum->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class CServerInfoWidget: public Ui_CServerInfoWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIEW_SERVER_INFO_WIDGET_H
