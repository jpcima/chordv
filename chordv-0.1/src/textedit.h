#ifndef TEXTEDIT_H
#define TEXTEDIT_H

#include "mainwindow.h"

#include "editorhighlighter.h"

#include <QTextEdit>



class TextEdit : public QTextEdit
{
    Q_OBJECT
public:
    TextEdit(QWidget *parent);
    void insertPlainText(const QString &text, bool carriagereturn = true);
    void setChordLanguage( QString language, QString minor);
protected:
   void wheelEvent(QWheelEvent *e);
   void mouseDoubleClickEvent(QMouseEvent *e);

private slots:
   void ChordToInsert(QString chord);
   void ShowChordInclusionDial();
   void TransPoseChord(int degre, bool par, int range);
private:
   //Ui::MainWindow *ui;
   QString ChordBeatUpDown(QString chord,bool up);
   void UpDownChord(QWheelEvent *e);
   bool ChordUnderCursor();
   void DeleteOldChordInsertNew(QString newchord);
   EditorHighlighter *m_editorhightlighter;
   QString m_chordlang;
   QString m_chordminor;
};

#endif // TEXTEDIT_H
