#include "mainwindow.h"
#include <QApplication>
#include "cfwtcp.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

//    CFWTcp cfwtcp;
//    cfwtcp.New();

    return a.exec();
}
