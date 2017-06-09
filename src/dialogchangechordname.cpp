#include "dialogchangechordname.h"
#include "ui_dialogchangechordname.h"

DialogChangeChordName::DialogChangeChordName(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogChangeChordName)
{
    ui->setupUi(this);
    m_convert=false;
    connect(ui->pushButtonCancel,SIGNAL(clicked(bool)),this,SLOT(close()));
    connect(ui->pushButtonConvert,SIGNAL(clicked(bool)),this,SLOT(Convert()));
}

DialogChangeChordName::~DialogChangeChordName()
{
    delete ui;
}

QString DialogChangeChordName::getToLang()
{
    return ui->widget->getOutputLang();
}

QString DialogChangeChordName::getFromMin()
{
    return ui->widget->getInputMinor();
}

QString DialogChangeChordName::getToMin()
{
    return ui->widget->getOutputMinor();
}

QString DialogChangeChordName::getFromLang()
{
    return ui->widget->getInputLang();
}

void DialogChangeChordName::Convert()
{
    m_convert=true;
    close();
}

bool DialogChangeChordName::OkDialog()
{
    return true;
}
