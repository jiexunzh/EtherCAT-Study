#include "mainwindow.h"

#include <QApplication>


int main(int argc, char *argv[])
{    
    setvbuf(stdout, NULL, _IONBF, 0);  // make printf show immediately
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling); // use high DPI support
    QApplication a(argc, argv);    
    MainWindow w;
    w.show();
    return a.exec();
}
