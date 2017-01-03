#ifndef NECK_H
#define NECK_H

#include <QGraphicsView>

class Neck : public QGraphicsView
{
public:
    Neck(QWidget *parent);
private:
    QGraphicsScene *m_scene;
    void DrawNeck();
    void DrawFret(int fret);
    void resizeEvent(QResizeEvent *event);
    QBrush m_woodbrush;
    QBrush m_fretbrush;
    QPen m_fretpen;
    QPen m_woodpen;
    QPen m_stringpen;
    void DrawStrings();
    void SizeString(int string);
    void DrawCircle(int fret);
};

#endif // NECK_H
