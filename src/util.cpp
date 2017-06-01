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

QString Util::toRomain(int i)
{
    if ( i == 1 ) return "I";
    if ( i == 2 ) return "II";
    if ( i == 3 ) return "III";
    if ( i == 4 ) return "IV";
    if ( i == 5 ) return "V";
    if ( i == 6 ) return "VI";
    if ( i == 7 ) return "VII";
    if ( i == 8 ) return "VIII";
    if ( i == 9 ) return "IX";
    if ( i == 10 ) return "X";
    if ( i == 11 ) return "XI";
    if ( i == 12 ) return "XII";
    if ( i == 13 ) return "XIII";
    if ( i == 14 ) return "XIV";
    if ( i == 15 ) return "XV";
    if ( i == 16 ) return "XVI";
    if ( i == 17 ) return "XVII";
    if ( i == 18 ) return "XVIII";
    if ( i == 19 ) return "XIX";
    if ( i == 20 ) return "XX";
    return "I";
}

