#ifndef TEST_H
#define TEST_H


#include "application.h"

#include <QProcess>
#include <QString>
#include <QEventLoop>

class Test : public QObject
{
    Q_OBJECT
public:
    Test( QString testname, QString condition, Application *a);
    ~Test();
private slots:
    void CheckPDF(int);
    void Started();
private:
    QProcess *m_launch;
    QEventLoop *m_loop;

};

#endif // TEST_H
