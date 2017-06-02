/********************************************************************************
** Form generated from reading UI file 'view_main_widget.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIEW_MAIN_WIDGET_H
#define UI_VIEW_MAIN_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CMainWidget
{
public:
    QLineEdit *lineEditPort;
    QPushButton *btnConnect;
    QTextEdit *textEditSend;
    QPushButton *btnSend;
    QPushButton *btnClose;
    QLabel *labelPort;
    QLabel *labelSend;
    QLabel *labelRecv;
    QTextBrowser *textBrowserRecv;
    QLabel *labelBackground;

    void setupUi(QWidget *CMainWidget)
    {
        if (CMainWidget->objectName().isEmpty())
            CMainWidget->setObjectName(QStringLiteral("CMainWidget"));
        CMainWidget->resize(392, 300);
        lineEditPort = new QLineEdit(CMainWidget);
        lineEditPort->setObjectName(QStringLiteral("lineEditPort"));
        lineEditPort->setGeometry(QRect(90, 50, 191, 31));
        btnConnect = new QPushButton(CMainWidget);
        btnConnect->setObjectName(QStringLiteral("btnConnect"));
        btnConnect->setGeometry(QRect(300, 50, 61, 31));
        textEditSend = new QTextEdit(CMainWidget);
        textEditSend->setObjectName(QStringLiteral("textEditSend"));
        textEditSend->setGeometry(QRect(90, 100, 191, 71));
        btnSend = new QPushButton(CMainWidget);
        btnSend->setObjectName(QStringLiteral("btnSend"));
        btnSend->setGeometry(QRect(300, 140, 61, 31));
        btnClose = new QPushButton(CMainWidget);
        btnClose->setObjectName(QStringLiteral("btnClose"));
        btnClose->setGeometry(QRect(300, 230, 61, 31));
        labelPort = new QLabel(CMainWidget);
        labelPort->setObjectName(QStringLiteral("labelPort"));
        labelPort->setGeometry(QRect(30, 50, 54, 31));
        labelSend = new QLabel(CMainWidget);
        labelSend->setObjectName(QStringLiteral("labelSend"));
        labelSend->setGeometry(QRect(30, 100, 54, 31));
        labelRecv = new QLabel(CMainWidget);
        labelRecv->setObjectName(QStringLiteral("labelRecv"));
        labelRecv->setGeometry(QRect(30, 190, 54, 31));
        textBrowserRecv = new QTextBrowser(CMainWidget);
        textBrowserRecv->setObjectName(QStringLiteral("textBrowserRecv"));
        textBrowserRecv->setGeometry(QRect(90, 190, 191, 71));
        labelBackground = new QLabel(CMainWidget);
        labelBackground->setObjectName(QStringLiteral("labelBackground"));
        labelBackground->setGeometry(QRect(0, 0, 392, 300));
        labelBackground->raise();
        btnClose->raise();
        btnConnect->raise();
        btnSend->raise();
        labelPort->raise();
        labelRecv->raise();
        labelSend->raise();
        lineEditPort->raise();
        textBrowserRecv->raise();
        textEditSend->raise();

        retranslateUi(CMainWidget);

        QMetaObject::connectSlotsByName(CMainWidget);
    } // setupUi

    void retranslateUi(QWidget *CMainWidget)
    {
        CMainWidget->setWindowTitle(QApplication::translate("CMainWidget", "CMainWidget", 0));
        btnConnect->setText(QApplication::translate("CMainWidget", "\350\277\236    \346\216\245", 0));
        btnSend->setText(QApplication::translate("CMainWidget", "\345\217\221    \351\200\201", 0));
        btnClose->setText(QApplication::translate("CMainWidget", "\345\205\263    \351\227\255", 0));
        labelPort->setText(QApplication::translate("CMainWidget", "\347\253\257    \345\217\243", 0));
        labelSend->setText(QApplication::translate("CMainWidget", "\345\217\221\351\200\201\345\206\205\345\256\271", 0));
        labelRecv->setText(QApplication::translate("CMainWidget", "\346\216\245\346\224\266\345\206\205\345\256\271", 0));
        labelBackground->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class CMainWidget: public Ui_CMainWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIEW_MAIN_WIDGET_H
