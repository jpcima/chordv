#include "dialogabout.h"
#include "ui_dialogabout.h"
#include "version.h"
DialogAbout::DialogAbout(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAbout)
{
    ui->setupUi(this);
    ui->lineEditVersion->setText(QString(VERSION));
    ui->textBrowserCredit->setOpenLinks(false);
}

DialogAbout::~DialogAbout()
{
    delete ui;
}
