#include <QCoreApplication>
#include "test.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Test("Toc End","Text/TocPosition=2");
    Test("Toc Begin","Text/TocPosition=1");
    Test("No Toc","Text/TocPosition=0");

    return a.exec();
}

