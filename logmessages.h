#ifndef LOGMESSAGES_H
#define LOGMESSAGES_H

#include <QTextEdit>

class LogMessages : public QTextEdit
{
public:
    LogMessages(QWidget *parent);
    void Error ( QString message );
};

#endif // LOGMESSAGES_H