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
        foreach ( QString line, m_BufLyrics)
    {
        if ( line =)
        while (line.indexOf(QRegEx))
    }
}


void ProcessorChord::displayPageSubtitle( QString )
{

}

void ProcessorChord::displayRytm()
{
    //Processor::displayPageSubtitle(m_rythm);
}

void ProcessorChord::displayBpm()
{
    //Text(m_document,QString("%1").arg(m_bpm),100,m_line,m_uiconfig->toolButtonSubtitleFont,right);
}
