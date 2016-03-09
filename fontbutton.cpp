#include "fontbutton.h"
#include "fontchooser.h"

#include <QDebug>

FontButton::FontButton(QWidget *parent):QToolButton(parent)
{
   connect (this,SIGNAL(clicked(bool)),this,SLOT(setFont(bool)));
}

void FontButton::setFont(bool)
{
    FontChooser fc(this);
    fc.setFont(m_font,m_textcolor,m_backgroundcolor);
    connect (&fc,SIGNAL(SelectFont(QFont,QColor,QColor)),this,SLOT(SelectedFont(QFont,QColor,QColor)));
    fc.exec();
}

void FontButton::SelectedFont(QFont font, QColor text, QColor background)
{
    m_font=font;
    m_textcolor=text;
    m_backgroundcolor=background;
    if (! m_textcolor.isValid()) m_textcolor=QColor("black");
    if (! m_backgroundcolor.isValid()) m_backgroundcolor=QColor("white");
    emit sendSelectedFont(m_font,m_textcolor,m_backgroundcolor);
}
