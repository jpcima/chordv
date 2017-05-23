#include "processorchord.h"
#include "ui_formconfig.h"
#include "ui_mainwindow.h"
#include "chord.h"

#include <QStringList>

#include "mainwindow.h"
#include <podofo/podofo.h>
#include <podofo/podofo-base.h>


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
        int num=0;
        if ( ! text.isEmpty() )
        {
          int col=m_column;
          QRegExp chordexp("([^[]*)\\[([^]]*)\\](.*)");
          while  ( text.indexOf(chordexp)!=-1)
          {

            QString t1=chordexp.cap(1);
            Text(m_document,t1,col,m_line,m_uiconfig->toolButtonNormalFont);
            Chord ch(chordexp.cap(2),m_uimainwindow->comboBoxChordLanguage->currentData().toString());
            PdfFont *pfont=m_document->CreateFont(m_uiconfig->toolButtonNormalFont->getFont().family().toLatin1());
            col+=pfont->GetFontMetrics()->StringWidth(PdfString (t1.toLatin1()));
            if (  m_uiconfig->comboBoxChordInText->currentIndex()!= FormConfig::DiagramInText)
               {
                num=m_uiconfig->toolButtonChordFont->getFont().pointSizeF()*1.2;
                QString c1=m_uiconfig->comboBoxChordLang->currentData().toString()=="en"?ch.nameEnglish():ch.nameLocale();
                Text(m_document,c1,col,m_line+num,m_uiconfig->toolButtonChordFont);
               }
            else
               {
                num = m_uiconfig->spuChordHorizontalSize->getPdfU();
                int line1=m_line+num;
                int col1=col;
                displayChord(ch.chord(),line1,col1,m_uiconfig->spuChordHorizontalSize->getPdfU(),m_uiconfig->comboBoxChordLang->currentData().toString());
               }
            text=chordexp.cap(3);
          }
          Text(m_document,text,col,m_line,m_uiconfig->toolButtonNormalFont);
        }
        NextLine(num);
    }
}
