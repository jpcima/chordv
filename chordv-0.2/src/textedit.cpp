#include "textedit.h"

#include "ui_mainwindow.h"
#include "chord.h"
#include "dialogchorddefinition.h"


#include <QDebug>
#include <QShortcut>
#include <QKeySequence>


TextEdit::TextEdit(QWidget *parent ): QTextEdit(parent)
{
    new QShortcut(QKeySequence(Qt::Key_F4),this,SLOT(ShowChordInclusionDial()));
    m_editorhightlighter = new EditorHighlighter(document());
}

void TextEdit::insertPlainText(const QString &text, bool carriagereturn)
{
    textCursor().insertText(text);
    if (  carriagereturn )    textCursor().insertBlock();
}

void TextEdit::setChordLanguage(QString language, QString minor)
{
    m_chordlang=language;
    m_chordminor=minor;
}

void TextEdit::wheelEvent(QWheelEvent *e)
{
    if(e->modifiers().testFlag(Qt::ControlModifier))
     {
      if (e->angleDelta().y()>0 ) this->zoomOut();
      else this->zoomIn();
     }
    if ( e->modifiers().testFlag(Qt::ShiftModifier))
     {
        UpDownChord(e);
     }
    else QTextEdit::wheelEvent(e);
}


bool TextEdit::ChordUnderCursor()
{
    QString chord;
    QTextCursor tc=textCursor();
    int column=tc.columnNumber();
    tc.select(QTextCursor::LineUnderCursor);
    QString string =tc.selectedText();
    int i= column ;
    while (--i>0)
    {
        if ( string.at(i)=='[' || string.at(i)==']') break;
    }
    int j=column;
    while ( j < string.length() )
    {
       if ( string.at(j)==']' || string.at(j)=='[')  break;
       j++;
    }
    if (  i >=0 && j < string.length() && string.at(i) == '[' && string.at(j) == ']')
       chord=string.mid(i,j-i+1);
    return !chord.isEmpty();
}

void TextEdit::DeleteOldChordInsertNew(QString newchord)
{
    QString chord;
    QTextCursor tc=textCursor();
    QTextCursor tc1=tc;
    int column=tc.columnNumber();
    tc.select(QTextCursor::LineUnderCursor);
    QString string =tc.selectedText();
    int i= column ;
    while (--i>0)
    {
        if ( string.at(i)=='[' || string.at(i)==']') break;
    }
    int j=column;
    while ( j < string.length() )
    {
       if ( string.at(j)==']' || string.at(j)=='[')  break;
       j++;
    }
    if (  i >=0 && j < string.length() && string.at(i) == '[' && string.at(j) == ']')
       chord=string.mid(i,j-i+1);
    if ( !chord.isEmpty() )
    {
        tc.clearSelection();
        tc=tc1;
        int cr=j-tc.columnNumber();
        int cl=tc.columnNumber()-i;
        for ( int m= 0;m<=cr;m++)tc.deleteChar();
        for ( int m= 0;m<cl;m++)tc.deletePreviousChar();
        tc.insertText(newchord);
        tc.movePosition(QTextCursor::WordLeft,QTextCursor::MoveAnchor,2);
        setTextCursor(tc);
    }

}

void TextEdit::UpDownChord(QWheelEvent *e)
{
    QString chord;
    QTextCursor tc=textCursor();
    QTextCursor tc1=tc;
    int column=tc.columnNumber();
    tc.select(QTextCursor::LineUnderCursor);
    QString string =tc.selectedText();
    int i= column ;
    while (--i>0)
    {
        if ( string.at(i)=='[' || string.at(i)==']') break;
    }
    int j=column;
    while ( j < string.length() )
    {
       if ( string.at(j)==']' || string.at(j)=='[')  break;
       j++;
    }
    if (  i >=0 && j < string.length() && string.at(i) == '[' && string.at(j) == ']')
       chord=string.mid(i,j-i+1);
    if ( !chord.isEmpty() )
    {
        chord=ChordBeatUpDown(chord,e->angleDelta().y()>0);
        tc.clearSelection();
        tc=tc1;
        int cr=j-tc.columnNumber();
        int cl=tc.columnNumber()-i;
        for ( int m= 0;m<=cr;m++)tc.deleteChar();
        for ( int m= 0;m<cl;m++)tc.deletePreviousChar();
        tc.insertText(chord);
        tc.movePosition(QTextCursor::WordLeft,QTextCursor::MoveAnchor,2);
        setTextCursor(tc);
    }
}

void TextEdit::mouseDoubleClickEvent(QMouseEvent *)
{
  ShowChordInclusionDial();
}


void TextEdit::ShowChordInclusionDial()
{
    DialogChordDefinition *dial= new DialogChordDefinition(this);
    dial->ActiveInsertButton();
    dial->SetChordLanguage(m_chordlang,m_chordminor);
    connect (dial,SIGNAL(ChordToInsert(QString)),this, SLOT(ChordToInsert(QString)));
    dial->exec();
}

void TextEdit::TransPoseChord(int degre, bool par, int range)
{
  Q_UNUSED(degre)
    qWarning()<<"transpose";
  Q_UNUSED(par)
  Q_UNUSED(range)
}

void TextEdit::ChordToInsert(QString chord)
{
    QTextCursor tc=textCursor();
    if ( ! ChordUnderCursor() )
        tc.insertText(chord);
    else
        DeleteOldChordInsertNew(chord);

}

QString TextEdit::ChordBeatUpDown(QString chord, bool up)
{
    chord.replace("[","");
    chord.replace("]","");
    Chord ch(chord,"fr");
    if ( up )
        return QString("[%1]").arg(ch.up());
    else
        return QString("[%1]").arg(ch.down());
}
