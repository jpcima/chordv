#ifndef PROCESSORLYRICS_H
#define PROCESSORLYRICS_H

#include "processor.h"
#include "mainwindow.h"

class ProcessorLyrics : public Processor
{
public:
    ProcessorLyrics(Ui::MainWindow *ui1,Ui::FormConfig *ui2);
private:
    void displayChordsForSong();

};

#endif // PROCESSORLYRICS_H
