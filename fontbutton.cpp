#include "fontbutton.h"
#include "fontchooser.h"
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
}
