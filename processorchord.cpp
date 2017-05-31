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
    m_mode="chord";
}

void ProcessorChord::displayLyrics()
{
    m_vm0=10;
    m_vm=0;
    if ( !m_rythm.contains("/"))
        m_nbBeatPerBar=4;
    else
        m_nbBeatPerBar=m_rythm.split("/").at(1).toInt();
    m_barsperline=4;
    m_fontchordsize=m_uiconfig->toolButtonChordFont->getFont().pointSize();
    m_position=1;
    m_w=m_fontchordsize*3;
    m_h=m_fontchordsize*2;
    m_x0=m_uiconfig->spuPageWidth->getPdfU()/3;
    m_y0=m_uiconfig->spuPageHeight->getPdfU()/2;
    int nbeat=0;
    int col=10;
    QRegExp regChord("([^[]*)\\[([^]]+)\\](.*)",Qt::CaseInsensitive);
    foreach ( QString line, m_BufLyrics)
    {
        if ( line =="SOC" || line=="EOC" || line =="SOR" || line == "EOR" || nbeat>m_nbBeatPerBar )
        {
            nbeat=0;
        }
        while (line.indexOf(regChord)!=-1)
        {
            QString ch=regChord.cap(2);

            Chord chord(ch,m_uimainwindow->comboBoxChordLanguage->currentData().toString());
            if ( chord.nbBeat() >=1 )
            {
              m_beats[chord.nameEnglish()]=chord.nbBeat();
              if ( !m_beats.isEmpty()  )
              {
                QStringList vallist;
                foreach ( QString k, m_beats.keys())  vallist<<QString("%1:%2").arg(k).arg(m_beats[k]);
                m_bar<<vallist.join("|");
                m_beats.clear();
                nbeat++;
                if (nbeat==m_nbBeatPerBar)
                {
                    DisplayBars(m_bar,m_position);
                    m_position++;
                    nbeat=0;
                    m_bar.clear();
                }
              }
            }
            else if (chord.nbBar()>=1 )
            {
                for ( int note=1; note<=chord.nbBar(); note ++)
                {
                   if ( note == 1 ) m_bar<<chord.nameEnglish();
                   else m_bar<<"%";
                   nbeat++;
                   if (nbeat==m_nbBeatPerBar)
                   {
                       DisplayBars(m_bar,m_position);
                       m_position++;
                       nbeat=0;
                       m_bar.clear();
                   }
                }
            }
//            Text(m_document,chord.nameEnglish(),col,m_line,m_uiconfig->toolButtonChordFont);
//            col+=10;
//            m_line+=10;
          line=regChord.cap(3);
        }
    }
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



void ProcessorChord::displayBpm()
{
    m_subtitlenumber++;
    if ( m_uiconfig->toolButtonSubtitleFont->getBackgroundColor() != m_uiconfig->colorButtonPaperColor->getColor())
    {
      m_painter.SetColor(m_uiconfig->toolButtonSubtitleFont->getBackgroundColor().redF(),m_uiconfig->toolButtonSubtitleFont->getBackgroundColor().greenF(),m_uiconfig->toolButtonSubtitleFont->getBackgroundColor().blueF());
      m_painter.Rectangle(m_uiconfig->spuHorizontalMargin->getPdfU(),
                          m_uiconfig->spuPageHeight->getPdfU()-m_uiconfig->spuVerticalMargin->getPdfU()-m_uiconfig->toolButtonTitleFont->getFont().pointSize()-m_subtitlenumber*m_uiconfig->toolButtonSubtitleFont->getFont().pointSize(),//*1.4-1,
                          m_uiconfig->spuPageWidth->getPdfU()-2*m_uiconfig->spuHorizontalMargin->getPdfU(),
                          m_uiconfig->toolButtonSubtitleFont->getFont().pointSize());
      m_painter.Fill();
    }
    m_line-=m_uiconfig->toolButtonSubtitleFont->getFont().pointSize();
    Text(m_document,tr("  Rythm : %1").arg(m_rythm),m_uiconfig->spuHorizontalMargin->getPdfU(),
         m_line,
         m_uiconfig->toolButtonSubtitleFont,left);
    Text(m_document,tr("Bpm : %1  ").arg(m_bpm),m_uiconfig->spuPageWidth->getPdfU(),
         m_line,
         m_uiconfig->toolButtonSubtitleFont,right);

}


void ProcessorChord::DisplayBars(QStringList ch, int position)
{
  m_painter.Rectangle(m_x0,m_y0-(position-1)*m_h-m_vm,m_w*m_barsperline,m_h);
  m_painter.Stroke();
  for ( int i=1 ; i <=m_barsperline ;i++)
   {
       m_painter.DrawLine(m_x0+i*m_w,m_y0-(position-2)*m_h-m_vm,
                          m_x0+i*m_w,m_y0-(position-1)*m_h-m_vm);
   }
  int i=0;
  foreach ( QString c, ch)
   {
      double x=m_x0+(i+0.5)*m_w;
      double y=m_y0-(position -1.33)*m_h-m_vm;
      i++;
      Text(m_document,c,x,y,m_uiconfig->toolButtonChordFont,center);
   }
  m_vm+=m_vm0;
}


bool ProcessorChord::CompleteBeats ()
{
    double sum=0;
    foreach (int val, m_beats.values())
         {sum=+1.0/val;}
    return  ( round(sum*100)== 100 );
}
