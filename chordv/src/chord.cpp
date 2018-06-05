#include "chord.h"

#include "langnotes.h"
#include "language.h"
#include "chordutil.h"

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
 m_ring<<"A"<<"A#"<<"B"<<"C"<<"C#"<<"D"<<"D#"<<"E"<<"F"<<"F#"<<"G"<<"G#";
 int i;
 i=0;
 foreach (QString r, m_ring)m_rang[r]=i++;
 m_rang["Bb"]=1;
 m_rang["Db"]=4;
 m_rang["Eb"]=6;
 m_rang["Gb"]=9;
 m_rang["Ab"]=11;
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
     {
        m_nbbeat=exp.cap(3).toInt();
        m_nbbar=0;
     }
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
     QSqlQuery q(QString("SELECT value FROM chords WHERE name='%1' AND approved = 1").arg(m_purechordEnglish));
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

QStringList Chord::removeDupplicateWhithoutRytm(QStringList chords,QString codelang)
{
    QStringList ret;
    foreach ( QString ch, chords)
    {
        Chord c(ch,codelang);
        if ( codelang=="en") ret<<c.pureNameEnglish();
        else ret<<c.pureNameLocale();
    }
    ret.removeDuplicates();
    return ret;
}

QString Chord::translate(QString chord, QString codelangfrom, QString minfrom, QString codelangto,QString minto)
{
    QString chordreg=Language::ListNotes(Language::getLanguage(codelangfrom)).join("|");
    QStringList chordoutput=Language::ListNotes(Language::getLanguage(codelangto));
    chordreg=QString("^(%1)").arg(chordreg);
    QRegExp reg(chordreg);
    if ( chord.contains(reg))
    {
        QString c=reg.cap(1);
        int i=Language::ListNotes(Language::getLanguage(codelangfrom)).indexOf(c);
        chord.replace(c,chordoutput.at(i));
        chord.replace(minfrom,minto);
    }
   return chord;
}

QString Chord::translate(QString chord, QString codelangfrom,  QString codelangto)
{
    QString chordreg=Language::ListNotes(Language::getLanguage(codelangfrom)).join("|");
    QStringList chordoutput=Language::ListNotes(Language::getLanguage(codelangto));
    chordreg=QString("^(%1)").arg(chordreg);
    QRegExp reg(chordreg);
    if ( chord.contains(reg))
    {
        QString c=reg.cap(1);
        int i=Language::ListNotes(Language::getLanguage(codelangfrom)).indexOf(c);
        chord.replace(c,chordoutput.at(i));
    }
    return chord;
}
QString Chord::nameEnglish()
{
    return m_nameEnglish;
}


QString Chord::up()
{
    if ( m_nbbeat == 4) return QString("%1:2").arg(m_purechordLocale);
    else if ( m_nbbeat == 2 ) return m_purechordLocale;
    else if ( m_nbbar==1 ) return QString("%1x2").arg(m_purechordLocale);
    else if ( m_nbbar>1 ) return QString("%1x%2").arg(m_purechordLocale).arg(m_nbbar+1);
    else return (m_originalchord);
}



QString Chord::down()
{
    if ( m_nbbar >=3 ) return QString("%1x%2").arg(m_purechordLocale).arg(m_nbbar-1);
    else if ( m_nbbar==2 ) return m_purechordLocale;
    else if ( m_nbbar==1 ) return QString("%1:2").arg(m_purechordLocale);
    else if (m_nbbeat==2) return QString("%1:4").arg(m_purechordLocale );
    else return (m_originalchord);
}


QString Chord::transpose(QString ChordInEnglish , int degre )
{
 if (degre<0) degre+=12;
 QMap <QString,int> rang;
 QStringList ring;
 ring<<"A"<<"A#"<<"B"<<"C"<<"C#"<<"D"<<"D#"<<"E"<<"F"<<"F#"<<"G"<<"G#";
 int i;
 i=0;
 foreach (QString r, ring)rang[r]=i++;
 rang["Bb"]=1;
 rang["Db"]=4;
 rang["Eb"]=6;
 rang["Gb"]=9;
 rang["Ab"]=11;
 QRegExp regexp("^([A-G][#b]?)");
 QString ind;
 QString rest;
 if ( ChordInEnglish.contains(regexp) )
    {
     ind=regexp.cap(1);
     rest=ChordInEnglish.replace(regexp,"");
    }
 int id=(rang[ind]+degre)%12;
 QString ret=ring.at(id)+rest;
 return ret;
}

QStringList Chord::getCodeLang(QString chord)
{
    chord.replace("[","");
    chord.replace("]","");
    QStringList ret;
    foreach ( QString lang, Language::ListLanguage())
    {
        foreach ( QString note, Language::ListNotes(lang) )
        {

            if (chord.startsWith(note))
                ret <<Language::getCodeLang(lang) ;
        }
    }
    return ret;
}

QString Chord::getNote(QString chord)
{
    chord.replace("[","");
    chord.replace("]","");
    foreach ( QString lang, Language::ListLanguage())
    {
        foreach ( QString note, Language::ListNotes(lang) )
        {

            if (chord.startsWith(note))
                return note;
        }
    }
    return "";
}


QString Chord::getMinor(QString )
{
    return "-";
}

