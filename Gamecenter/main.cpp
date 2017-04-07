#include "mainwindow.h"
#include "spider.h"
#include <game2048.h>
#include <QApplication>
#include <QDesktopWidget>






int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.show();
    Spider s;
    Game2048 g;




    return a.exec();
}
