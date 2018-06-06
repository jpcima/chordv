#include "dialogconfiguration.h"
#include "ui_dialogconfiguration.h"

#include "spinboxunit.h"
#include "settings.h"
#include "language.h"

#include <QDebug>
#include <QLineEdit>
#include <QTranslator>
#include <QFileDialog>
#include <QDir>
#include <QFileInfoList>

DialogConfiguration::DialogConfiguration(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogConfiguration)
{
    ui->setupUi(this);
    m_parent=parent;
    Language::setLanguageComboBox(ui->comboBoxInterfaceLanguage);
    connect(ui->pushButtonClose,SIGNAL(clicked(bool)),this,SLOT(close()));
    connect(ui->pushButtonSave,SIGNAL(clicked(bool)),this,SLOT(Save()));
    connect(ui->toolButtonPDFReaderName,SIGNAL(clicked(bool)),this,SLOT(SetPDFReader()));
    Connect();
    InitSettings();
    ui->tabWidget->setCurrentIndex(0);
    ui->widgetMemory->setOffSetAsDefault();
    ui->lyricsConfig->setOffButtonSetAsDefault();
    ui->textConfig->setOffButtonSetAsDefault();
    ui->chordConfig->setOffButtonSetAsDefault();
}

void DialogConfiguration::setTranslator(QTranslator *translator)
{
    m_translator=translator;
}




void DialogConfiguration::SetPDFReader()
{
    QString pdfreader=QFileDialog::getOpenFileName(this,tr("Choose PDF Reader program"),"/");
    ui->lineEditPDFReaderName->setText(pdfreader);
    emit PdfReaderChanged();
}

void DialogConfiguration::Connect()
{
    connect(ui->comboBoxInterfaceLanguage,SIGNAL(currentTextChanged(QString)),this,SLOT(SelectLanguage(QString)));

}

DialogConfiguration::~DialogConfiguration()
{
    delete ui;
}

void DialogConfiguration::SelectLanguage(QString  lang)
{
    Settings s;
    s.setValue("InterfaceLanguage",lang);
    QTranslator tr;
    QString filename=Language::getTranslationQmFileName(lang);
    tr.load(filename);
    if ( lang != "English" )
       {
          qApp->installTranslator(&tr);
          m_translator=&tr;
       }
    else
       {
          qApp->removeTranslator(m_translator);
          m_translator=0;
       }
    Retranslate(lang);
    emit LanguageChanged(lang);
}


void DialogConfiguration::Retranslate(QString)
{
    ui->comboBoxInterfaceLanguage->disconnect();
    ui->retranslateUi(this);
    ui->widgetMemory->Retranslate();
    ui->chordConfig->Retranslate();
    ui->lyricsConfig->Retranslate();
    ui->textConfig->Retranslate();
    //ui->comboBoxInterfaceLanguage->setCurrent;
    connect(ui->comboBoxInterfaceLanguage,SIGNAL(currentTextChanged(QString)),this,SLOT(SelectLanguage(QString)));

}

void DialogConfiguration::InitSettings()
{
    Settings s;
    ui->comboBoxInterfaceLanguage->setCurrentText(s.value("InterfaceLanguage",0).toString());
    ui->comboBoxUnit->setCurrentText(s.value("Unit","mm").toString());
    ui->lineEditCreatoName->setText(s.value("CreatorName","").toString());
    ui->lineEditPDFReaderName->setText(s.value("PDFReader","").toString());
    ui->checkBoxOpenLastFileOnStart->setChecked(s.value("OpenLastFileOnStart",false).toBool());
}

void DialogConfiguration::Save()
{
   QSettings s;
   s.setValue("InterfaceLanguage",ui->comboBoxInterfaceLanguage->currentText());
   s.setValue("Unit",ui->comboBoxUnit->currentText());
   s.setValue("CreatorName",ui->lineEditCreatoName->text());
   s.setValue("PDFReader",ui->lineEditPDFReaderName->text());
   s.setValue("OpenLastFileOnStart",ui->checkBoxOpenLastFileOnStart->isChecked());

   ui->chordConfig->Save(s.fileName(),"Chord");
   ui->textConfig->Save(s.fileName(),"Text");
   ui->lyricsConfig->Save(s.fileName(),"Lyrics");
   ui->widgetMemory->Save();

   close();
}
