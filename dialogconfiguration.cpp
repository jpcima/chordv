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
}

void DialogConfiguration::Save()
{
   QSettings s;
   s.setValue("InterfaceLanguage",ui->comboBoxInterfaceLanguage->currentText());
   s.setValue("Unit",ui->comboBoxUnit->currentText());
   s.setValue("CreatorName",ui->lineEditCreatoName->text());
   ui->memoryConfig->Save(s.fileName(),FormConfig::Memory);
   ui->chordConfig->Save(s.fileName(),FormConfig::Chord);
   ui->textConfig->Save(s.fileName(),FormConfig::Text);
   ui->lyricsConfig->Save(s.fileName(),FormConfig::Lyrics);
   close();
}
