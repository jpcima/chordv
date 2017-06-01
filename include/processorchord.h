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
    void displayBpm();
    void displayPageSubtitle(QString ){}
    void includeSoc();
    void includeSor();
    int m_nbBeatPerBar;
    void doColumnBreak(QString line){}
    int m_w;
    int m_h;
    int m_x0;
    ///
    /// \brief m_vm vertical margin between two chord lines
    ///
    int m_vm;
    int m_hm;
    int m_fontchordsize;
    int m_barsperline;
    ///
    /// \brief m_posx can be 1 2 3 4 ( if 4 = m_nbBeatPerBar )
    ///
    int m_posx;

    QMap <QString, int >m_beats;
    QStringList m_subbar;
    PoDoFo::PdfFont *m_chordfont;
    bool CompleteBeats(QStringList listchord,int nbbeat);
    void DisplayBar(QString ch);
    void SubBar2Bar();
};

#endif // PROCESSORCHORD_H
