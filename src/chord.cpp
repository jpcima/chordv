#include "chord.h"
#include "langnotes.h"

#include <QApplication>
#include <QRegExp>
#include <QSqlQuery>
#include <QSqlError>
#include <QString>
#include <QStringList>
#include <QVariant>
#include <QDebug>
#include <QSettings>

Chord::Chord(QString chord, QString lang):QString(chord)
{
 m_originalchord=chord;
 m_nbbeat=0;
 m_nbbar=1;
 m_lang=lang;
 QRegExp exp("([^x:]*)([x:]?)([0-9]*)");
 QRegExp par("([^(]+)");
 if ( chord.contains(exp))
 {
     if ( exp.cap(2)=="x")
        m_nbbar=exp.cap(3).toInt();
     else if (exp.cap(2) == ":")
        m_nbbeat=exp.cap(3).toInt();
     m_purechordLocale=exp.cap(1);
 }
 else
 {
     m_purechordLocale=chord;
 }
 QString res;
 if ( m_purechordLocale.contains(QRegExp("([A-G][#b]?[^=]*)=([x0-9 ]+")))
     res=m_purechordLocale;
 else
 {
     m_nameLocale=m_purechordLocale;
     if ( m_nameLocale.contains(par))
     {
          m_nameLocale=par.cap(1);
     }
     m_purechordEnglish=ToEnglish(m_purechordLocale);

     if ( m_purechordEnglish.contains(par))
     {
         m_nameEnglish=par.cap(1);
     }
     QSqlQuery q(QString("SELECT value FROM chords WHERE name='%1'").arg(m_purechordEnglish));
     if ( !q.next())
         res=QString(qApp->translate("Chord","not found"));
     else
         res=q.value(0).toString();
 }
 m_chordonstrings=res.split(" ");
 m_fret=m_chordonstrings.takeFirst();
}

QString Chord::chord()
{
    return m_originalchord;
}

QString Chord::removeRytm()
{
  return (m_purechordLocale);
}

int Chord::nbBar()
{
    return m_nbbar;
}

int Chord::nbBeat()
{
    return m_nbbeat;
}

QStringList Chord::toStrings()
{
    return(m_chordonstrings);
}

QString Chord::fret()
{
     return m_fret;
}



QString Chord::ToEnglish(QString  chord)
{
   chord.replace ("m","-");
   if ( chord.startsWith(m_notes.noteLocale("A"))) chord.replace(m_notes.noteLocale("A"),"A");
   else if ( chord.startsWith(m_notes.noteLocale("B"))) chord.replace(m_notes.noteLocale("B"),"B");
   else if ( chord.startsWith(m_notes.noteLocale("C"))) chord.replace(m_notes.noteLocale("C"),"C");
   else if ( chord.startsWith(m_notes.noteLocale("D"))) chord.replace(m_notes.noteLocale("D"),"D");
   else if ( chord.startsWith(m_notes.noteLocale("E"))) chord.replace(m_notes.noteLocale("E"),"E");
   else if ( chord.startsWith(m_notes.noteLocale("F"))) chord.replace(m_notes.noteLocale("F"),"F");
   else if ( chord.startsWith(m_notes.noteLocale("G"))) chord.replace(m_notes.noteLocale("G"),"G");
   return(chord);
}

QString Chord::nameLocale()
{
    return m_nameLocale;
}

QString Chord::pureNameLocale()
{
    return m_purechordLocale;
}

QString Chord::pureNameEnglish()
{
    return m_purechordEnglish;
}

QStringList Chord::removeDupplicateWhithoutRytm(QStringList chords,QString lang)
{
    QStringList ret;
    foreach ( QString ch, chords)
    {
        Chord c(ch,lang);
        if ( lang=="en") ret<<c.pureNameEnglish();
        else ret<<c.pureNameLocale();
    }
    ret.removeDuplicates();
    return ret;
}

QString Chord::nameEnglish()
{
    return m_nameEnglish;
}
