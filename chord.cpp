#include "chord.h"

#include <QApplication>
#include <QRegExp>
#include <QSqlQuery>
#include <QSqlError>
#include <QString>
#include <QStringList>
#include <QVariant>
#include <QDebug>

Chord::Chord(QString chord):QString(chord)
{


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
 if ( m_purechordLocale.contains(QRegExp("[x0-9 ]+")))
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


QString Chord::ToEnglish(QString  chord)
{

   chord.replace ("m","-");
   QString A=qApp->translate("Chord","A");
   QString B=qApp->translate("Chord","B");
   QString C=qApp->translate("Chord","C");
   QString D=qApp->translate("Chord","D");
   QString E=qApp->translate("Chord","E");
   QString F=qApp->translate("Chord","F");
   QString G=qApp->translate("Chord","G");
   QString ret;
   if ( chord.startsWith(A)) ret=chord.replace(A,"A");
   if ( chord.startsWith(B)) ret=chord.replace(B,"B");
   if ( chord.startsWith(C)) ret=chord.replace(C,"C");
   if ( chord.startsWith(D)) ret=chord.replace(D,"D");
   if ( chord.startsWith(E)) ret=chord.replace(E,"E");
   if ( chord.startsWith(F)) ret=chord.replace(F,"F");
   if ( chord.startsWith(G)) ret=chord.replace(G,"G");
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
