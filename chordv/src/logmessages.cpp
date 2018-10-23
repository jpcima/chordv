#include "logmessages.h"

#include <QDebug>
#include <QFontMetrics>

LogMessages::LogMessages(QWidget *parent):QTextEdit(parent)
{
 QFont f;
 QFontMetrics fm(f);
 this->setMinimumHeight(fm.height()*1.2);
}


QString LogMessages::ColorizeUntilColon( QString color, QString message)
{
    QRegExp exp("([^:]+:)(.*)");
    message.replace(exp,QString("<font color=\"%1\">%2</font>%3").arg(color).arg("\\1").arg("\\2"));
    return message;
}

void LogMessages::Error(QString message)
{
    append(ColorizeUntilColon("red",message));
}


void LogMessages::Info(QString message)
{
    this->append(ColorizeUntilColon("green",message));
}
