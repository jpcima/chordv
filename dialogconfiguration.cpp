#include "dialogconfiguration.h"
#include "ui_dialogconfiguration.h"
#include "spinboxunit.h"
#include "settings.h"
#include <QDebug>
#include <QLineEdit>
#include <QTranslator>

DialogConfiguration::DialogConfiguration(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogConfiguration)
{
    ui->setupUi(this);
    m_parent=parent;
    connect(ui->pushButtonClose,SIGNAL(clicked(bool)),this,SLOT(close()));
    connect(ui->pushButtonSave,SIGNAL(clicked(bool)),this,SLOT(Save()));
    Connect();
    InitSettings();
}


void DialogConfiguration::Connect()
{
    connect(ui->comboBoxInterfaceLanguage,SIGNAL(currentIndexChanged(int)),this,SLOT(SelectLanguage(int)));

}

DialogConfiguration::~DialogConfiguration()
{
    delete ui;
}

void DialogConfiguration::SelectLanguage(int i)
{
    Settings s;
    s.setValue("InterfaceLanguage",i);
    QTranslator tr;
    tr.load(":/Lang/chordV_fr_FR.qm");
    if ( i == 1 )
       {
          qApp->installTranslator(&tr);
       }
    else
       {
          qApp->removeTranslator(&tr);
       }
    Retranslate(i);
    emit LanguageChanged(i);
}


void DialogConfiguration::Retranslate(int i)
{
    qDebug()<<"ici"<<i;
    ui->comboBoxInterfaceLanguage->disconnect();
    ui->retranslateUi(this);
    ui->comboBoxInterfaceLanguage->setCurrentIndex(i);
    connect(ui->comboBoxInterfaceLanguage,SIGNAL(currentIndexChanged(int)),this,SLOT(SelectLanguage(int)));

}

void DialogConfiguration::InitSettings()
{
    Settings s;
    ui->comboBoxInterfaceLanguage->setCurrentIndex(s.value("InterfaceLanguage",0).toInt());
    ui->comboBoxUnit->setCurrentText(s.value("Unit","mm").toString());
    ui->lineEditCreatoName->setText(s.value("CreatorName","").toString());
}

void DialogConfiguration::Save()
{
   QSettings s;
   s.setValue("InterfaceLanguage",ui->comboBoxInterfaceLanguage->currentIndex());
   s.setValue("Unit",ui->comboBoxUnit->currentText());
   s.setValue("CreatorName",ui->lineEditCreatoName->text());
   ui->memoryConfig->Save(s.fileName(),FormConfig::Memory);
   ui->chordConfig->Save(s.fileName(),FormConfig::Chord);
   ui->textConfig->Save(s.fileName(),FormConfig::Text);
   ui->lyricsConfig->Save(s.fileName(),FormConfig::Lyrics);
   close();
}
