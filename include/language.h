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
    static QStringList ListChord(QString lang, QString codelang);
    static QStringList ListMinor(QString lang, QString codelang);
};

#endif // LANGUAGE_H
