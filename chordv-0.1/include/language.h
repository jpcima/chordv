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
    static QStringList ListChord(QString lang);
    static QStringList ListMinor(QString lang);
    static QString getCodeLang(QString language);
    static QString TranslateLineWithchord(QString line, QString fromlang, QString frommin, QString tolang, QString tomin);
};

#endif // LANGUAGE_H
