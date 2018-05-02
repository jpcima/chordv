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
    //m_vm0=10;
    m_vm=10;
    m_hm=0;
    if ( !m_time.contains("/"))
        m_nbBeatPerBar=4;
    else
        m_nbBeatPerBar=m_time.split("/").at(1).toInt();
    m_barsperline=4; // Unused ?
    m_fontchordsize=m_uiconfig->toolButtonChordFont->getFont().pointSize();
    m_w=m_fontchordsize*4.5;
    m_h=m_fontchordsize*3;
    m_x0=m_uiconfig->spuPageWidth->getPdfU()/5;

    QRegExp regChord("([^[]*)\\[([^]]+)\\](.*)",Qt::CaseInsensitive);

    m_posx=0;
    foreach ( QString line, m_BufLyrics)
    {
        if ( line ==tr("  Refrain :") || line=="  Chorus :" || m_posx>m_nbBeatPerBar )
        {
            SubBar2Bar();
            m_posx=0;
            m_line-=m_h+m_vm;
            Text(m_document,line,m_uiconfig->spuHorizontalMargin->getPdfU(),m_line,m_uiconfig->toolButtonChordFont);
            m_line-=m_uiconfig->toolButtonChordFont->getFont().pointSize();
        }
        if ( line == tr("End of chorus") || line =="End of refrain")
        {
            SubBar2Bar();
            m_posx=0;
            m_line-=m_h+4*m_vm;
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
                SubBar2Bar();
                for ( int note=1; note<=chord.nbBar(); note ++)
                {
                   if ( note == 1 ) DisplayBar(chord.nameEnglish());
                   else DisplayBar("%");
                }
            }
          line=regChord.cap(3);
        }

    }
    SubBar2Bar();
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
    QStringList chordlist,bar;
    QStringList temp=m_subbar;
    int nbbeat=0;
    foreach ( QString b, m_subbar)
    {
        nbbeat++;
        chordlist<<b;
        if ( CompleteBeats(m_subbar, nbbeat))
        {
            bar<<chordlist.join("|");
            nbbeat=0;
            for ( int i =0 ; i<chordlist.count(); i++ ) temp.removeFirst();
            chordlist.clear();
        }
    }
    m_subbar=temp;
    foreach ( QString chord, bar)
    {
        DisplayBar(chord);
    }
    m_subbar.clear();
}





void ProcessorChord::includeSor()
{

    m_BufLyrics<<tr("  Refrain :");
}

void ProcessorChord::includeSoc()
{
    m_BufLyrics<<tr("  Chorus :");
}


void ProcessorChord::displayBpm()
{
    if ( m_uiconfig->toolButtonSubtitleFont->getBackgroundColor() != m_uiconfig->colorButtonPaperColor->getColor())
    {
      m_painter.SetColor(m_uiconfig->toolButtonSubtitleFont->getBackgroundColor().redF(),m_uiconfig->toolButtonSubtitleFont->getBackgroundColor().greenF(),m_uiconfig->toolButtonSubtitleFont->getBackgroundColor().blueF());
      m_painter.Rectangle(m_uiconfig->spuHorizontalMargin->getPdfU(),
                          m_uiconfig->spuPageHeight->getPdfU()-m_uiconfig->spuVerticalMargin->getPdfU()-m_uiconfig->toolButtonTitleFont->getFont().pointSize()-m_uiconfig->toolButtonSubtitleFont->getFont().pointSize(),//*1.4-1,
                          m_uiconfig->spuPageWidth->getPdfU()-2*m_uiconfig->spuHorizontalMargin->getPdfU(),
                          m_uiconfig->toolButtonSubtitleFont->getFont().pointSize());
      m_painter.Fill();
    }
    m_line-=m_uiconfig->toolButtonSubtitleFont->getFont().pointSize();
    Text(m_document,tr("  Time : %1").arg(m_time),m_uiconfig->spuHorizontalMargin->getPdfU(),
         m_line,
         m_uiconfig->toolButtonSubtitleFont,left);
    Text(m_document,tr("Tempo : %1  ").arg(m_tempo),m_uiconfig->spuPageWidth->getPdfU(),
         m_line,
         m_uiconfig->toolButtonSubtitleFont,right);

}

