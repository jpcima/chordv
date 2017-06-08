#ifndef DIALOGCHANGECHORDNAME_H
#define DIALOGCHANGECHORDNAME_H

#include <QDialog>

namespace Ui {
class DialogChangeChordName;
}

class DialogChangeChordName : public QDialog
{
    Q_OBJECT

public:
    explicit DialogChangeChordName(QWidget *parent = 0);
    ~DialogChangeChordName();
    QString getFromLang();
    QString getToLang();
    QString getFromMin();
    QString getToMin();
    bool OkDialog();
private slots:
    void Convert();
private:
    bool m_convert;
    Ui::DialogChangeChordName *ui;
};

#endif // DIALOGCHANGECHORDNAME_H
