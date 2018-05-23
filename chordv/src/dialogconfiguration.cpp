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
    ui->checkBoxFullScreenMemory->setChecked(s.value("FullScreenBoxMemory",false).toBool());
    ui->checkBoxScrollingTextMemory->setChecked(s.value("ScrollingTextMemory",false).toBool());
    ui->comboBoxPositionMemory->setCurrentIndex(s.value("PositionMemory",0).toInt());
//    ui->toolButtonFontMemory->set->setColor(s.value);
}

void DialogConfiguration::Save()
{
   QSettings s;
   s.setValue("InterfaceLanguage",ui->comboBoxInterfaceLanguage->currentText());
   s.setValue("Unit",ui->comboBoxUnit->currentText());
   s.setValue("CreatorName",ui->lineEditCreatoName->text());
   s.setValue("PDFReader",ui->lineEditPDFReaderName->text());
   s.setValue("OpenLastFileOnStart",ui->checkBoxOpenLastFileOnStart->isChecked());
   s.setValue("FullScreenBoxMemory", ui->checkBoxFullScreenMemory->isChecked());
   s.setValue("ScrollingTextMemory", ui->checkBoxScrollingTextMemory->isChecked());
   s.setValue("PositionMemory",ui->comboBoxPositionMemory->currentIndex());
   ui->chordConfig->Save(s.fileName(),FormConfig::Chord);
   ui->textConfig->Save(s.fileName(),FormConfig::Text);
   ui->lyricsConfig->Save(s.fileName(),FormConfig::Lyrics);

   close();
}
