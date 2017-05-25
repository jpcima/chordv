#include "processorchord.h"

#include "ui_formconfig.h"
#include "ui_mainwindow.h"
#include "chord.h"
#include "mainwindow.h"

#include <podofo/podofo.h>
#include <podofo/podofo-base.h>


#include <QStringList>
#include <QDebug>

using namespace PoDoFo;


ProcessorChord::ProcessorChord(Ui::MainWindow *ui1, Ui::FormConfig *ui2):Processor(ui1,ui2)
{

}


void ProcessorChord::displayLyrics()
{
    if ( !m_rythm.contains("/"))
        m_nbBeatPerBar=4;
    else
        m_nbBeatPerBar=m_rythm.split("/").at(1).toInt();

    int nbeat=0;
    int col=10;
    QRegExp regChord("([^[]*)\\[([^]]+)\\](.*)",Qt::CaseInsensitive);
    foreach ( QString line, m_BufLyrics)
    {

        while (line.indexOf(regChord)!=-1)
        {
            QString ch=regChord.cap(2);
            nbeat++;
            if ( line =="SOC" || line=="EOC" || line =="SOR" || line == "EOR" || nbeat>m_nbBeatPerBar )
            {
                nbeat=1;
            }
            Chord chord(ch,m_uimainwindow->comboBoxChordLanguage->currentData().toString());
            qDebug()<<chord.chord()<<chord.nbBar()<<chord.nbBeat()<<chord.nbNote();
            Text(m_document,chord.nameEnglish(),col,m_line,m_uiconfig->toolButtonChordFont);
            col+=10;
            m_line+=10;
            line=regChord.cap(3);
        }
    }
}


void ProcessorChord::displayPageSubtitle( QString )
{

}

void ProcessorChord::includeEoc()
{
    m_BufLyrics<<"EOC";
}


void ProcessorChord::includeSoc()
{
    m_BufLyrics<<"SOC";
}

void ProcessorChord::includeSor()
{
    m_BufLyrics<<"SOR";
}

void ProcessorChord::includeEor()
{
    m_BufLyrics<<"EOR";
}


void ProcessorChord::displayRytm()
{
    //Processor::displayPageSubtitle(m_rythm);
}

void ProcessorChord::displayBpm()
{
    //Text(m_document,QString("%1").arg(m_bpm),100,m_line,m_uiconfig->toolButtonSubtitleFont,right);
}
