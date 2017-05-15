#ifndef LANGNOTES_H
#define LANGNOTES_H

#include <QMap>

class LangNotes
{
public:
    LangNotes();
    QString note(QString lang,QString englishnote);
private:
    QMap  < QString ,QStringList > m_lang;
    QMap <QString,int> m_englishnote;
};

#endif // LANGNOTES_H
