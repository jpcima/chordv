#include "application.h"
#include "test.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    Application a(argc,argv);
    Test("Toc End","Text/TocPosition=2",&a);
    Test("Toc Begin","Text/TocPosition=1",&a);
    Test("No Toc","Text/TocPosition=0",&a);
    Test("Toc Begin many page in Toc","Text/TocPosition=1|Text/TocVerticalSpacing=4",&a);
    Test("Toc End many page in Toc","Text/TocPosition=2|Text/TocVerticalSpacing=4",&a);



}

