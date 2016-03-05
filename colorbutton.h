#ifndef COLORBUTTON_H
#define COLORBUTTON_H

#include <QToolButton>

class ColorButton : public QToolButton
{
    Q_OBJECT
public:
    ColorButton(QWidget *parent=0);
    QColor getColor(){ return m_color;}
    void setColor(QColor color){ m_color=color;}
private:
    QColor m_color;
private slots:
    void setColor(bool);
};

#endif // COLORBUTTON_H
