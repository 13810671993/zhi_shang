#include "main/main_common.h"
#include "network/network_common.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 启动网络资源
    CNetwork* pNetwork = new CNetwork();

    CMainWidget w(pNetwork);
    w.show();

    return a.exec();
}
