#include <QApplication>
#include <QTextCodec>
#include "login/login_common.h"
#include "network/network_common.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

    CLoginWidget ab(0);
    ab.show();


    return a.exec();
}
