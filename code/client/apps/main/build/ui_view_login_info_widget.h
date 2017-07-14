/********************************************************************************
** Form generated from reading UI file 'view_login_info_widget.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIEW_LOGIN_INFO_WIDGET_H
#define UI_VIEW_LOGIN_INFO_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CLoginInfoWidget
{
public:
    QLabel *CLblBackgroundUp;
    QLabel *CLblBackgroundDown;
    QComboBox *CCmbUser;
    QLineEdit *CLedPasswd;
    QLabel *CLblUser;
    QLabel *CLblPasswd;
    QPushButton *CBtnSwitch;
    QPushButton *CBtnMinimum;
    QPushButton *CBtnClose;
    QCheckBox *CChkRememberPasswd;
    QCheckBox *CChkAutoLogin;
    QPushButton *CBtnLogin;

    void setupUi(QWidget *CLoginInfoWidget)
    {
        if (CLoginInfoWidget->objectName().isEmpty())
            CLoginInfoWidget->setObjectName(QStringLiteral("CLoginInfoWidget"));
        CLoginInfoWidget->resize(400, 300);
        CLblBackgroundUp = new QLabel(CLoginInfoWidget);
        CLblBackgroundUp->setObjectName(QStringLiteral("CLblBackgroundUp"));
        CLblBackgroundUp->setGeometry(QRect(0, 0, 400, 150));
        CLblBackgroundDown = new QLabel(CLoginInfoWidget);
        CLblBackgroundDown->setObjectName(QStringLiteral("CLblBackgroundDown"));
        CLblBackgroundDown->setGeometry(QRect(0, 150, 400, 150));
        CCmbUser = new QComboBox(CLoginInfoWidget);
        CCmbUser->setObjectName(QStringLiteral("CCmbUser"));
        CCmbUser->setGeometry(QRect(100, 160, 200, 30));
        CLedPasswd = new QLineEdit(CLoginInfoWidget);
        CLedPasswd->setObjectName(QStringLiteral("CLedPasswd"));
        CLedPasswd->setGeometry(QRect(100, 190, 200, 30));
        CLblUser = new QLabel(CLoginInfoWidget);
        CLblUser->setObjectName(QStringLiteral("CLblUser"));
        CLblUser->setGeometry(QRect(50, 160, 50, 30));
        CLblPasswd = new QLabel(CLoginInfoWidget);
        CLblPasswd->setObjectName(QStringLiteral("CLblPasswd"));
        CLblPasswd->setGeometry(QRect(50, 190, 50, 30));
        CBtnSwitch = new QPushButton(CLoginInfoWidget);
        CBtnSwitch->setObjectName(QStringLiteral("CBtnSwitch"));
        CBtnSwitch->setGeometry(QRect(328, 10, 16, 16));
        CBtnMinimum = new QPushButton(CLoginInfoWidget);
        CBtnMinimum->setObjectName(QStringLiteral("CBtnMinimum"));
        CBtnMinimum->setGeometry(QRect(352, 10, 16, 16));
        CBtnClose = new QPushButton(CLoginInfoWidget);
        CBtnClose->setObjectName(QStringLiteral("CBtnClose"));
        CBtnClose->setGeometry(QRect(376, 10, 16, 16));
        CChkRememberPasswd = new QCheckBox(CLoginInfoWidget);
        CChkRememberPasswd->setObjectName(QStringLiteral("CChkRememberPasswd"));
        CChkRememberPasswd->setGeometry(QRect(100, 220, 100, 30));
        CChkAutoLogin = new QCheckBox(CLoginInfoWidget);
        CChkAutoLogin->setObjectName(QStringLiteral("CChkAutoLogin"));
        CChkAutoLogin->setGeometry(QRect(200, 220, 100, 30));
        CBtnLogin = new QPushButton(CLoginInfoWidget);
        CBtnLogin->setObjectName(QStringLiteral("CBtnLogin"));
        CBtnLogin->setGeometry(QRect(100, 250, 200, 30));

        retranslateUi(CLoginInfoWidget);

        QMetaObject::connectSlotsByName(CLoginInfoWidget);
    } // setupUi

    void retranslateUi(QWidget *CLoginInfoWidget)
    {
        CLoginInfoWidget->setWindowTitle(QApplication::translate("CLoginInfoWidget", "Form", 0));
        CLblBackgroundUp->setText(QString());
        CLblBackgroundDown->setText(QString());
        CLblUser->setText(QString());
        CLblPasswd->setText(QString());
        CBtnSwitch->setText(QString());
        CBtnMinimum->setText(QString());
        CBtnClose->setText(QString());
        CChkRememberPasswd->setText(QString());
        CChkAutoLogin->setText(QString());
        CBtnLogin->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class CLoginInfoWidget: public Ui_CLoginInfoWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIEW_LOGIN_INFO_WIDGET_H
