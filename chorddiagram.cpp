#include "chorddiagram.h"
#include <QPainter>


ChordDiagram::ChordDiagram(QWidget *parent) : QWidget(parent)
{
    m_diagram=QString();
}

void ChordDiagram::setDiagram(QString diagram)
{
    m_diagram=diagram;
    repaint();
}

void ChordDiagram::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    int h=this->height();
    int w=this->width();
    int cs=20;
    int hm=20;
    int xmfret=-10;
    int ymfret=+7;
    int x=w/2-3*cs;
    int y=hm;
    int rcercle=10;
    for ( int i=0;i<=5;i++)
    {
        painter.drawLine(x+cs*i,y,x+cs*i,h-hm);
    }
    for (int i= 1 ; i<= 5 ; i++)
    {
        painter.drawLine(x,y*i,x+cs*5,y*i);
    }
    QPen pen;
    pen.setWidth(3);
    painter.setPen(pen);
    painter.drawLine(x+1,y,x+cs*5+1,y);
    if ( !m_diagram.isEmpty())
    {
        QStringList list=m_diagram.split(" ");
        painter.drawText(QPoint(x+xmfret,y+ymfret),list.at(0));
        for ( int i=0;i<6;i++)
        {
            QString note=list.at(i+1);
            if ( note!="x") painter.drawEllipse(x+cs*i,y*note.toInt(),rcercle,rcercle);
        }

    }
}

