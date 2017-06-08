#ifndef FORMINPUTOUTPUTCHORD_H
#define FORMINPUTOUTPUTCHORD_H

#include <QWidget>
#include <QComboBox>
#include <QLabel>

namespace Ui {
class FormInputOutputChord;
}

class FormInputOutputChord : public QWidget
{
    Q_OBJECT

public:
    explicit FormInputOutputChord(QWidget *parent = 0);
    QString getInputLang();
    QString getInputCodeLang();
    QString getOutputLang();
    QString getInputMinor();
    QString getOutputMinor();
    QString getOutputCodeLang();
    void setOutputMinor(int index);
    void setInputMinor(int index);
    void setInputLang(int index);
    void setOutputLang(int index);
    ~FormInputOutputChord();

private slots:
    void LanguageOutputChanged(QString);
    void LanguageInputChanged(QString);
private:
    Ui::FormInputOutputChord *ui;
    void SetInvisibleIfOnlyOnceChoice(QComboBox *ptr, QLabel *ptrl);
};

#endif // FORMINPUTOUTPUTCHORD_H
