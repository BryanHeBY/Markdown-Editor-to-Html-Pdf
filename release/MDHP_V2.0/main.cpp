#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QString new_open;
    if(argc==2)new_open=argv[1];
    MainWindow *w=new MainWindow(NULL,new_open);
    w->show();
    return a.exec();
}
