#include "mainwindow.h"
#include <QApplication>
#include <QSettings>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setOrganizationName("IGNU");
    a.setApplicationName("ChordV");
//    a.setOrganizationDomain("ignu.com");
    QSettings s;
    qDebug()<<s.value("File");
    MainWindow w;
    w.show();
    return a.exec();
}
