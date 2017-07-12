#ifndef UTIL_H
#define UTIL_H

#include <QStringList>
/// Some utilities


class ChordUtil
{
public:
    static QStringList LastProjects();
    static void MemorizeProject( QString filename);
    static QString getLastDirectory();
    static void setLastDirectory(QString filename);
    static QString toRomain(int i);
    static QStringList Normalize(QStringList FretAnd6Strings);
    static int fromRomain(QString i);
};

#endif // UTIL_H
