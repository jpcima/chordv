#include "application.h"
#include "test.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    Application a(argc,argv);
    Test("Toc End","Text/TocPosition=2",&a);
    Test("Toc Begin","Text/TocPosition=1",&a);
    Test("No Toc","Text/TocPosition=0",&a);
}

