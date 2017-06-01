#ifndef TEXTEDIT_H
#define TEXTEDIT_H

#include "mainwindow.h"
#include <QTextEdit>



class TextEdit : public QTextEdit
{
public:
    TextEdit(QWidget *parent);
    void SetUi(Ui::MainWindow *ui);
protected:
   void wheelEvent(QWheelEvent *e);

private:
    Ui::MainWindow *ui;
};

#endif // TEXTEDIT_H
