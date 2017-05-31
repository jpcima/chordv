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

    if ( m_firstline )
    {
        m_firstline=false;
        m_line-=m_uiconfig->toolButtonNormalFont->getFont().pointSizeF()*3;
        m_initialhposition=m_line;
    }
    m_vm0=10;
    m_vm=0;
    m_hm=0;
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
            Text(m_document,line,m_uiconfig->spuHorizontalMargin->getPdfU(),m_line,m_uiconfig->toolButtonChordFont);
        }
        while (line.indexOf(regChord)!=-1)
        {
            QString ch=regChord.cap(2);

            Chord chord(ch,m_uimainwindow->comboBoxChordLanguage->currentData().toString());
            if ( chord.nbBeat() >=1 )
            {
                m_subbar<<QString("%1:%2").arg(chord.nameEnglish()).arg(chord.nbBeat());
            }
            else if (chord.nbBar()>=1 )
            {
                //SubBar2Bar();
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



bool ProcessorChord::CompleteBeats (QStringList chordlist, int nbbeat)
{
    double sum=0;
    foreach ( QString ch ,chordlist)
    {
        if ( nbbeat == 0 ) return round(sum*100)== 100;
        int val= ch.split(":").last().toInt();
        if (val != 0 ) sum+=1.0/val;
        nbbeat--;
    }
    return round(sum*100)== 100 ;
}

void ProcessorChord::SubBar2Bar()
{
    QStringList chordlist;
    qDebug()<<m_subbar;
    QStringList m_temp=m_subbar;
    int nbbeat=0;
    foreach ( QString b, m_subbar)
    {
        QStringList l=b.split(":");
        nbbeat++;
        chordlist<<b;
        if ( CompleteBeats(m_subbar, nbbeat))
        {
            m_bar<<chordlist.join("|");
            nbbeat=0;
            for ( int i =0 ; i<chordlist.count(); i++ ) m_temp.removeFirst();
            chordlist.clear();
        }
    }
    m_subbar=m_temp;
    qDebug()<<m_subbar;
    foreach ( QString chord, m_subbar)
    {
        DisplayBar(chord);
        if (m_posx==4)  { m_posx=1; m_posy+=1+m_vm; }
        else m_posx++;
    }
    m_subbar.clear();
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

void ProcessorChord::DisplayBar(QString ch )
{
    m_painter.Rectangle(m_x0 + m_posx * m_w , m_y0 - m_posy *m_h ,m_w,m_h );
    m_painter.Stroke();
    QStringList chords=ch.split("|");
    if ( chords.count()==1 )
    {
        double x=m_x0+(m_posx+0.5)*m_w;
        double y=m_y0-(m_posy -1.33)*m_h;
        Text(m_document,ch,x,y,m_uiconfig->toolButtonChordFont,center);
    }
    else if ( chords.count() == 2 )
    {
        m_painter.DrawLine(m_x0+m_posx*m_w,m_y0 - m_posy *m_h,m_x0+m_posx*m_w+m_w,m_y0 - m_posy *m_h+m_h);
        double x= x=m_x0+(m_posx+1.0/4)*m_w;
        double y=m_y0-(m_posy -1.33*2)*m_h;
        Text(m_document,chords.at(0),x,y,m_uiconfig->toolButtonChordFont,center);
        x=m_x0+(m_posx+3.0/4)*m_w;
        y=m_y0-(m_posy +1.33*2)*m_h;
        Text(m_document,chords.at(1),x,y,m_uiconfig->toolButtonChordFont,center);
    }
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

