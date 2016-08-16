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
private:
    Ui::DialogConfiguration *ui;
    QWidget *m_parent;
};

#endif // DIALOGCONFIGURATION_H
