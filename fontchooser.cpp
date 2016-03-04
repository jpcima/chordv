#include "fontchooser.h"
#include "ui_fontchooser.h"

FontChooser::FontChooser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FontChooser)
{
    ui->setupUi(this);
}

FontChooser::~FontChooser()
{
    delete ui;
}
