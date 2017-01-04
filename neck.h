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
    void mousePressEvent(QMouseEvent *event);
    void DrawNotes();
    void DrawNoNote(int x,int y);
    ///
    /// \brief String2Note convert a fret pressed on a string
    /// \param string : the string
    /// \param fret : the pressed fred
    /// \return  : the note in string format
    ///
    QString String2Note(int string, int fret);
    QString NotesToChord();
    QStringList getNotes();

    ///
    /// \brief m_chord fret values on each chord
    /// chord is 0 x 2 3 3 2 ( 1 chord is high )
    ///
    int m_chord[5];
    ///
    /// \brief m_notes list of 17 notes  :  C C# Db D D# Eb E F F# Gb G G# Ab A A# Bb B
    ///                                     0 1  1  2 3  3  4 5 6  6  7 8  8  9 10 10 11
    QStringList m_notes;
    ///
    /// \brief m_values list of values for each 17 notes : 0 1 1 2 3 3 4 5 6 6 7 8 8 9 10 10 11
    ///
    int m_values[17]= {0,1,1,2,3,3,4,5,6,6,7,8,9,10,10,11};
    QStringList m_necknotes;
    ///
    /// \brief m_notevalues m_notevalues["C#"] = 1 ...
    ///
    QHash <QString,int> m_notevalues;
    ///
    ////// \brief m_strings note of each strings on the guitar (from high to bass)
    ///
    int m_strings[6] ={4,11,7,2,9,4};
    QList <int>m_chordInterval ;
    QStringList m_chordNote;
    QList<int> CalcChorInterval(QStringList chord);
};

#endif // NECK_H
