#include "language.h"

#include <QSettings>
#include <QFileInfo>
#include <QDir>
#include <QComboBox>

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


void Language::setLanguageComboBox(QComboBox *ptr)
{
    QSettings s;
    QFileInfo fi(s.fileName());
    QString Langpath=fi.absolutePath();
    QString path=Langpath+"/Languages";
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
            ptr->addItem(QIcon(pngfile),name);
        }
    }

}
