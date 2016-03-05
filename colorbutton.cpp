#include "colorbutton.h"
#include <QColorDialog>
ColorButton::ColorButton(QWidget *parent):QToolButton(parent)
{
    connect (this,SIGNAL(clicked(bool)),this,SLOT(setColor(bool)));
}

void ColorButton::setColor(bool)
{
   m_color=QColorDialog::getColor(m_color,this);
   emit ColorChanged(m_color);
}

