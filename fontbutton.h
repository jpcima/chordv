#ifndef FONTBUTTON_H
#define FONTBUTTON_H

#include <QToolButton>


class FontButton : public QToolButton
{
    Q_OBJECT
public:
    FontButton(QWidget *parent);
    void setFamily( QString family) {m_font.setFamily(family);}
    void setColor ( QColor color) {m_textcolor=color;}
    void setBackgroundColor ( QColor color ) { m_backgroundcolor=color;}
    void setWeight(int i) { m_font.setWeight(i); }
    void setItalic(bool b) { m_font.setItalic(b) ;}
    void setPointsize ( int size) {m_font.setPointSize(size);}
    QFont getFont() { return m_font;}
    QColor getBackgroundColor () { return m_backgroundcolor;}
    QColor getTextColor () { return m_textcolor;}

private:
    QColor m_textcolor;
    QColor m_backgroundcolor;
    QFont m_font;
private slots:
    void setFont(bool );
    void SelectedFont(QFont font, QColor text, QColor background);
};

#endif // FONTBUTTON_H
