#ifndef LANGUAGE_H
#define LANGUAGE_H

#include <QString>
#include <QComboBox>
class Language
{
public:

    static QString getTranslationQmFileName(QString language);
    static void setLanguageComboBox(QComboBox *ptr);
    static QString getTranslationDocFileName(QString language);
    static QStringList ListChord(QComboBox *ptr);
    static QStringList ListMinor(QComboBox *ptr);
};

#endif // LANGUAGE_H
