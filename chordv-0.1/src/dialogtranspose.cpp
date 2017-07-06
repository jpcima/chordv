#include "dialogtranspose.h"
#include "ui_dialogtranspose.h"

DialogTranspose::DialogTranspose(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogTranspose)
{
    ui->setupUi(this);
}

DialogTranspose::~DialogTranspose()
{
    delete ui;
}
