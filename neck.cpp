#include "neck.h"
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
    for ( int string=0; string <=5; string ++) m_strings[string]=-1;
    m_notes<<"C"<<"C#"<<"Db"<<"D"<<"D#"<<"Eb"<<"E"<<"F"<<"F#"<<"Gb"<<"G"<<"G#"<<"Ab"<<"A"<<"A#"<<"Bb"<<"B";
    int i=0;
    foreach ( QString note, m_notes) m_notevalues[note]=i++;
}

void Neck::mousePressEvent(QMouseEvent *event)
{
    if ( event->button()==Qt::LeftButton )
    {
        QPointF point=this->mapToScene(event->pos());
        int string=(int)(point.y()*6/height()+1);
        int fret=(int)(point.x()*23/width()+1);
        if ( m_strings[string-1] == 0 ) m_strings[string-1]=-1;
        else m_strings[string-1]=fret;
        DrawNeck();
    }
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
   // getNotes();
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
    int sizepoint=17;
    int sizesmallpoint=13;
    int center=(height())/12;
    for ( int string =0; string <6; string ++)
    {
        if ( m_strings[string]== -1 )
        {
            DrawNoNote(-10,height()/6*string+center)  ;
        }
        if ( m_strings[string] == 0 )
            m_scene->addEllipse(-13,height()/6*string+center-sizesmallpoint/2,sizesmallpoint,sizesmallpoint,QPen(),QBrush(QColor(Qt::green)) );
        else
           m_scene->addEllipse((width()/22)*m_strings[string]-sizepoint,height()/6*string+center-sizepoint/2,sizepoint,sizepoint,QPen(),QBrush(QColor(Qt::green)) );
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
    //switch ( string  )
    //case 1 :


}

QString Neck::getNotes()
{
   QString ret;
   for ( int i=0; i<6; i++)
       ret+=String2Note( i, m_strings[i]);
   return ret;

}

QString Neck::NotesToChord()
{

}
