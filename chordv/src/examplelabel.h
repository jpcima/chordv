#ifndef EXAMPLELABEL_H
#define EXAMPLELABEL_H

#include <QLabel>


class ExampleLabel : public QLabel
{
public:
    ExampleLabel(QWidget *parent=0,Qt::WindowFlags f=0);
    void setColor( QFont font, QColor color, QColor background);

signals:

public slots:
};

#endif // EXAMPLELABEL_H
