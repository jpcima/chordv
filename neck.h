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
    int m_strings[5];
    void DrawStrings();
    void SizeString(int string);
    void DrawCircle(int fret);
    void mousePressEvent(QMouseEvent *event);
    void DrawNotes();
    void DrawNoNote(int x,int y);
    QString String2Note(int string, int fret);
    QString NotesToChord();
    QString getNotes();
    QStringList m_notes;
    QHash <QString,int> m_notevalues;
    QStringList m_value2note;
};

#endif // NECK_H
