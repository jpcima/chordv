#include "language.h"

#include <QSettings>
#include <QFileInfo>
#include <QDir>
#include <QComboBox>
#include <QFile>

QString Language::getTranslationQmFileName(QString language)
{
    if (language=="English") return QString();
    QSettings s;
    QFileInfo f1(s.fileName());
    QString dirname=f1.absolutePath()+"/Languages/"+language;
    QDir d(dirname);
    QStringList filter;
    filter<<"*.qm";
    QFileInfoList fi=d.entryInfoList(filter);
    if (fi.count()>=1)
        return fi.at(0).absoluteFilePath();
    else return QString();
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
    ptr->addItem(QIcon(":/Image/Images/en.png"),"English","en");
    QFileInfoList filist=QDir(path).entryInfoList(QDir::AllDirs|QDir::NoDotAndDotDot);
    foreach (QFileInfo fi, filist)
    {
        QString dir=fi.absoluteFilePath();
        QString name=fi.fileName();
        QDir d(dir);
        QStringList filter;
        filter<<"*.qm";
        QFileInfoList list=d.entryInfoList(filter);
        if ( !list.isEmpty())
        {
            QString qmfile=list.at(0).absoluteFilePath();
            QString pngfile=qmfile.replace(QRegExp("\\.qm$"),".png");
            QFileInfo fi(pngfile);
            QString lang=fi.baseName();
            ptr->addItem(QIcon(pngfile),name,lang);
        }
    }

}

QStringList Language::ListChord(QString lang, QString codelang)
{
    QSettings s;
    QFileInfo f1(s.fileName());
    QString filename=QString("%1/Languages/%2/%3.chords").arg(f1.absolutePath(),lang,codelang);
    QFile file(filename);
    file.open(QIODevice::ReadOnly|QIODevice::Text);
    QString chords=file.readLine();
    chords.chop(1);
    file.close();
    return chords.split(",");
}

QStringList Language::ListMinor(QString lang, QString codelang)
{
    QSettings s;
    QFileInfo f1(s.fileName());
    QString filename=QString("%1/Languages/%2/%3.chords").arg(f1.absolutePath(),lang,codelang);
    QFile file(filename);
    file.open(QIODevice::ReadOnly|QIODevice::Text);
    QString chords=file.readLine();
    QString minor=file.readLine();
    minor.chop(1);
    file.close();
    return minor.split(",");
}
