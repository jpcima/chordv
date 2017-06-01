#ifndef COLORBUTTON_H
#define COLORBUTTON_H

#include <QToolButton>

class ColorButton : public QToolButton
{
    Q_OBJECT
public:
    ColorButton(QWidget *parent=0);
    QColor getColor(){ return m_color;}
     void setColor(QColor color);
private:
    QColor m_color;
private slots:
    void setColor(bool);
signals:
    void ColorChanged(QColor color);
};

#endif // COLORBUTTON_H
