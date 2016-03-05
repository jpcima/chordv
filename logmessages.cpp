#include "logmessages.h"



LogMessages::LogMessages(QWidget *parent):QTextEdit(parent)
{

}

void LogMessages::Error(QString message)
{
    QTextCharFormat myClassFormat;
    myClassFormat.setFontWeight(QFont::Bold);
    myClassFormat.setForeground(Qt::red);
    this->append(message);
}

