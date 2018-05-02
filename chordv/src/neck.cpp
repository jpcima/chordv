#include "neck.h"
#include "ChordDetector.h"
#include <QDebug>
#include <QMouseEvent>


Neck::Neck(QWidget *parent) : QGraphicsView(parent)
{
    m_scene = new QGraphicsScene(this);
    this->setScene(m_scene);
    m_fretpen.setCapStyle(Qt::RoundCap);
    m_fretpen.setColor(Qt::gray);
    m_fretpen.setWidth(5);

    m_fretpen.setStyle(Qt::SolidLine);
    m_woodbrush.setTexture(QPixmap(":/Image/Images/neck.jpg"));
    m_woodpen=QPen();
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff );
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff );
    setFrameStyle(0);
    for ( int string=0; string <=5; string ++) m_chord[string]=-1;
    m_necknotes<<"C"<<"Db"<<"D"<<"Eb"<<"E"<<"F"<<"F#"<<"G"<<"Ab"<<"A"<<"Bb"<<"B";
    m_notes<<"C"<<"C#"<<"Db"<<"D"<<"D#"<<"Eb"<<"E"<<"F"<<"F#"<<"Gb"<<"G"<<"G#"<<"Ab"<<"A"<<"A#"<<"Bb"<<"B";
    int i=0;
    foreach ( QString note, m_notes) m_notevalues[note]=m_values[i++];
}

void Neck::mousePressEvent(QMouseEvent *event)
{
    if ( event->button()==Qt::LeftButton )
    {
        QPointF point=this->mapToScene(event->pos());
        int string=(int)(point.y()*6/height()+1);
        int fret=(int)(point.x()*22/width()+1);
        if ( m_chord[string-1] == 0 ) m_chord[string-1]=-1;
        else m_chord[string-1]=fret;
        DrawNeck();
    }
    else if ( event->button() == Qt::RightButton)
    {
         QPointF point=this->mapToScene(event->pos());
         int fret=(int)(point.x()*23/width()+1);
         for ( int string = 0 ; string <=5  ; string ++)
             m_chord[string]=fret;
          DrawNeck();
    }
}

void Neck::wheelEvent(QWheelEvent *event)
{
    if ( event->delta() > 0 )
        for ( int string = 0 ; string <=5  ; string ++)
           { if ( m_chord[string] <22 )m_chord[string]= m_chord[string]+1;}
    else
        for ( int string = 0 ; string <=5  ; string ++)
           {if ( m_chord[string] >1) m_chord[string]= m_chord[string]-1; }
    DrawNeck();

}

void Neck::resizeEvent(QResizeEvent *)
{
   DrawNeck();
}

void Neck::DrawNeck()
{
    m_scene->clear();
    m_scene->addRect(0,0,width(),height(),m_woodpen,m_woodbrush);
    for ( int fret=0;  fret < 22; fret++) DrawFret(fret);
    DrawStrings();
    DrawNotes();
    emit ChordsDetected( NotesToChord(getNotes()),toString());
}

QString Neck::toString()
{
    QString ret;
    for ( int i=5; i>=0; i--)
    {
        if ( m_chord[i]== -1) ret+="x-";
        else ret+=QString("%1-").arg(m_chord[i]);
    }
    ret.replace(QRegExp("-$"),"");
    return ret;
}

void Neck::DrawFret ( int fret  )
{
    int x=(width()/22)*(fret);
    DrawCircle(fret);
    m_scene->addLine(x,3,x,height()-3,m_fretpen);
}

void Neck::DrawStrings()
{
    int stringstep=(height())/6 ;
    int center=stringstep/2 ;
    for ( int string=1; string<=6; string++)
    {
        SizeString(string);
        m_scene->addLine(0,stringstep*string-center,width(),stringstep*string-center ,m_stringpen );
    }
}

void Neck::SizeString( int string)
{
    if ( string <= 3 )
    {
      m_stringpen.setWidth(1);
      m_stringpen.setColor(QColor(250,250,250));
    }
    else if ( string <=5 )
    {
        m_stringpen.setWidth(2);
        m_stringpen.setColor(QColor(110,110,110));
    }
    else
    {
        m_stringpen.setWidth(3);
        m_stringpen.setColor(QColor(110,110,110));
    }
}


void Neck::DrawCircle(int fret)
{
    if ( fret == 3 ||  fret == 5 || fret == 7 || fret == 9 || fret == 15   || fret == 17|| fret == 19 )
    {
        m_scene->addEllipse((width()/22)*fret- width()/44-7,height()/2-7,14,14,QPen(),QBrush(QColor(Qt::white)) );
    }
    else if ( fret == 12 )
    {
        m_scene->addEllipse((width()/22)*fret- width()/44-7,height()/4-7,14,14,QPen(),QBrush(QColor(Qt::white)) );
        m_scene->addEllipse((width()/22)*fret- width()/44-7,height()*3/4-7,14,14,QPen(),QBrush(QColor(Qt::white)) );
    }
}


void Neck::DrawNotes()
{
    int sizepoint=height()/7;
    int sizesmallpoint=height()/10;
    int center=(height())/12;
    for ( int string =0; string <6; string ++)
    {
        if ( m_chord[string]== -1 )
        {
            DrawNoNote(-10,height()/6*string+center)  ;
        }
        else
        if ( m_chord[string] == 0 )
        {
        m_scene->addEllipse(-13,height()/6*string+center-sizesmallpoint/2,sizesmallpoint,sizesmallpoint,QPen(),QBrush(QColor(Qt::green)) );
        }
        else
        {
        m_scene->addEllipse((width()/22)*m_chord[string]-sizepoint,height()/6*string+center-sizepoint/2,sizepoint,sizepoint,QPen(),QBrush(QColor(Qt::green)) );
        }
    }
}


void Neck::DrawNoNote( int x, int y)
{
    int size=3;
     m_scene->addLine(x-size,y-size, x+size,y+size ,QPen(QColor(Qt::red))) ;
     m_scene->addLine(x-size,y+size, x+size,y-size ,QPen(QColor(Qt::red))) ;
}

QString Neck::String2Note ( int string, int fret )
{
    if (fret == -1 ) return 0;
    int note=m_strings[string];
    note=(fret+note)%12;
    return m_necknotes.at(note);
}

QStringList Neck::getNotes()
{
   QStringList ret;
   for ( int i=5; i>=0; i--)
    {
       QString note=String2Note( i, m_chord[i]);
       if (!note.isNull())ret<<note;
   }
   return ret;
}


QStringList Neck::NotesToChord( QStringList notes )
{
  ChordDetector d(notes);
  return d.detectChord();
}



QStringList Neck::EraseEmptyNote(QStringList notes)
{
    QStringList ret;
    foreach ( QString note, notes)
        if ( ! note.isEmpty()) ret<<note;
    return ret;
}

QString Neck::chordInterval( int i)
{
  if ( i == 0 ) return "";
  return QString("%1").arg(i)  ;
}
