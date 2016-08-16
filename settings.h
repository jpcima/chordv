#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>
#include <QVariant>

class Settings : public QSettings
{
public:
    Settings();
    QVariant value(QString key, QVariant defaut);
};

#endif // SETTINGS_H
