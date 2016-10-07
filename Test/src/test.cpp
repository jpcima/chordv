#include "test.h"
#include "application.h"
#include <QSettings>
#include <QFileInfo>
#include <QDebug>
#include <QProcess>

Test::Test(QString testname, QString condition, Application *a)
{
    QString inifile=a->getBindir()+"/test.ini";
    QString runfile=a->getBindir()+"/run.ini";
    QFileInfo fi(inifile);
    if (  ! fi.exists())
    {
        qInfo()<<QString("File %1 doesn't exist. Bye!").arg(inifile);
        exit(1);
    }
    QFile file(inifile);
    file.copy(runfile);

    QSettings s(runfile,QSettings::IniFormat);

    s.setValue("Watermark",testname);
    foreach ( QString cond,condition.split('|'))
    {
        QStringList conds=cond.split('=');
        s.setValue(conds.at(0),conds.at(1));
    }
    QProcess launch;
    launch.start("../bin/test",QStringList()<<"-t"<<runfile);
}
