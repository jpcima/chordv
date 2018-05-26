#include "dialogprocessmemory.h"
#include "ui_dialogprocessmemory.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QDebug>
#include <QRegExp>
#include <QTimer>

DialogProcessMemory::DialogProcessMemory(QWidget *parent, QString songs, int position,QString title,  bool showrythm,  QFont font, QColor textcolor, QColor background, bool fullScreen):
QDialog(parent),
ui(new Ui::DialogProcessMemory)
{
    ui->setupUi(this);
    m_font=font;
    m_showrythm=showrythm;
    m_textcolor=textcolor;
    m_backgroundcolor=background;
    m_countrythm=1;
    QRect rect=qApp->desktop()->geometry();
    QFontMetrics fm(font);
    if ( fullScreen )
    {
        setGeometry(0,0,rect.width(),rect.height());
    }
    else
    {
       int H2=fm.height();
       if (position ==0 ) setGeometry(0,0,rect.width(),2*H2);
       else if  ( position==1 ) setGeometry(0,rect.height()/2-H2,rect.width(),H2*2);
       else setGeometry(0,rect.height()-H2*2,rect.width(),H2*2);
    }
    if ( ! m_showrythm ) ui->labelTimeBullet->setVisible(false);

    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    setStyleSheet(QString("background-color:%1;color:%2;").arg(m_backgroundcolor.name()).arg(m_textcolor.name()));
    ui->labelText1->setFont(m_font);
    ui->labelText2->setFont(m_font);
    m_nblinecouplet=0;
    m_nblinerefrain=0;
    getInfo(songs,title);
    m_indice=0;
    m_timer=0;
    m_timerclearrythm=0;
    displaySong();
    if ( m_showrythm)
    {
        m_timerrythm = new QTimer ;
        connect(m_timerrythm, SIGNAL(timeout()), this, SLOT(showRythm()));
        m_timerrythm->setInterval(m_msecPerBar);
        qDebug()<<m_msecPerBar;
        m_timerrythm->start();
    }
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
    m_tempo=120;
    m_msecPerBar=MillisecondPerBeat(m_tempo);
    m_timeup=4;
    bool chorus=false;
    bool refrain=false;
    bool firstcouplet=false;
    bool refrainexist=false;
    bool refrainmade=false;
    int coupletindex=0;
    m_nblyrics=0;
    ui->labelText1->setFont(m_font);
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
                m_tempo=TempoREX.cap(1).toInt();
                m_msecPerBar=MillisecondPerBeat(m_tempo);
            }
            else if ( line.contains(TimeREX))
            {
                m_timeup=TimeREX.cap(1).toInt();
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
            {
             m_nblyrics++;
             int nbbeat=getNumberOfBeat(line,m_timeup);
             m_lyrics[m_nblyrics]="...";
             m_seconds[m_nblyrics]=m_msecPerBar*nbbeat;
            }
            else if ( refrain )
            {
                m_nblinerefrain++;
                int nbbeat=getNumberOfBeat(line,m_timeup);
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
                    int nbbeat=getNumberOfBeat(line,m_timeup);
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

}

int DialogProcessMemory::MillisecondPerBeat( int tempo )
{
    return 60000  / tempo;
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
               number+=nb;
            else number+=timeup;
        }
        else number+=timeup;
    }
    return number;
}


void DialogProcessMemory::displaySong()
{
    m_indice++;
    if (m_timer!=0) delete(m_timer);
    if ( m_indice <= m_nblyrics)
        displayLine();
    else
    {
        QTimer *timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(close()));
        timer->start(3000);
    }
}

void DialogProcessMemory::displayLine()
{
    ui->labelText1->setText(m_lyrics[m_indice]);
    if ( m_indice+1 <= m_nblyrics) ui->labelText2->setText(m_lyrics[m_indice+1]);
    else ui->labelText2->setText(">");
    if ( m_indice != m_nblyrics)
    {
      m_timer = new QTimer;
      connect(m_timer, SIGNAL(timeout()), this, SLOT(displaySong()));
      m_timer->start(m_seconds[m_indice]);
    }
}

void DialogProcessMemory::showRythm()
{
    if ( m_countrythm % m_timeup == 1 ) ui->labelTimeBullet->setPixmap(QPixmap("../Images/redbull.png"));
    else ui->labelTimeBullet->setPixmap(QPixmap("../Images/greenbull.png"));
    m_countrythm++;
    if ( m_timerclearrythm != 0 ) delete m_timerclearrythm;
    qWarning()<<m_indice<<m_nblyrics;
    if (  m_indice <= m_nblyrics)
    {
       m_timerclearrythm = new QTimer;
       connect(m_timerclearrythm, SIGNAL(timeout()), this, SLOT(eraseBull()));
       m_timerclearrythm->start(300);
    }
    else delete m_timerrythm;
}

void DialogProcessMemory::eraseBull()
{
    ui->labelTimeBullet->setPixmap(QPixmap());
}
