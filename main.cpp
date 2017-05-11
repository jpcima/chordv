#include "mainwindow.h"
#include <QApplication>
#include <QSettings>
#include <QDebug>
#include <QTranslator>
#include <QSqlDatabase>
#include <QFileInfo>
#include <QMessageBox>
#include <QDir>
#include <version.h>
#include <dialogconfiguration.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setOrganizationName("IGNU");
    a.setApplicationName("ChordV");
    a.setApplicationVersion(QString("%1/%2").arg(VERSION).arg(FULLVERSION));

    // Installation of DataBase include in ressource and chordV-fr file
    // in .config/IGNU/directory

    QSettings s;

    QString filename= s.fileName();
    QFileInfo fi(filename);
    QString databasefile=fi.absolutePath()+"/Chord.db";
    QString langfrfilename=fi.absolutePath()+"/Languages/Français/fr.qm";
    QString langfrfilename2=fi.absolutePath()+"/Languages/Français/fr.ts";
    QString langfrfilename3=fi.absolutePath()+"/Languages/Français/fr.png";

    QFileInfo fidb(databasefile);
    if  (! fidb.exists()) QFile::copy(":/Base/Chord.db",databasefile);
    QFileInfo filang(langfrfilename);
              if (! filang.exists())
    {
        QDir dir(fi.absolutePath());
        dir.mkdir("Languages");
        dir.mkdir("Languages/Français");
        QFile::copy(":/Lang/fr.qm",langfrfilename);
        QFile::copy(":/Lang/fr.ts",langfrfilename2);
        QFile::copy(":/Image/Images/fr.png",langfrfilename3);
    }
    QTranslator *tr=0;

    QString lang=s.value("InterfaceLanguage").toString();
    if ( lang != "English" )
    {
        tr =new QTranslator;
        QString qmfile=DialogConfiguration::getTranslationQmFileName(lang);
        tr->load(qmfile);
        a.installTranslator(tr);
    }
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

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
