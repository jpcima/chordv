#include "neck.h"
#include <QDebug>


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
}



void Neck::resizeEvent(QResizeEvent *)
{
   DrawNeck();
   qDebug()<<width()<<height()<<m_scene->width()<<m_scene->width();
}

void Neck::DrawNeck()
{
    m_scene->clear();
    m_scene->addRect(0,0,width(),height(),m_woodpen,m_woodbrush);
    for ( int fret=0;  fret < 22; fret++) DrawFret(fret);
    DrawStrings();
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
    if ( fret == 3 || fret == 5 || fret == 7 || fret == 9 || fret == 15   || fret == 17|| fret == 19 )
    {
        m_scene->addEllipse((width()/22)*fret+ width()/44-7,height()/2-7,14,14,QPen(),QBrush(QColor(Qt::white)) );
    }
    else if ( fret == 12 )
    {
        m_scene->addEllipse((width()/22)*fret+ width()/44-7,height()/4-7,14,14,QPen(),QBrush(QColor(Qt::white)) );
        m_scene->addEllipse((width()/22)*fret+ width()/44-7,height()*3/4-7,14,14,QPen(),QBrush(QColor(Qt::white)) );
    }
}
