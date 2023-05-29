#include "glwidget.h"
#include "dialog.h"
#include "mainwindow.h"
#include <QApplication>
#define WindowWidth 640
#define WindowHeight 480
int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}