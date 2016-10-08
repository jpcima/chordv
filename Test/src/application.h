#ifndef APPLICATION_H
#define APPLICATION_H

#include <QCoreApplication>

class Application : public QCoreApplication
{
public:
    Application(int argc,char **argv);
    QString getBindir() { return m_bindir; }
    QString getExec(){ return m_exec;}
private:
    QString m_bindir;
    QString m_exec;
};

#endif // APPLICATION_H
