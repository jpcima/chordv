#ifndef DIALOGCONFIGURATION_H
#define DIALOGCONFIGURATION_H

#include <QDialog>

namespace Ui {
class DialogConfiguration;
}

class DialogConfiguration : public QDialog
{
    Q_OBJECT

public:
    explicit DialogConfiguration(QWidget *parent = 0);
    ~DialogConfiguration();
    void InitSettings();
private slots:
    void Save();
    void SelectLanguage(int i);
private:
    Ui::DialogConfiguration *ui;
    QWidget *m_parent;
    void Connect();
    void Retranslate(int i);
signals:
    void LanguageChanged(int i);
};

#endif // DIALOGCONFIGURATION_H
