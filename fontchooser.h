#ifndef FONTCHOOSER_H
#define FONTCHOOSER_H

#include <QDialog>

namespace Ui {
class FontChooser;
}

class FontChooser : public QDialog
{
    Q_OBJECT

public:
    explicit FontChooser(QWidget *parent = 0);
    ~FontChooser();

private:
    Ui::FontChooser *ui;
};

#endif // FONTCHOOSER_H
