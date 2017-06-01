#include "textedit.h"
#include "ui_mainwindow.h"
#include <QDebug>

TextEdit::TextEdit(QWidget *parent ): QTextEdit(parent)
{

}

void TextEdit::SetUi(Ui::MainWindow *ptr)
{
    ui=ptr;
}

void TextEdit::wheelEvent(QWheelEvent *e)
{
    if(e->modifiers().testFlag(Qt::ControlModifier))
     {
      if (e->angleDelta().y()>0 ) this->zoomOut();
      else this->zoomIn();
     }
    else QTextEdit::wheelEvent(e);
}

