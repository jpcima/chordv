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

private:
    Ui::DialogTranspose *ui;
};

#endif // DIALOGTRANSPOSE_H
