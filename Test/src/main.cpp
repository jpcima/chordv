#include "application.h"
#include "test.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    Application a(argc,argv);
    Test("No Toc","Text/TocPosition=0",&a);
    Test("Toc Begin ONE page in toc","Text/TocPosition=1",&a);
    Test("Toc Begin many pages in Toc","Text/TocPosition=1|Text/TocVerticalSpacing=4",&a);
    Test("Toc End ONE page in toc","Text/TocPosition=2",&a);
    Test("Toc End many pages in Toc","Text/TocPosition=2|Text/TocVerticalSpacing=4",&a);



}

