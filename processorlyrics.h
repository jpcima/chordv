#ifndef PROCESSORLYRICS_H
#define PROCESSORLYRICS_H

#include "processor.h"
#include "mainwindow.h"
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
    void doColumnBreak(QString line);

};

#endif // PROCESSORLYRICS_H
