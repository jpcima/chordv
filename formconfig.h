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
    void Init();
    void Save(QString filename,QString section);
protected:
    void disableWidgets(QRegExp value);
private:
    Ui::FormConfig *ui;
    QWidget *m_parent;
signals:
    void sendLog (QString message);

private slots:
    void setCover(int);
    void displayFont(QFont font, QColor text, QColor background);
    void SizeChanged(QString value);
    void displayThumb(QString image);
};

#endif // FORMCONFIG_H
