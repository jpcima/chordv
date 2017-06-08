#ifndef DIALOGTWOLINESTOCHORDPRO_H
#define DIALOGTWOLINESTOCHORDPRO_H

#include <QDialog>
#include <QMap>
#include <QComboBox>
#include <QLabel>

namespace Ui {
class DialogTwoLinesToChordPro;
}

class DialogTwoLinesToChordPro : public QDialog
{
    Q_OBJECT

public:
    explicit DialogTwoLinesToChordPro(QWidget *parent = 0);
    ~DialogTwoLinesToChordPro();

private slots:
    void Convert();
    void Demo();
    void LanguageOutputChanged(QString value);
    void LanguageInputChanged(QString value);
private:
    Ui::DialogTwoLinesToChordPro *ui;
    bool isChords(QString line);
    QMap <int,QString> m_chords;
    bool MapIsEmpty();
    QString mixLineAndMap(QString line);
    void ConvertToMap(QString line);
    void ClearMap();
    QString m_minorfrom;
    QString m_minorto;
    void SetInvisibleIfOnlyOnceChoice(QComboBox *ptr, QLabel *label);
    QString translate(QString chord);
};

#endif // DIALOGTWOLINESTOCHORDPRO_H
