/********************************************************************************
** Form generated from reading UI file 'view_user_operation_dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIEW_USER_OPERATION_DIALOG_H
#define UI_VIEW_USER_OPERATION_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_CUserOperationDialog
{
public:

    void setupUi(QDialog *CUserOperationDialog)
    {
        if (CUserOperationDialog->objectName().isEmpty())
            CUserOperationDialog->setObjectName(QStringLiteral("CUserOperationDialog"));
        CUserOperationDialog->resize(400, 300);

        retranslateUi(CUserOperationDialog);

        QMetaObject::connectSlotsByName(CUserOperationDialog);
    } // setupUi

    void retranslateUi(QDialog *CUserOperationDialog)
    {
        CUserOperationDialog->setWindowTitle(QApplication::translate("CUserOperationDialog", "Dialog", 0));
    } // retranslateUi

};

namespace Ui {
    class CUserOperationDialog: public Ui_CUserOperationDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIEW_USER_OPERATION_DIALOG_H
