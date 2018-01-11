#ifndef DIALOGTRANSPOSE_H
#define DIALOGTRANSPOSE_H

#include <QDialog>

namespace Ui {
class DialogTranspose;
}

class DialogTranspose : public QDialog
{
    Q_OBJECT

public:
    explicit DialogTranspose(QWidget *parent = 0);
    ~DialogTranspose();

private slots:
    void ChangeValue(int i);
    void Apply();
private:
    Ui::DialogTranspose *ui;
signals:
    void AskChange(int val, bool parenthesis, int Range);
};

#endif // DIALOGTRANSPOSE_H
