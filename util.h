#ifndef UTIL_H
#define UTIL_H

#include <QStringList>

class Util
{
public:
    Util();
    static QStringList LastProjects();
    static void MemorizeProject( QString filename);
    static QString getLastDirectory();
    static void setLastDirectory(QString filename);
    static QString toRomain(int i);
};

#endif // UTIL_H
