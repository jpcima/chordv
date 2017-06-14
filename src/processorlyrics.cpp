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
        if (  m_uiconfig->comboBoxChordInText->currentIndex()== FormConfig::DiagramInText && !m_BufLyrics.isEmpty() && m_BufLyrics.at(0)!= tr("start_of_chorus"))
          {
            m_initialhposition-=m_uiconfig->spuChordHorizontalSize->getPdfU();
            m_line=m_initialhposition;
          }
    }

    foreach (QString text,m_BufLyrics)
    {
        int num=0;
        int col=m_column;
        QRegExp CommentRex("^ *\\{(?:comment|c): *([^}]*) *\\}",Qt::CaseInsensitive);
        QRegExp CommentItalicRex("^ *\\{(?:comment-italic|ci): *([^}]*) *\\}",Qt::CaseInsensitive);
        QRegExp CommentBoxRex("^ *\\{(?:comment-box|cb): *([^}]*) *\\}",Qt::CaseInsensitive);

        QRegExp chordexp("([^[]*)\\[([^]]*)\\](.*)");
        PdfFont *pfont=m_document->CreateFont(m_uiconfig->toolButtonNormalFont->getFont().family().toLatin1());
        PdfFont *cfont=m_document->CreateFont(m_uiconfig->toolButtonChordFont->getFont().family().toLatin1());
        if ( ! text.isEmpty() )
        {
          if ( isColBreak(text)) doColumnBreak(text);
          else if ( text.contains(CommentRex))
          {
              Text(m_document,CommentRex.cap(1),m_column,m_line,m_uiconfig->toolButtonCommentFont);
               NextLine();
          }
          else if ( text.contains(CommentItalicRex))
          {
              Text(m_document,CommentItalicRex.cap(1),m_column,m_line,m_uiconfig->toolButtonCommentItalicFont);
               NextLine();
          }
          else if ( text.contains(CommentBoxRex))
          {
              TextInBox(m_document,CommentRex.cap(1),m_column,m_line,m_uiconfig->toolButtonCommentBoxFont);
               NextLine();
          }
          else if ( ! isChorus(text))
          {
          int positionchord=0;
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
                int lenght=pfont->GetFontMetrics()->StringWidth(PdfString (QString("%1 ").arg(c1).toLatin1()));

                if ( positionchord+lenght>=col && positionchord!=0)
                {
                    Drawline(positionchord,num,m_uiconfig->toolButtonChordFont);
                    col= positionchord;
                }
                   Text(m_document,c1,col,m_line+num,m_uiconfig->toolButtonChordFont);
                 positionchord=col+lenght;
               }
            else
               {
                num = m_uiconfig->spuChordHorizontalSize->getPdfU()+m_uiconfig->toolButtonChordFont->getFont().pointSizeF()*1.2;
                int col1=col-m_uiconfig->spuChordHorizontalSize->getPdfU()/2;
                 m_painter.Circle(col ,m_line,3);
                 m_painter.Fill(true);
                 m_painter.Circle(positionchord ,m_line,5);
                 m_painter.Fill(true);
                 int  ll= m_uiconfig->spuChordHorizontalSize->getPdfU()/2.0;
                int d=col - m_uiconfig->spuChordHorizontalSize->getPdfU()/2.0;
                if ( d < positionchord )
                {
                    col1=positionchord;
                }
                int l=m_line+m_uiconfig->spuChordHorizontalSize->getPdfU();
                displayChord(ch.chord(),l,col1,m_uiconfig->spuChordHorizontalSize->getPdfU(),m_uiconfig->comboBoxChordLang->currentData().toString());
                positionchord=col+m_uiconfig->spuChordHorizontalSize->getPdfU()/2.0;
                //+m_uiconfig->toolButtonChordFont->getFont().pointSizeF()*1.2;
               }
            text=chordexp.cap(3);
           }
          if ( (text ==tr("Refrain :") || text ==tr("Chorus :")) && m_uiconfig->comboBoxChordInText->currentIndex()== FormConfig::DiagramInText)
                  num = m_uiconfig->spuChordHorizontalSize->getPdfU();
          else if ( m_uiconfig->comboBoxChordInText->currentIndex()!= FormConfig::DiagramInText )
                  num= m_uiconfig->toolButtonChordFont->getFont().pointSizeF();
          Text(m_document,text,col,m_line,m_uiconfig->toolButtonNormalFont);
          }
          else // chorus
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
                   num = m_uiconfig->spuChordHorizontalSize->getPdfU()+m_uiconfig->toolButtonChordFont->getFont().pointSizeF()*1.2;
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


void ProcessorLyrics::Drawline( double pos, int num , FontButton *ptr )
{
    m_painter.Circle(pos ,m_line+num-ptr->getFont().pointSizeF()/2.0,1.3);
    m_painter.Fill(true);
    ///m_painter.DrawLine(pos,m_line+num-num-ptr->getFont().pointSizeF()/2.0,pos,m_line+num-num-ptr->getFont().pointSizeF()/4.0);
    m_painter.DrawLine(pos,m_line+num-ptr->getFont().pointSizeF()/2.0,pos+ptr->getFont().pointSizeF()/2.0,m_line+num-ptr->getFont().pointSizeF()/2.0);
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
