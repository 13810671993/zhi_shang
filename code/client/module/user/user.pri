FORMS += \
    $$PWD/view/ui/view_regist_account_dialog.ui \
    $$PWD/view/ui/view_modify_passwd_dialog.ui

HEADERS += \
    $$PWD/user_operation_common.h \
    $$PWD/view/include/view_regist_account_dialog.h \
    $$PWD/view/include/view_modify_passwd_dialog.h \
    $$PWD/ctrl/include/ctrl_user.h

SOURCES += \
    $$PWD/view/source/view_regist_account_dialog.cpp \
    $$PWD/view/source/view_modify_passwd_dialog.cpp \
    $$PWD/ctrl/source/ctrl_user.cpp

RESOURCES += \
    $$PWD/view/user_operation.qrc
