#include "dialogprocessmemory.h"
#include "ui_dialogprocessmemory.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QDebug>
#include <QRegExp>

DialogProcessMemory::DialogProcessMemory(QWidget *parent, QString songs, int position,QString title,  bool scrolling,  QFont font, QColor text, QColor background):
QDialog(parent),
ui(new Ui::DialogProcessMemory)
{
    ui->setupUi(this);
    QRect rect=qApp->desktop()->geometry();
    QFontMetrics fm(font);
    int H2=fm.height();
    if (position ==0 ) setGeometry(0,0,rect.width(),2*H2);
    else if  ( position==1 ) setGeometry(0,rect.height()/2-H2,rect.width(),H2*2);
    else setGeometry(0,rect.height()-H2*2,rect.width(),H2*2);

    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    setStyleSheet(QString("background-color:%1;").arg(background.name()));
    m_nblinecouplet=0;
    m_nblinerefrain=0;
    getInfo(songs,title);
}

DialogProcessMemory::~DialogProcessMemory()
{
    delete ui;
}

void DialogProcessMemory::getInfo( QString songs,QString title)
{
    QRegExp TitleREX("^ *\\{(?:title|t): *([^}]*)\\}",Qt::CaseInsensitive);
    QRegExp SocREX("^ *\\{(?:soc|start_of_chorus)\\}",Qt::CaseInsensitive);
    QRegExp EocREX("^ *\\{(?:eoc|end_of_chorus)\\}",Qt::CaseInsensitive);
    QRegExp SorREX("^ *\\{(?:sor|start_of_refrain)\\}",Qt::CaseInsensitive);
    QRegExp EorREX("^ *\\{(?:eor|end_of_refrain)\\}",Qt::CaseInsensitive);
    QRegExp TempoREX("^ *\\{(?:tempo): *([0-9]*)\\}",Qt::CaseInsensitive);
    QRegExp TimeREX("^ *\\{(?:time): *([1-5])/(1|2|4|8|16|32|64)\\}",Qt::CaseInsensitive);
    QRegExp OtherREX("^ *\\{");
    QStringList buf=songs.split("\n");
    bool found=false;
    int tempo=120;
     m_msecPerBar=MillisecondPerBeat(tempo);
    int timeup=4;
    int timedown=4;
    bool chorus=false;
    bool refrain=false;
    bool firstcouplet=false;
    bool refrainexist=false;
    bool refrainmade=false;
    int coupletindex=0;
    m_nblyrics=0;
    foreach ( QString line, buf)
    {
        if ( line.contains(TitleREX))
        {
            if ( found ) break;
            if (TitleREX.cap(1) == title)
                found =true;
        }
        else if ( found )
        {
            if ( line.contains(TempoREX))
            {
                tempo=TempoREX.cap(1).toInt();
                 m_msecPerBar=MillisecondPerBeat(tempo);
            }
            else if ( line.contains(TimeREX))
            {
                timeup=TimeREX.cap(1).toInt();
                timedown=TimeREX.cap(2).toInt();
            }
            else if (line.contains(SocREX))
                chorus=true;
            else if (line.contains(EocREX))
                chorus=false;
            else if (line.contains(SorREX))
            {
                m_nblinerefrain=0;
                refrain=true;
            }
            else if (line.contains(EorREX))
            {
                refrain=false;
                refrainmade=true;
            }
            else if (line.contains(OtherREX)) ;
            else if ( line.isEmpty())
            {
                firstcouplet=false;
                coupletindex=0;
                if ( refrainexist && ! refrainmade)
                {
                  int index=1;
                  foreach (QString ref, m_refrain)
                  {
                      m_nblyrics++;
                      m_lyrics[m_nblyrics]=ref;
                      m_seconds[m_nblyrics]=m_refrainnbbeat[index]*m_msecPerBar;
                      index++;
                  }
                }
            }
            else if (chorus)
                qWarning()<<"chorus"<<line ;
            else if ( refrain )
            {
                m_nblinerefrain++;
                int nbbeat=getNumberOfBeat(line,timeup);
                m_refrainnbbeat[m_nblinerefrain]=nbbeat;
                m_refrain<<line;
                m_nblyrics++;
                m_lyrics[m_nblyrics]=line;
                m_seconds[m_nblyrics]=m_msecPerBar*nbbeat;
                refrainexist=true;
                refrainmade=true;
            }
            else
            {
                if ( line.contains("[") || firstcouplet )
                {
                    firstcouplet=true;
                    m_nblinecouplet++;
                    int nbbeat=getNumberOfBeat(line,timeup);
                    m_coupletnbbeat[m_nblinecouplet]=nbbeat;
                    m_nblyrics++;
                    m_lyrics[m_nblyrics]=line;
                    m_seconds[m_nblyrics]=m_msecPerBar*nbbeat;
                    coupletindex=0;
                }
                else
                 {
                    coupletindex++;
                    m_nblyrics++;
                    m_lyrics[m_nblyrics]=line;
                    m_seconds[m_nblyrics]=m_coupletnbbeat[coupletindex]*m_msecPerBar;
                    refrainmade=false;
                 }
           }
        }
    }
    foreach ( int i, m_lyrics.keys())
    {
        qWarning()<<m_lyrics[i];
        qWarning()<<m_seconds[i];
    }

}

int DialogProcessMemory::MillisecondPerBeat( int tempo )
{
    return 6000  / tempo;
}

int DialogProcessMemory::getNumberOfBeat(QString &line,int timeup)
{
    int number=0;

    QRegExp chordEx("\\[([^]]*)\\]");
    while ( line.indexOf(chordEx)!=-1)
    {
        QString chord=chordEx.cap(1);
        line.replace(QString("[%1]").arg(chordEx.cap(1)),"");
        QRegExp chord1("x([0-9]+)");
        QRegExp chord2(":([1-4]+)");
        if ( chord.contains(chord1) )
        {   bool ok;
            int nb=chord1.cap(1).toInt(&ok);
            if ( ok )
              number+=timeup*nb;
            else
              number+=timeup;
        }
        else if ( chord.contains(chord2) )
        {
            bool ok;
            int nb=chord2.cap(1).toInt(&ok);
            if ( ok )
            if (chord.contains(chord2)) number+=nb;
            else number+=timeup;
        }
        else number+=timeup;
    }
    return number;
}
