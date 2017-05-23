#include "main/main_common.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CMainWidget w;
    w.show();

    return a.exec();
}
