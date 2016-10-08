#include "test.h"
#include "application.h"
#include <QSettings>
#include <QFileInfo>
#include <QDebug>


Test::Test(QString testname, QString condition, Application *a): QObject()
{
    QString inifile=a->getBindir()+"/test.chop";
    QString runfile=a->getBindir()+"/run.chop";
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
       qDebug()<<"finished";
       m_loop->exit(0);
}



void Test::Started()
{
       qDebug()<<"started";
}
