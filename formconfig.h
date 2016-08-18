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
    enum Classes { Chord,Lyrics,Memory,Text};
    explicit FormConfig(QWidget *parent = 0);
    ~FormConfig();
    void setValue(QString var, QVariant value);
    void Save(QString filename,QString section);
    void InitDefault(Classes classe);
protected:
    void disableWidgets(QRegExp value);
private:
    Ui::FormConfig *ui;
    QWidget *m_parent;
    QString classe2String(Classes name);
    void Calculate();
signals:
    void sendLog (QString message);

private slots:
    void setCover(int);
    void displayFont(QFont font, QColor text, QColor background);
    void displayThumb(QString image);
    void SizeChanged(QString size);
    void SizeChanged(bool);
};

#endif // FORMCONFIG_H
