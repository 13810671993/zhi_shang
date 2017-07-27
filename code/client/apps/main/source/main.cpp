#include <QApplication>
#include <QTextCodec>
#include "page_manager/include/page_manager.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

    CPageMgr pageMgr(&a);
    pageMgr.StartLogin();

    return a.exec();
}
