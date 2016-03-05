#ifndef FORMCONFIG_H
#define FORMCONFIG_H

#include <QWidget>
#include <QRegExp>

namespace Ui {
class FormConfig;
}

class FormConfig : public QWidget
{
    Q_OBJECT

public:
    explicit FormConfig(QWidget *parent = 0);
    ~FormConfig();
    void setValue(QString var, QVariant value);
protected:
    void disableWidgets(QRegExp value);
private:
    Ui::FormConfig *ui;
    QWidget *m_parent;
};

#endif // FORMCONFIG_H
