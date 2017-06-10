#include "language.h"
#include "chord.h"
#include <QSettings>
#include <QFileInfo>
#include <QDir>
#include <QComboBox>
#include <QFile>
#include <QDebug>

QString Language::getTranslationQmFileName(QString language)
{
    if (language=="English") return QString();
    QSettings s;
    QFileInfo f1(s.fileName());
    return QString("%1/Languages/%2/%3.qm").arg(f1.absolutePath(),language,Language::getCodeLang(language));
}


QString Language::getTranslationDocFileName(QString language)
{
    QSettings s;
    QFileInfo f1(s.fileName());
    QString dirname=f1.absolutePath()+"/Languages/"+language;
    QDir d(dirname);
    QStringList filter;
    filter<<"*.html";
    QFileInfoList fi=d.entryInfoList(filter);
    if (fi.count()>=1)
        return fi.at(0).absoluteFilePath();
    else return QString();
}



void Language::setLanguageComboBox(QComboBox *ptr)
{
    QSettings s;
    QFileInfo fi(s.fileName());
    QString Langpath=fi.absolutePath();
    QString path=Langpath+"/Languages";
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

QStringList Language::ListChord(QString lang)
{
    QSettings s;
    QFileInfo f1(s.fileName());
    QString codelang=Language::getCodeLang(lang);
    QString filename=QString("%1/Languages/%2/%3.chords").arg(f1.absolutePath(),lang,codelang);
    QFile file(filename);
    file.open(QIODevice::ReadOnly|QIODevice::Text);
    QString chords=file.readLine();
    chords.chop(1);
    file.close();
    return chords.split(",");
}

QStringList Language::ListMinor(QString lang)
{
    QSettings s;
    QFileInfo f1(s.fileName());
    QString codelang=Language::getCodeLang(lang);
    QString filename=QString("%1/Languages/%2/%3.chords").arg(f1.absolutePath(),lang,codelang);
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
    QString lang;
    QSettings s;
    QFileInfo fi(s.fileName());
    QString path=QString("%1/Languages/%2").arg(fi.absolutePath(),language);
    QFileInfoList filist=QDir(path).entryInfoList(QDir::AllEntries|QDir::NoDotAndDotDot);
    foreach (QFileInfo fi, filist)
    {
        if ( fi.filePath().endsWith(".chords") )
             lang = fi.baseName();
    }
    return lang;
}

QString Language::TranslateLineWithchord(QString line,QString fromlang, QString frommin, QString tolang, QString tomin)
{
   bool accolade=false;
   QRegExp regchord("(\\[[^]]+\\])");
   while ( line.indexOf(regchord)!=-1)
     {
          accolade=true;
          QString newchord=regchord.cap(1).replace("[","").replace("]","");
          newchord=Chord::translate(newchord,fromlang,frommin,tolang,tomin);
          line.replace(regchord.cap(1),QString("{%1}").arg(newchord));
     }
     if ( accolade)
     {
          line.replace("{","[").replace("}","]");
     }
     return line;
}

