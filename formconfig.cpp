#include "formconfig.h"
#include "ui_formconfig.h"

FormConfig::FormConfig(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormConfig)
{
    ui->setupUi(this);
}

FormConfig::~FormConfig()
{
    delete ui;
}
