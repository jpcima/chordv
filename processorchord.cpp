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
    if ( !m_rythm.contains("/"))
        m_nbBeatPerBar=4;
    else
        m_nbBeatPerBar=m_rythm.split("/").at(1).toInt();
  //  m_nbBeatPerBar/=4;
    m_h=80;
    m_w=100;
    m_x0=m_uiconfig->spuHorizontalMargin->getPdfU();
    m_y0=m_initialhposition;
    int nbeat=0;
    int col=10;
    QRegExp regChord("([^[]*)\\[([^]]+)\\](.*)",Qt::CaseInsensitive);
    qDebug()<<m_title;
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
                    qDebug()<<m_bar;
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
                       qDebug()<<m_bar;
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


void ProcessorChord::Rectangle(QStringList ch,int type, int positionx,int positiony)
{
    m_painter.Rectangle(m_x0+(positionx-1)*m_w,m_y0+(positiony-1)*m_h,m_w,m_h);
    if ( type==1) m_painter.DrawText(m_x0+(positionx-1)*m_w/2,m_y0+(positiony-1)*m_h/2,
                                     PdfString(ch.at(0).toLocal8Bit()));
    else if ( type == 2 )
    {
        m_painter.DrawLine(m_x0+(positionx-1)*m_w,m_y0+(positiony-1)*m_h,m_x0+positionx*m_w,m_y0+positiony*m_h);
    }
}


bool ProcessorChord::CompleteBeats ()
{
    double sum=0;
    foreach (int val, m_beats.values())
         {sum=+1.0/val;}
    return  ( round(sum*100)== 100 );
}
