#include "dialogprocessmemory.h"
#include "ui_dialogprocessmemory.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QDebug>
#include <QRegExp>
#include <QTimer>
#include <QKeyEvent>
#include <QFontMetrics>
#include <QMessageBox>


DialogProcessMemory::DialogProcessMemory(QWidget *parent, QString songs, int position,QString title,  bool showrythm,
                                         bool click, int volume, bool accentuedfirst ,QFont font, QColor textcolor, QColor background, bool fullScreen, bool twolines, double advance,
                                         int nbbeatbefore, bool jacksynchro):
QDialog(parent),
ui(new Ui::DialogProcessMemory)
{
    ui->setupUi(this);
    m_player= new QMediaPlayer;
    m_stop=false;
    m_pause=false;
    m_jacksynchro=jacksynchro;
    m_font=font;
    m_showrythm=showrythm;
    m_textcolor=textcolor;
    m_backgroundcolor=background;
    m_countrythm=1;
    m_advance=advance;
    m_timebefore=nbbeatbefore;
    m_volume=volume;
    m_click=click;
    m_firststart=true;
    m_accentuedfirst=accentuedfirst;
    m_status=NotStarted;
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

    setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    setStyleSheet(QString("background-color:%1").arg(m_backgroundcolor.name()));
    ui->labelText1->setFont(m_font);
    ui->labelText1->setStyleSheet(QString("color:%1;").arg(m_textcolor.name()));
    ui->labelText2->setFont(m_font);
    ui->labelText2->setStyleSheet(QString("color:%1;").arg(getColorBetween(m_backgroundcolor, m_textcolor).name()));
    if ( ! twolines) ui->labelText2->setVisible(false);
    m_nblinecouplet=0;
    m_nblinerefrain=0;
    getInfo(songs,title);
    m_period=m_millisecondperbeat/4;
    m_indice=0;
    m_timerend=0;
    m_timerclearrythm=0;
    m_timerrythm=0;
    m_timerlyrics=0;
    m_time=0;
    m_jackclient=0;


    if ( m_jacksynchro)
    {
        jack_status_t  status;
        if ((m_jackclient = jack_client_open ("chordVJack", JackNoStartServer,&status)) == 0) {
             QMessageBox::warning(0,tr("Jack not found"),tr("Jack seems to not be launched ! \n(Try to launch Jack manually without QJackCtl)"));
             m_jacksynchro=false;
            }
        else
        {
            if (jack_activate (m_jackclient) ){
                QMessageBox::warning(0,tr("Jack problem"),tr("Jack cannot be activated !"));
                m_jacksynchro=false;
                }
            else
            {
                m_timeline = new QTimer;
                connect(m_timeline, SIGNAL(timeout()), this, SLOT(JackMessages()));
                m_timeline->setInterval(m_period);
                m_timeline->start();
            }
        }
    }
    if (  m_showrythm || m_click )
    {
        m_timerrythm = new QTimer ;
        connect(m_timerrythm, SIGNAL(timeout()), this, SLOT(showRythm()));
        m_timerrythm->setInterval(m_millisecondperbeat);
        if ( ! m_jacksynchro )
            m_timerrythm->start();
        else m_pause=true;
    }
    connect (this,SIGNAL(rejected()),this,SLOT(Close()));
    if ( ! m_jacksynchro ) Start();

}

void DialogProcessMemory::Start()
{
    QTimer::singleShot(m_timebefore*m_millisecondperbeat*m_timeup-1000*m_advance, this, SLOT(WaitBeforeStart()));
}


void DialogProcessMemory::JackMessages()
{
    jack_position_t current;
    jack_transport_state_t transport_state;
    jack_nframes_t frame_time;
    transport_state = jack_transport_query (m_jackclient, &current);
    frame_time = jack_frame_time (m_jackclient);
    switch (transport_state) {
        case JackTransportStopped:
            if (m_status==Running)
            {
                m_status=Paused;
                if ( m_timerrythm ) m_timerrythm->stop();
                if ( m_timerlyrics) m_timerlyrics->stop();
            }
            break;
        case JackTransportRolling:
            if (m_firststart) Start();
            m_firststart=false;
            if (m_status!=Running)
            {
                m_status=Running;
                if ( m_timerrythm ) m_timerrythm->start();
                if ( m_timerlyrics) m_timerlyrics->start();
            }
            break;
        case JackTransportStarting:
            qWarning()<<"state: Starting";
            break;
        default:
            qWarning()<<"state: [unknown]";
        }
}

