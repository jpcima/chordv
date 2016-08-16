#include "dialogconfiguration.h"
#include "ui_dialogconfiguration.h"

DialogConfiguration::DialogConfiguration(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogConfiguration)
{
    ui->setupUi(this);
}

DialogConfiguration::~DialogConfiguration()
{
    delete ui;
}
