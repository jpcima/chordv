#ifndef APPLICATION_H
#define APPLICATION_H

#include <QCoreApplication>

class Application : public QCoreApplication
{
public:
    Application(int argc,char **argv);
    QString getBindir() { return m_bindir; }
private:
    QString m_bindir;
};

#endif // APPLICATION_H
