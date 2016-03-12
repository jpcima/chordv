#include "mainwindow.h"
#include <QApplication>
#include <QSettings>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setOrganizationName("IGNU");
    a.setApplicationName("ChordV");
//    a.setOrganizationDomain("ignu.com");
    MainWindow w;
    w.show();
    return a.exec();
}
