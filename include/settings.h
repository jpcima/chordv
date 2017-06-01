#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>
#include <QVariant>

class Settings : public QSettings
{
public:
    Settings();
    Settings(QString filename);
    QVariant value(QString key, QVariant defaut);
};

#endif // SETTINGS_H
