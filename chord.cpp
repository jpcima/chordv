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
 m_lang=lang;
 QRegExp exp("([^x]*)x([0-9]$)");
 QRegExp par("([^(]+)");
 if ( chord.contains(exp))
 {
     m_tempo=exp.cap(2);
     m_purechordLocale=exp.cap(1);
 }
 else
 {
     m_tempo=QString();
     m_purechordLocale=chord;
 }
 QString res;
 if ( m_purechordLocale.contains(QRegExp("([A-G][#b]?[^:]*):([x0-9 ]+")))
     res=m_purechordLocale;
 else
 {
     m_nameLocale=m_purechordLocale;
     if ( m_nameLocale.contains(par))
     {
          m_nameLocale=par.cap(1);
     }
     m_purechordEnglish=ToEnglish(lang,m_purechordLocale);

     if ( m_purechordEnglish.contains(par))
     {
         m_nameEnglish=par.cap(1);
     }
     QSqlQuery q(QString("SELECT value FROM chords WHERE name='%1'").arg(m_purechordEnglish));
     if ( !q.next())
         res=QString(qApp->translate("Chord","ERROR"));
     else
         res=q.value(0).toString();
 }
 m_chordonstrings=res.split(" ");
 m_fret=m_chordonstrings.takeFirst();
}

QString Chord::removeTempo()
{
  return (m_purechordLocale);
}

QString Chord::tempo()
{
    return (m_tempo);
}

QStringList Chord::toStrings()
{
    return(m_chordonstrings);
}

QString Chord::fret()
{
     return m_fret;
}


QString Chord::ToEnglish(QString lang,QString  chord)
{
   chord.replace ("m","-");
   QString ret;
   if ( chord.startsWith(m_notes.note(lang,"A"))) ret=chord.replace(m_notes.note(lang,"A"),"A");
   if ( chord.startsWith(m_notes.note(lang,"B"))) ret=chord.replace(m_notes.note(lang,"B"),"B");
   if ( chord.startsWith(m_notes.note(lang,"C"))) ret=chord.replace(m_notes.note(lang,"C"),"C");
   if ( chord.startsWith(m_notes.note(lang,"D"))) ret=chord.replace(m_notes.note(lang,"D"),"D");
   if ( chord.startsWith(m_notes.note(lang,"E"))) ret=chord.replace(m_notes.note(lang,"E"),"E");
   if ( chord.startsWith(m_notes.note(lang,"F"))) ret=chord.replace(m_notes.note(lang,"F"),"F");
   if ( chord.startsWith(m_notes.note(lang,"G"))) ret=chord.replace(m_notes.note(lang,"G"),"G");
   return(ret);
}

QString Chord::nameLocale()
{
    return m_nameLocale;
}

QString Chord::nameEnglish()
{
    return m_nameEnglish;
}
