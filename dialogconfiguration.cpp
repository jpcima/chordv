#include "dialogconfiguration.h"
#include "ui_dialogconfiguration.h"
#include "spinboxunit.h"
#include "settings.h"
#include <QDebug>
#include <QLineEdit>

DialogConfiguration::DialogConfiguration(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogConfiguration)
{
    ui->setupUi(this);
    m_parent=parent;
    connect(ui->pushButtonClose,SIGNAL(clicked(bool)),this,SLOT(close()));
    connect(ui->pushButtonSave,SIGNAL(clicked(bool)),this,SLOT(Save()));
    InitSettings();
}

DialogConfiguration::~DialogConfiguration()
{
    delete ui;
}

void DialogConfiguration::InitSettings()
{
    Settings s;
    ui->comboBoxInterfaceLanguage->setCurrentText(s.value("InterfaceLanguage","English").toString());
    ui->comboBoxUnit->setCurrentText(s.value("Unit","mm").toString());
    ui->lineEditCreatoName->setText(s.value("CreatorName","").toString());
    ui->chordChonfig->InitDefaut("Chord");
    ui->lyricsConfig->InitDefaut("Lyrics");
    ui->memoryConfig->InitDefaut("Memory");
    ui->textConfig->InitDefaut("Text");
}

void DialogConfiguration::Save()
{


}
