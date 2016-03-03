#ifndef FORMCONFIG_H
#define FORMCONFIG_H

#include <QWidget>

namespace Ui {
class FormConfig;
}

class FormConfig : public QWidget
{
    Q_OBJECT

public:
    explicit FormConfig(QWidget *parent = 0);
    ~FormConfig();

private:
    Ui::FormConfig *ui;
};

#endif // FORMCONFIG_H
