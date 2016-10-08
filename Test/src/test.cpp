#include "test.h"
#include "application.h"
#include <QSettings>
#include <QFileInfo>
#include <QDebug>


Test::Test(QString testname, QString condition, Application *a): QObject()
{
    m_testname=testname;
    m_testname.replace(" ","_");
    m_starttime=QDateTime::currentDateTime();
    QString inifile=QString("%1/test.chop").arg(a->getBindir());
    QString runfile=QString("%1/run_%2.chop").arg(a->getBindir(),m_testname);
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

    m_launch = new QProcess;
    connect (m_launch,SIGNAL(finished(int)),this,SLOT(CheckPDF(int)));
    connect (m_launch,SIGNAL(started()),this,SLOT(Started()));
    m_launch->start(a->getExec(),QStringList()<<"-t"<<runfile);
    m_loop = new QEventLoop;
    m_loop->exec();
}

Test::~Test()
{
    delete m_launch;
    delete m_loop;
}

void Test::CheckPDF(int)
{
       qint64 delta=m_starttime.msecsTo(QDateTime::currentDateTime());
       QTime time(0,0,0,delta);
       qInfo()<<QString("%1 done [%2]").arg(m_testname).arg(time.toString("mm:ss:zzz"));
       m_loop->exit(0);
}



void Test::Started()
{
}