void DialogProcessMemory::WaitBeforeStart()
{
    displaySong();
}

DialogProcessMemory::~DialogProcessMemory()
{
    delete m_player;
    if (m_jackclient) delete m_jackclient;
    delete ui;

}

void DialogProcessMemory::getInfo( QString songs,QString title)
{
    QRegExp TitleREX("^ *\\{(?:title|t): *([^}]*)\\}",Qt::CaseInsensitive);
    QRegExp SocREX("^ *\\{(?:soc|start_of_chorus)\\}",Qt::CaseInsensitive);
    QRegExp EocREX("^ *\\{(?:eoc|end_of_chorus)\\}",Qt::CaseInsensitive);
    QRegExp SorREX("^ *\\{(?:sor|start_of_refrain)\\}",Qt::CaseInsensitive);
    QRegExp EorREX("^ *\\{(?:eor|end_of_refrain)\\}",Qt::CaseInsensitive);
    QRegExp TempoREX("^ *\\{(?:tempo): *([0-9.]*)\\}",Qt::CaseInsensitive);
    QRegExp TimeREX("^ *\\{(?:time): *([1-5])/(1|2|4|8|16|32|64)\\}",Qt::CaseInsensitive);
    QRegExp OtherREX("^ *\\{");
    QStringList buf=songs.split("\n");
    bool found=false;
    m_tempo=120;
    m_millisecondperbeat=60000/m_tempo;
    m_timeup=4;
    bool chorus=false;
    bool refrain=false;
    bool firstcouplet=false;
    bool refrainexist=false;
    bool refrainmade=false;
    int coupletindex=0;
    m_nblyrics=0;
    ui->labelText1->setFont(m_font);
    bool firstline=true;
    bool tocomplete=false;
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
                m_tempo=TempoREX.cap(1).toDouble();
                if ( m_tempo<1) m_tempo=120;
                qDebug()<<"tempo"<<m_tempo;
                m_millisecondperbeat=60000/m_tempo;
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
                      m_seconds[m_nblyrics]=m_refrainnbbeat[index]*m_millisecondperbeat;
                      index++;
                  }
                }
            }
            else if (chorus)
            {
             m_nblyrics++;
             int nbbeat=getNumberOfBeat(line,m_timeup);
             m_lyrics[m_nblyrics]="...";
             m_seconds[m_nblyrics]=m_millisecondperbeat*nbbeat;
            }
            else if ( refrain )
            {
                m_nblinerefrain++;
                if ( firstline )
                {
                    QRegExp splitREX("^([^[]+)(.*)");
                    if ( line.contains(splitREX))
                    {
                       m_nblyrics++;
                       m_lyrics[m_nblyrics]=splitREX.cap(1);
                       line=splitREX.cap(2);
                       tocomplete=true;
                    }
                }
                firstline=false;
                int nbbeat=getNumberOfBeat(line,m_timeup);
                m_refrainnbbeat[m_nblinerefrain]=nbbeat;
                m_refrain<<line;
                m_nblyrics++;
                m_lyrics[m_nblyrics]=line;
                m_seconds[m_nblyrics]=m_millisecondperbeat*nbbeat;
                refrainexist=true;
                refrainmade=true;
            }
            else
            {
                if ( line.contains("[") || firstcouplet )
                {
                    firstcouplet=true;
                    m_nblinecouplet++;
                    if ( firstline )
                    {
                        QRegExp splitREX("^([^[]+)(.*)");
                        if ( line.contains(splitREX))
                        {
                           m_nblyrics++;
                           m_lyrics[m_nblyrics]=splitREX.cap(1);
                           line=splitREX.cap(2);
                           tocomplete=true;
                        }
                    }
                    firstline=false;
                    int nbbeat=getNumberOfBeat(line,m_timeup);
                    m_coupletnbbeat[m_nblinecouplet]=nbbeat;
                    m_nblyrics++;
                    m_lyrics[m_nblyrics]=line;
                    m_seconds[m_nblyrics]=m_millisecondperbeat*nbbeat;
                    coupletindex=0;
                }
                else
                 {
                    coupletindex++;
                    m_nblyrics++;
                    m_lyrics[m_nblyrics]=line;
                    m_seconds[m_nblyrics]=m_coupletnbbeat[coupletindex]*m_millisecondperbeat;
                    refrainmade=false;
                 }
           }
        }
    }
    if ( tocomplete )
    {
        QFontMetrics fm(m_font);

        while ( fm.width(m_lyrics[1])< fm.width(m_lyrics[2]))
            m_lyrics[1]=" "+m_lyrics[1];
        m_seconds[1]=m_seconds[2];
    }

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
    if (m_timerlyrics!=0) m_timerlyrics->stop();
    if ( ! m_stop )
        displayLine();
    else
    {
        m_timerclearrythm->stop();
        m_timerrythm->stop();
        m_timerend = new QTimer(this);
        connect(m_timerend, SIGNAL(timeout()), this, SLOT(close()));
        m_timerend->start(1000);
    }
}

