#ifndef CHORD_H
#define CHORD_H


#include <QString>
#include <QRegExp>
#include <QStringList>

class Chord : public QString
{
public:
    Chord(QString chord);
    QString removeTempo();
    QString tempo();
    QStringList toStrings();
    QString fret();
    QString ToEnglish(QString chord);
    QString nameEnglish();
    QString nameLocale();
private:
    QString m_tempo; // 2 : from D7x2
    QString m_purechordLocale; // Ré7(III)
    QString m_purechordEnglish; // D7(III)

    QStringList m_chordonstrings; //  x x 0 2 1 2
    QString m_fret; // 0 1 ...
    QString m_nameLocale; // Ré7
    QString m_nameEnglish; //D7
};

#endif // CHORD_H
