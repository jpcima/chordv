#ifndef CHORDDIAGRAM_H
#define CHORDDIAGRAM_H

#include <QWidget>

class ChordDiagram : public QWidget
{
    Q_OBJECT
public:
    explicit ChordDiagram(QWidget *parent = 0);
     void setDiagram(QString diagram);
private:
    void paintEvent(QPaintEvent *p);
    QString m_diagram;
};

#endif // CHORDDIAGRAM_H