void DialogProcessMemory::displayLine()
{
    ui->labelText1->setText(m_lyrics[m_indice]);
    if ( m_indice+1 <= m_nblyrics) ui->labelText2->setText(m_lyrics[m_indice+1]);
    else
      ui->labelText2->setText("");
    if ( m_indice <= m_nblyrics)
    {
      m_timerlyrics = new QTimer;
      connect(m_timerlyrics, SIGNAL(timeout()), this, SLOT(displaySong()));
      m_timerlyrics->start(m_seconds[m_indice]);
    }
    else
    {
        m_stop=true;
        displaySong();
    }
}

void DialogProcessMemory::showRythm()
{

    if ( m_click )
    {
       if (m_accentuedfirst && m_countrythm % m_timeup == 1) m_player->setMedia(QUrl("qrc:/sound/1.wav"));
       else  m_player->setMedia(QUrl("qrc:/sound/2.wav"));
       m_player->setVolume(m_volume);
       m_player->play();
    }
    if ( m_showrythm )
    {
        if ( m_countrythm % m_timeup == 1 ) ui->labelTimeBullet->setPixmap(QPixmap(":/Image/Images/redbull.png"));
        else ui->labelTimeBullet->setPixmap(QPixmap(":/Image/Images/greenbull.png"));
    }
    m_countrythm++;
    if ( m_timerclearrythm != 0 )  delete m_timerclearrythm;
    if (  m_showrythm &&  m_indice <= m_nblyrics)
    {
       m_timerclearrythm = new QTimer;
       connect(m_timerclearrythm, SIGNAL(timeout()), this, SLOT(eraseBull()));
       m_timerclearrythm->start(300);
    }
    else if ( m_showrythm ) delete m_timerrythm;

}

void DialogProcessMemory::eraseBull()
{
    ui->labelTimeBullet->setPixmap(QPixmap());
}


QColor DialogProcessMemory::getColorBetween(QColor color1, QColor color2)
{
    int r1,g1,b1,r2,g2,b2;
    color1.getRgb(&r1,&g1,&b1);
    color2.getRgb(&r2,&g2,&b2);
    return QColor((r1+r2)/2,(g1+g2)/2,(b1+b2)/2);
}


void DialogProcessMemory::Close()
{
    DeleteAllTimers();
}

void DialogProcessMemory::DeleteAllTimers()
{
    if (m_timerclearrythm) delete m_timerclearrythm;
    if ( m_timerrythm) delete m_timerrythm;
    if ( m_timerlyrics) delete m_timerlyrics;
    if ( m_timerend) delete m_timerend;
    m_timerclearrythm=0;
    m_timerrythm=0;
    m_timerlyrics=0;
    m_timerend=0;
}

void DialogProcessMemory::keyPressEvent(QKeyEvent *event)
{
    if ( ! m_jacksynchro)
    {
        if (event->key()==Qt::Key_Space )
        {
        PauseFlipFlop();
        }
    }
    QDialog::keyPressEvent(event);
}

void DialogProcessMemory::PauseFlipFlop()
{
    if (! m_pause)
    {
     if ( m_timerrythm ) m_timerrythm->stop();
     if ( m_timerlyrics) m_timerlyrics->stop();
    }
   else
   {
     if ( m_timerrythm )m_timerrythm->start();
     if ( m_timerlyrics)m_timerlyrics->start();
   }
   m_pause=!m_pause;
}
