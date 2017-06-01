#include "processorlyrics.h"
#include "ui_formconfig.h"
#include "ui_mainwindow.h"
#include "chord.h"

#include <QDebug>
#include <QStringList>



using namespace PoDoFo;

ProcessorLyrics::ProcessorLyrics(Ui::MainWindow *ui1, Ui::FormConfig *ui2):Processor(ui1,ui2)
{
    m_mode="lyrics";
}

void ProcessorLyrics::displayChordsForSong()
{
  if ( m_uiconfig->comboBoxChordInText->currentIndex()==FormConfig::ChordAtBeginingAndChordNameInText)
  {
    // chords are displayed in first with diagram and just chord name in text
    NextLine();
    NextLine();
    QStringList chords=m_BufChords;
    QStringList chordswithoutrythm=Chord::removeDupplicateWhithoutRytm(chords,m_uiconfig->comboBoxChordLang->currentData().toString());
    foreach ( QString chord, chordswithoutrythm)
        displayChord(chord,m_line,m_column,m_uiconfig->spuChordHorizontalSize->getPdfU(),m_uiconfig->comboBoxChordLang->currentData().toString());
    m_column=m_uiconfig->spuHorizontalMargin->getPdfU();
    m_line-=m_uiconfig->spuChordHorizontalSize->getPdfU();
 }
}


void ProcessorLyrics::displayLyrics()
{
    BufLyricsNormailisation();
    if ( m_firstline )
    {
        m_firstline=false;
        m_line-=m_uiconfig->toolButtonNormalFont->getFont().pointSizeF()*3;
        m_initialhposition=m_line;
        if (  m_uiconfig->comboBoxChordInText->currentIndex()== FormConfig::DiagramInText && m_BufLyrics.at(0)!= tr("start_of_chorus"))
          {
            m_initialhposition-=m_uiconfig->spuChordHorizontalSize->getPdfU();
            m_line=m_initialhposition;
          }
    }

    foreach (QString text,m_BufLyrics)
    {
        int num=0;
        int col=m_column;

        QRegExp chordexp("([^[]*)\\[([^]]*)\\](.*)");
        PdfFont *pfont=m_document->CreateFont(m_uiconfig->toolButtonNormalFont->getFont().family().toLatin1());
        PdfFont *cfont=m_document->CreateFont(m_uiconfig->toolButtonChordFont->getFont().family().toLatin1());
        if ( ! text.isEmpty() )
        {
          if ( isColBreak(text)) doColumnBreak(text);
          else if ( ! isChorus(text))
          {

          while  ( text.indexOf(chordexp)!=-1)
          {
            Chord ch(chordexp.cap(2),m_uimainwindow->comboBoxChordLanguage->currentData().toString());
            QString t1=chordexp.cap(1);
            Text(m_document,t1,col,m_line,m_uiconfig->toolButtonNormalFont);
            //col+=pfont->GetFontMetrics()->StringWidth(PdfString (t1.toLatin1()));
            addCol(col,pfont->GetFontMetrics()->StringWidth(PdfString (t1.toLatin1())));
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
                int col1=col-m_uiconfig->spuChordHorizontalSize->getPdfU()/2;
                //while ( col1 -m_oldcol <m_uiconfig->spuChordHorizontalSize->getPdfU()/6) col1+=m_uiconfig->spuChordHorizontalSize->getPdfU()/6;
              addCol(col1,m_uiconfig->spuChordHorizontalSize->getPdfU()/6);
                displayChord(ch.chord(),line1,col1,m_uiconfig->spuChordHorizontalSize->getPdfU(),m_uiconfig->comboBoxChordLang->currentData().toString());
                m_oldcol=col1;
               }
            text=chordexp.cap(3);
           }
          if ( (text ==tr("Refrain :") || text ==tr("Chorus :")) && m_uiconfig->comboBoxChordInText->currentIndex()==0)
          {
              num = m_uiconfig->spuChordHorizontalSize->getPdfU();
          }
          Text(m_document,text,col,m_line,m_uiconfig->toolButtonNormalFont);
          }
          else
          {
           while  ( text.indexOf(chordexp)!=-1)
           {
               Chord ch(chordexp.cap(2),m_uimainwindow->comboBoxChordLanguage->currentData().toString());
               if (  m_uiconfig->comboBoxChordInText->currentIndex()!= FormConfig::DiagramInText)
                  {
                   num=m_uiconfig->toolButtonChordFont->getFont().pointSizeF()*1.2;
                   QString c1=m_uiconfig->comboBoxChordLang->currentData().toString()=="en"?ch.nameEnglish():ch.nameLocale();
                   Text(m_document,c1,col,m_line,m_uiconfig->toolButtonChordFont);
                   //int col2=col+cfont->GetFontMetrics()->StringWidth(PdfString ((c1+"  ").toLatin1()));
                   //col+=col2 ;
                    addCol(col,cfont->GetFontMetrics()->StringWidth(PdfString ((c1+"  ").toLatin1())));
                  }
               else
                  {
                   num = m_uiconfig->spuChordHorizontalSize->getPdfU();
                   int line1=m_line+num;
                   displayChord(ch.chord(),line1,col,m_uiconfig->spuChordHorizontalSize->getPdfU(),m_uiconfig->comboBoxChordLang->currentData().toString());
                  }
               text=chordexp.cap(3);
           }
          }
        }
        NextLine(num);
    }
}

void ProcessorLyrics::doColumnBreak(QString line)
{
    QRegExp ColumnBreakREX("^ *\\{(column_break|colb)(:lyrics) *\\}",Qt::CaseInsensitive);
    if ( line.contains(ColumnBreakREX))
    {
        if ( m_colnumber > 1 && currentColumn() < m_colnumber  )
              {
                m_column = nextColumn( currentColumn() ) ;
                m_line=m_initialhposition;
              }
            else
            {
                if (m_tocpages.count() != 0)
                    m_tocpages[m_title]++;
                newPage();
            }
    }

}
