#include "language.h"
#include "chord.h"
#include <QSettings>
#include <QFileInfo>
#include <QDir>
#include <QComboBox>
#include <QFile>
#include <QDebug>
#include <QMap>
#include <QStringList>

static QMap <QString, QString > Code2Language;
static QMap <QString, QString > Language2Code;


void Language::InitLanguage()
{
    QString datadir(DATADIR);
    QString path=QString("%1/Languages").arg(datadir);
    QFileInfoList filist=QDir(path).entryInfoList(QDir::AllEntries|QDir::NoDotAndDotDot);
    foreach (QFileInfo fi, filist)
    {
        QStringList filter;
        filter << "*.chords";
        QFileInfoList chordlist=QDir(fi.filePath()).entryInfoList(filter);
        Code2Language[chordlist.at(0).baseName()]=fi.fileName();
        Language2Code[fi.fileName()]=chordlist.at(0).baseName();
    }

}

QString Language::getTranslationQmFileName(QString language)
{
    if (language=="English") return QString();
    QString datadir(DATADIR);
    QString ret=QString("%1/Languages/%2/%3.qm").arg(datadir,language,Language::getCodeLang(language));
    return ret;
}


QString Language::getTranslationDocFileName(QString language)
{
    QString datadir(DATADIR);
    QString dirname=datadir+"/Languages/"+language;
    QDir d(dirname);
    QStringList filter;
    filter<<"*.html";
    QFileInfoList fi=d.entryInfoList(filter);
    if (fi.count()>=1)
        return fi.at(0).absoluteFilePath();
    else return QString();
}

QString Language::getTranslationDemoFileName(QString language)
{
    QString datadir(DATADIR);
    QString dirname=datadir+"/Languages/"+language;
    QDir d(dirname);
    QStringList filter;
    filter<<"*.chop";
    QFileInfoList fi=d.entryInfoList(filter);
    if (fi.count()>=1)
        return fi.at(0).absoluteFilePath();
    else return QString();
}


void Language::setLanguageComboBox(QComboBox *ptr)
{
    QString datadir(DATADIR);
    QString path=datadir+"/Languages";
    ptr->clear();
    QFileInfoList filist=QDir(path).entryInfoList(QDir::AllDirs|QDir::NoDotAndDotDot);
    foreach (QFileInfo fi, filist)
    {
        QString dir=fi.absoluteFilePath();
        QString name=fi.fileName();
        QDir d(dir);
        QStringList filter;
        filter<<"*.chords";
        QFileInfoList list=d.entryInfoList(filter);
        if ( !list.isEmpty())
        {
            QString qmfile=list.at(0).absoluteFilePath();
            QString pngfile=qmfile.replace(QRegExp("\\.chords$"),".png");
            QFileInfo fi(pngfile);

            QString lang=fi.baseName();
            ptr->addItem(QIcon(pngfile),name,lang);
        }
    }

}

QStringList Language::ListNotes(QString language)
{
    QString datadir(DATADIR);
    QString codelang=Language::getCodeLang(language);
    QString filename=QString("%1/Languages/%2/%3.chords").arg(datadir,language,codelang);
    QFile file(filename);
    file.open(QIODevice::ReadOnly|QIODevice::Text);
    QString chords=file.readLine();
    chords.chop(1);
    file.close();
    return chords.split(",");
}

QStringList Language::ListMinor(QString lang)
{
    QString datadir(DATADIR);
    QString codelang=Language::getCodeLang(lang);
    QString filename=QString("%1/Languages/%2/%3.chords").arg(datadir,lang,codelang);
    QFile file(filename);
    file.open(QIODevice::ReadOnly|QIODevice::Text);
    QString minor=file.readLine();
    minor=file.readLine();
    minor.chop(1);
    file.close();
    return minor.split(",");
}

QString Language::getCodeLang(QString language)
{
    return Language2Code[language];
}

QString Language::getLanguage(QString codelang)
{
    return Code2Language[codelang];
}


QString Language::TranslateLineWithchord(QString line,QString fromlang, QString frommin, QString tolang, QString tomin)
{
   bool accolade=false;
   QRegExp regchord("(\\[[^]]+\\])");
   while ( line.indexOf(regchord)!=-1)
     {
          accolade=true;
          QString newchord=regchord.cap(1).replace("[","").replace("]","");
          newchord=Chord::translate(newchord,Language::getCodeLang(fromlang),frommin,Language::getCodeLang(tolang),tomin);
          line.replace(regchord.cap(1),QString("{%1}").arg(newchord));
     }
     if ( accolade)
     {
          line.replace("{","[").replace("}","]");
     }
     return line;
}

QStringList Language::ListLanguage()
{
   return Language2Code.keys();
}

QStringList Language::ListCodeLang()
{

    return Code2Language.keys();
}



