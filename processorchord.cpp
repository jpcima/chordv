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
    if ( m_firstline )
    {
        m_firstline=false;
        m_line-=m_uiconfig->toolButtonNormalFont->getFont().pointSizeF()*3;
        m_initialhposition=m_line;
    }
    foreach (QString text,m_BufLyrics)
    {
        if ( ! text.isEmpty() )
        {
          int col=m_column;
          QRegExp chordexp("([^[]*)\\[([^]]*)\\](.*)");
          while  ( text.indexOf(chordexp)!=-1)
          {
            Chord ch(chordexp.cap(2),m_uimainwindow->comboBoxChordLanguage->currentData().toString());
            if (  m_uiconfig->comboBoxChordInText->currentIndex()!= FormConfig::DiagramInText)
               {
                QString c=m_uiconfig->comboBoxChordLang->currentData().toString()=="en"?ch.nameEnglish():ch.nameLocale();
                Text(m_document,c,col,m_line,m_uiconfig->toolButtonChordFont);
               }
            else
               {
                displayChord(ch.chord(),m_line,col,m_uiconfig->spuChordHorizontalSize->getPdfU(),m_uiconfig->comboBoxChordLang->currentData().toString());
               }
            text=chordexp.cap(3);
          }
        }
        NextLine();
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
