#ifndef PROCESSORCHORD_H
#define PROCESSORCHORD_H

#include "processor.h"
#include "mainwindow.h"
#include <podofo/podofo.h>
#include <podofo/podofo-base.h>

#include <QMap>


class ProcessorChord : public Processor
{
public:
    ProcessorChord(Ui::MainWindow *ui1, Ui::FormConfig *ui2);
private:
    void displayLyrics();
    void displayRytm();
    void displayBpm();
    void displayPageSubtitle(QString);

    void includeSoc();
    void includeEoc();
    void includeSoR();
    void includeEoR();
    int m_nbBeatPerBar;
    void includeSor();
    void includeEor();
    void doColumnBreak(QString line){}

};

#endif // PROCESSORCHORD_H
