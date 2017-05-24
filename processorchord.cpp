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

void ProcessorChord::includeChorus( QString )
{

}


void ProcessorChord::displayLyrics()
{
    QRegExp chordREX("\\[[^]]+\\]",Qt::CaseInsensitive);
    foreach (QString text,m_BufLyrics)
    {
       qDebug()<<"hihi"<<text;
    }
}


void ProcessorChord::displayPageSubtitle( QString )
{

}

void ProcessorChord::displayTempo()
{
    //Processor::displayPageSubtitle(m_tempo);
}

void ProcessorChord::displayBpm()
{
    //Text(m_document,QString("%1").arg(m_bpm),100,m_line,m_uiconfig->toolButtonSubtitleFont,right);
}
