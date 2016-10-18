#include "application.h"
#include "test.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    Application a(argc,argv);
    // Cover pittfalls
    Test("No Toc","Text/TocPosition=0",&a);
    Test("No Toc Many page for songs","Text/TocPosition=0|Text/",&a);
    Test("No Toc no cover","Text/Cover=0|Text/TocPosition=0",&a);
    Test("Toc Begin ONE page in toc","Text/TocPosition=1",&a);
    Test("Toc Begin ONE page in toc no cover","Text/TocPosition=1|Text/Cover=0",&a);
    Test("Toc Begin many pages in Toc","Text/TocPosition=1|Text/TocVerticalSpacing=7",&a);
    Test("Toc Begin many pages in Toc no cover","Text/TocPosition=1|Text/TocVerticalSpacing=7|Text/Cover=0",&a);
    Test("Toc End ONE page in toc","Text/TocPosition=2",&a);
    Test("Toc End ONE page in toc no cover","Text/TocPosition=2|Text/Cover=0",&a);
    Test("Toc End many pages in Toc","Text/TocPosition=2|Text/TocVerticalSpacing=7",&a);
    Test("Toc End many pages in Toc","Text/TocPosition=2|Text/TocVerticalSpacing=7|Text/Cover=0",&a);
}