void ProcessorChord::DisplayBar(QString ch )
{

    if ( !m_pageAllocation)
    {
       m_page = m_document->CreatePage(*m_dimension);
       m_painter.SetPage(m_page);
       m_pageAllocation=true;
    }
    m_painter.Rectangle(m_x0 + m_posx * m_w , m_line  , m_w ,  m_h );
    m_painter.Stroke();
    QStringList chords=ch.split("|");
    if ( chords.count()==1 )
    {
        double x=m_x0+(m_posx+0.5)*m_w;
        double y=m_line+0.33*m_h;
        Text(m_document,ch.split(":").at(0),x,y,m_uiconfig->toolButtonChordFont,center);
    }
    else if ( chords.count() == 2 )
    {
        m_painter.DrawLine(m_x0+m_posx*m_w,m_line ,m_x0+m_posx*m_w+m_w,m_line +m_h);
        double x=m_x0+(m_posx+0.25)*m_w;
        double y=m_line+0.53*m_h;
        Text(m_document,chords.at(0).split(":").at(0),x,y,m_uiconfig->toolButtonChordFont,center);
        x=m_x0+(m_posx+0.75)*m_w;
        y=m_line+0.17*m_h;
        Text(m_document,chords.at(1).split(":").at(0),x,y,m_uiconfig->toolButtonChordFont,center);
    }
    else if ( chords.count()==3)
    {
        QStringList beatlist;
        beatlist<<chords.at(0).split(":").at(1);
        beatlist<<chords.at(1).split(":").at(1);
        beatlist<<chords.at(2).split(":").at(1);
        QString sequence=beatlist.join("");
        if ( sequence == "244")
        {
            m_painter.DrawLine(m_x0+m_posx*m_w,m_line ,m_x0+m_posx*m_w+m_w,m_line +m_h);
            m_painter.DrawLine(m_x0+(m_posx+0.5)*m_w,m_line+0.5*m_h ,m_x0+m_posx*m_w+m_w,m_line);
            double x=m_x0+(m_posx+0.25)*m_w;
            double y=m_line+0.53*m_h;
            Text(m_document,chords.at(0).split(":").at(0),x,y,m_uiconfig->toolButtonChordFont,center);
            x=m_x0+(m_posx+0.80)*m_w;
            y=m_line+0.40*m_h;
            Text(m_document,chords.at(1).split(":").at(0),x,y,m_uiconfig->toolButtonChordFont,center,0.75);
            x=m_x0+(m_posx+0.50)*m_w;
            y=m_line+0.15*m_h;
            Text(m_document,chords.at(2).split(":").at(0),x,y,m_uiconfig->toolButtonChordFont,center,0.75);
        }
        else if ( sequence == "424")
        {
            m_painter.DrawLine(m_x0+m_posx*m_w,m_line+m_h ,m_x0+m_posx*m_w+m_w,m_line);
            m_painter.DrawLine(m_x0+m_posx*m_w,m_line ,m_x0+(m_posx-0.5)*m_w+m_w,m_line +m_h*0.5);
            double x=m_x0+(m_posx+0.20)*m_w;
            double y=m_line+0.40*m_h;
            Text(m_document,chords.at(0).split(":").at(0),x,y,m_uiconfig->toolButtonChordFont,center,0.75);
            x=m_x0+(m_posx+0.75)*m_w;
            y=m_line+0.5*m_h;
            Text(m_document,chords.at(1).split(":").at(0),x,y,m_uiconfig->toolButtonChordFont,center);
            x=m_x0+(m_posx+0.50)*m_w;
            y=m_line+0.15*m_h;
            Text(m_document,chords.at(2).split(":").at(0),x,y,m_uiconfig->toolButtonChordFont,center,0.75);

        }
        else if ( sequence == "442")
        {
            m_painter.DrawLine(m_x0+m_posx*m_w,m_line ,m_x0+m_posx*m_w+m_w,m_line +m_h);
            m_painter.DrawLine(m_x0+m_posx*m_w,m_line+m_h,  m_x0+(m_posx-0.5)*m_w+m_w,m_line+m_h*0.5);
            double x=m_x0+(m_posx+0.20)*m_w;
            double y=m_line+0.40*m_h;
            Text(m_document,chords.at(0).split(":").at(0),x,y,m_uiconfig->toolButtonChordFont,center,0.75);
            x=m_x0+(m_posx+0.50)*m_w;
            y=m_line+0.70*m_h;
            Text(m_document,chords.at(1).split(":").at(0),x,y,m_uiconfig->toolButtonChordFont,center,0.75);
            x=m_x0+(m_posx+0.75)*m_w;
            y=m_line+0.17*m_h;
            Text(m_document,chords.at(2).split(":").at(0),x,y,m_uiconfig->toolButtonChordFont,center);
        }
    }
    else if ( chords.count()==4)
    {
         m_painter.DrawLine(m_x0+m_posx*m_w,m_line ,m_x0+m_posx*m_w+m_w,m_line +m_h);
         m_painter.DrawLine(m_x0+m_posx*m_w,m_line+m_h ,m_x0+m_posx*m_w+m_w,m_line);
         double x=m_x0+(m_posx+0.20)*m_w;
         double y=m_line+0.40*m_h;
         Text(m_document,chords.at(0).split(":").at(0),x,y,m_uiconfig->toolButtonChordFont,center,0.75);
         x=m_x0+(m_posx+0.50)*m_w;
         y=m_line+0.70*m_h;
         Text(m_document,chords.at(1).split(":").at(0),x,y,m_uiconfig->toolButtonChordFont,center,0.75);
         x=m_x0+(m_posx+0.80)*m_w;
         y=m_line+0.40*m_h;
        Text(m_document,chords.at(2).split(":").at(0),x,y,m_uiconfig->toolButtonChordFont,center,0.75);
         x=m_x0+(m_posx+0.50)*m_w;
         y=m_line+0.15*m_h;
        Text(m_document,chords.at(3).split(":").at(0),x,y,m_uiconfig->toolButtonChordFont,center,0.75);
    }
    if ( m_posx == 3)
        {
            m_posx=0;
            m_line-=m_h+m_vm;
        }
     else m_posx++;
}


