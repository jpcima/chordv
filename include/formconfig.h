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
    enum ChordInclusion {DiagramInText,ChordAtBeginingAndChordNameInText,NoChordAtBeginingAndChordNameInText};
    explicit FormConfig(QWidget *parent = 0);
    ~FormConfig();
    void setValue(QString var, QVariant value);
    void Save(QString filename,Classes section);
    void InitDefault(Classes classe);
    virtual Ui::FormConfig *getUi() { return ui;}
    void SetConfigFromFile(QString FileName);
    void SetConfigFromInit();
    QString classe2String(Classes name);
    void Retranslate();
    void disableGroup(QString group);
    void setProjectPath(QString path);
protected:
    void disableWidgets(QRegExp value);
    void InitComboBoxChordInclusion(QStringList list);
private:
    Ui::FormConfig *ui;
    QWidget *m_parent;
    QString m_configFileName;
    QString m_projectpath;
    void Calculate();
signals:
    void sendLog (QString message);

private slots:
    void setCover(int);
    void displayFont(QFont font, QColor text, QColor background);
    void displayThumb(QString image);
    void SizeChanged(QString size);
    void SizeChanged(bool);
    void FindSize(double);
    void deleteCoverImage(bool);
};

#endif // FORMCONFIG_H
