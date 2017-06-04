#ifndef TEXTEDIT_H
#define TEXTEDIT_H

#include "mainwindow.h"
#include <QTextEdit>



class TextEdit : public QTextEdit
{
    Q_OBJECT
public:
    TextEdit(QWidget *parent);
    void SetUi(Ui::MainWindow *ui);
protected:
   void wheelEvent(QWheelEvent *e);
   void mouseDoubleClickEvent(QMouseEvent *e);

private slots:
   void ChordToInsert(QString chord);
   void ShowChordInclusionDial();
private:
   Ui::MainWindow *ui;
   QString ChordBeatUpDown(QString chord,bool up);
   void UpDownChord(QWheelEvent *e);
   bool ChordUnderCursor();
   void DeleteOldChordInsertNew(QString newchord);
};

#endif // TEXTEDIT_H
