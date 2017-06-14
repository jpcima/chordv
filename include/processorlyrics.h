#ifndef PROCESSORLYRICS_H
#define PROCESSORLYRICS_H

#include "processor.h"
#include "mainwindow.h"
#include "fontbutton.h"
#include <podofo/podofo.h>
#include <podofo/podofo-base.h>

class ProcessorLyrics : public Processor
{
public:
    ProcessorLyrics(Ui::MainWindow *ui1,Ui::FormConfig *ui2);
private:
    void displayChordsForSong();
    void displayLyrics();
    void includeEor(){}
    void includeEoc(){}
    void doColumnBreak(QString line);
    void Drawline(double pos, int num, FontButton *ptr);
};

#endif // PROCESSORLYRICS_H
