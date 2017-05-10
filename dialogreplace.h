#ifndef DIALOGREPLACE_H
#define DIALOGREPLACE_H

#include <QDialog>

namespace Ui {
class DialogReplace;
}

class DialogReplace : public QDialog
{
    Q_OBJECT

public:
    explicit DialogReplace(QWidget *parent = 0);
    ~DialogReplace();

private:
    Ui::DialogReplace *ui;
signals:
    void SearchBack(QString text,bool casesensitive, bool wordonly);
    void Search(QString text,bool casesensitive, bool wordonly);
    void Replace(QString textfrom, QString textto, bool All, bool casesentisite, bool wordonly,bool back);

private slots:
    void Search();
    void Replace();
};

#endif // DIALOGREPLACE_H
