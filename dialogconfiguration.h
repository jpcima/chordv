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

private:
    Ui::DialogConfiguration *ui;
};

#endif // DIALOGCONFIGURATION_H
