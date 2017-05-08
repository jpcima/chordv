#include "mainwindow.h"
#include <QApplication>
#include <QSettings>
#include <QDebug>
#include <QTranslator>
#include <QSqlDatabase>
#include <QFileInfo>
#include <QMessageBox>
#include <version.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setOrganizationName("IGNU");
    a.setApplicationName("ChordV");
    a.setApplicationVersion(QString("%1/%2").arg(VERSION).arg(FULLVERSION));


    QTranslator *tr=0;
    QSettings s;
    if ( s.value("InterfaceLanguage").toInt() == 1 )
    {
        tr =new QTranslator;
        tr->load(":/Lang/chordV_fr_FR.qm");
        a.installTranslator(tr);
    }
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    QFileInfo fi(s.fileName());
    QString databasefile=fi.absolutePath()+"/Chord.db";
    QFileInfo fi2(databasefile);
    if ( ! fi2.exists() || fi2.size()==0)
    {
        QMessageBox msgBox;
        msgBox.setText(QObject::tr("Database %1 not found. You will not be able to design chords !").arg(databasefile));
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.exec();
    }
    else
    {
        db.setDatabaseName(databasefile);
        db.open();
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
