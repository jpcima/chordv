#ifndef LANGUAGE_H
#define LANGUAGE_H

#include <QString>
#include <QComboBox>
class Language
{
public:

    static QString getTranslationQmFileName(QString language);
    static void setLanguageComboBox(QComboBox *ptr);
};

#endif // LANGUAGE_H
