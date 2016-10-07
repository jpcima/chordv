#include "mainwindow.h"
#include <QApplication>
#include <QSettings>
#include <QDebug>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setOrganizationName("IGNU");
    a.setApplicationName("ChordV");
//    a.setOrganizationDomain("ignu.com");
    QTranslator *tr=0;
    QSettings s;
    if ( s.value("InterfaceLanguage").toInt() == 1 )
    {
        tr =new QTranslator;
        tr->load(":/Lang/chordV_fr_FR.qm");
        a.installTranslator(tr);
    }
    MainWindow w;
    bool hide=false;
    foreach ( QString arg, qApp->arguments() )
    {
        if (  arg== "-t" || arg =="--test" ) hide =true;
    }
    w.setTranstator(tr);
    if ( hide ) w.hide();
    else w.show();
    return a.exec();
}
