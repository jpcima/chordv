#ifndef CHORD_H
#define CHORD_H

#include "langnotes.h"
#include <QString>
#include <QRegExp>
#include <QStringList>

class Chord : public QString
{
public:
    Chord(QString chord,QString lang);
    QString chord();
    QString removeRytm();
    QString nbBar();
    QString nbBeat();
    QStringList toStrings();
    QString fret();
    QString ToEnglish(QString lang,QString chord);
    QString nameEnglish();
    QString nameLocale();
    QString pureNameLocale();
    QString pureNameEnglish();
    static QStringList removeDupplicateWhithoutRytm(QStringList chords,QString lang);
private:
    QString m_originalchord;
    QString m_nbbar; // 2 : from D7x2
    QString m_nbbeat; // 2 : from D7:2
    QString m_purechordLocale; // Ré7(III)
    QString m_purechordEnglish; // D7(III)

    QStringList m_chordonstrings; //  x x 0 2 1 2
    QString m_fret; // 0 1 ...
    QString m_nameLocale; // Ré7
    QString m_nameEnglish; //D7
    LangNotes m_notes;
    QString m_lang;
};

#endif // CHORD_H
