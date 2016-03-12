#ifndef UTIL_H
#define UTIL_H

#include <QStringList>

class Util
{
public:
    Util();
    static QStringList LastProjects();
    static void MemorizeProject( QString filename);
};

#endif // UTIL_H
