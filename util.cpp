#include "util.h"
#include <QSettings>
#include <QFileInfo>
#include <QDir>
#include <QDebug>
Util::Util()
{

}

QStringList Util::LastProjects()
{
    QStringList l;
    QSettings s;
    for ( int i=0; i<10; i++)
    {   QString val=s.value(QString("LastProjects/f%1").arg(i+1)).toString();
        if (val.isEmpty()) break;
        l <<val;
    }
   return l;
}

void Util::MemorizeProject(QString filename)
{
    if (filename.isEmpty()) return;
    QSettings s;
    s.beginGroup("LastProjects");
    foreach ( QString l, s.allKeys())
      if ( s.value(l).toString()==filename) return ;
    s.endGroup();
    QString old=s.value(QString("LastProjects/f1")).toString();
    s.setValue("LastProjects/f1",filename);
    for (int i=2; (i<10) && (!old.isEmpty()) ; i++)
    {
        s.setValue(QString("LastProjects/f%1").arg(i),old);
        old=s.value(QString("LastProjects/f%1").arg(i+1)).toString();
    }
}


QString  Util::getLastDirectory()
{
    QSettings s;
    return(s.value("LastOpenedDirectory").toString());
}

void Util::setLastDirectory(QString filename)
{
    if (filename.isEmpty()) return;
    QSettings s;
    QFileInfo fi(filename);
    QString  dir=fi.absoluteDir().absolutePath();
    s.setValue("LastOpenedDirectory",dir);

}
