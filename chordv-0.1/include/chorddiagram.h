#ifndef CHORDDIAGRAM_H
#define CHORDDIAGRAM_H

#include <QWidget>

///
/// \brief The ChordDiagram class is a widget class usable in designer
///  to show chords in Qtt Designer
///
///
class ChordDiagram : public QWidget
{
    Q_OBJECT
public:
    ///
    /// \brief ChordDiagram the constructor with QWidget *parent who give the parent widget compliant
    /// to Graphic Designer of QtCreator
    /// \param parent : pointer on the parent
    ///
    explicit ChordDiagram(QWidget *parent = 0);
    ///
    /// \brief setDiagram when Widget is positionned give the name of the chord.
    /// \param diagram is given in 52x122x form
    ///
    void setDiagram(QString diagram);
    ///
    /// \brief getDiagram return the diagram name in 52x122x form
    /// \return
    ///
    QString getDiagram();
private:
    void paintEvent(QPaintEvent *p);
    QString m_diagram;
};

#endif // CHORDDIAGRAM_H
