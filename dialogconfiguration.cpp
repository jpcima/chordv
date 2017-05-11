#include "dialogconfiguration.h"
#include "ui_dialogconfiguration.h"
#include "spinboxunit.h"
#include "settings.h"
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
    setLanguageComboBox(ui->comboBoxInterfaceLanguage);
    connect(ui->pushButtonClose,SIGNAL(clicked(bool)),this,SLOT(close()));
    connect(ui->pushButtonSave,SIGNAL(clicked(bool)),this,SLOT(Save()));
    connect(ui->toolButtonPDFReaderName,SIGNAL(clicked(bool)),this,SLOT(SetPDFReader()));
    Connect();
    InitSettings();
}


void DialogConfiguration::setLanguageComboBox(QComboBox *ptr)
{
    QSettings s;
    QFileInfo fi(s.fileName());
    QString Langpath=fi.absolutePath();
    QString path=Langpath+"/Languages";
    QFileInfoList filist=QDir(path).entryInfoList(QDir::AllDirs|QDir::NoDotAndDotDot);
    foreach (QFileInfo fi, filist)
    {
        QString dir=fi.absoluteFilePath();
        QString name=fi.fileName();
        QDir d(dir);
        QStringList filter;
        filter<<"*.qm";
        QFileInfoList list=d.entryInfoList(filter);
        if ( !list.isEmpty())
        {
            QString qmfile=list.at(0).absoluteFilePath();
            QString pngfile=qmfile.replace(QRegExp("\\.qm$"),".png");
            ptr->addItem(QIcon(pngfile),name);
        }
    }

}

QString DialogConfiguration::getTranslationQmFileName(QString language)
{
    if (language=="English") return QString();
    QSettings s;
    QFileInfo f1(s.fileName());
    QString dirname=f1.absolutePath()+"/Languages/"+language;
    QDir d(dirname);
    QStringList filter;
    filter<<"*.qm";
    QFileInfoList fi=d.entryInfoList(filter);
    if (fi.count()>1)
        return fi.at(0).absoluteFilePath();
}

void DialogConfiguration::SetPDFReader()
{
    QString pdfreader=QFileDialog::getOpenFileName(this,tr("Choose PDF Reader program"),"/");
    ui->lineEditPDFReaderName->setText(pdfreader);
    emit PdfReaderChanged();
}

void DialogConfiguration::Connect()
{
    connect(ui->comboBoxInterfaceLanguage,SIGNAL(currentIndexChanged(QString)),this,SLOT(SelectLanguage(QString)));

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
    QString filename=getTranslationQmFileName(lang);
    tr.load(filename);
    if ( lang != "English" )
       {
          qApp->installTranslator(&tr);
       }
    else
       {
          qApp->removeTranslator(&tr);
       }
    Retranslate(lang);
    emit LanguageChanged(lang);
}


void DialogConfiguration::Retranslate(QString lang)
{
    ui->comboBoxInterfaceLanguage->disconnect();
    ui->retranslateUi(this);
    //ui->comboBoxInterfaceLanguage->setCurrent;
    connect(ui->comboBoxInterfaceLanguage,SIGNAL(currentIndexChanged(int)),this,SLOT(SelectLanguage(int)));

}

void DialogConfiguration::InitSettings()
{
    Settings s;
    ui->comboBoxInterfaceLanguage->setCurrentIndex(s.value("InterfaceLanguage",0).toInt());
    ui->comboBoxUnit->setCurrentText(s.value("Unit","mm").toString());
    ui->lineEditCreatoName->setText(s.value("CreatorName","").toString());
    ui->lineEditPDFReaderName->setText(s.value("PDFReader","").toString());
}

void DialogConfiguration::Save()
{
   QSettings s;
   s.setValue("InterfaceLanguage",ui->comboBoxInterfaceLanguage->currentIndex());
   s.setValue("Unit",ui->comboBoxUnit->currentText());
   s.setValue("CreatorName",ui->lineEditCreatoName->text());
   s.setValue("PDFReader",ui->lineEditPDFReaderName->text());
   ui->memoryConfig->Save(s.fileName(),FormConfig::Memory);
   ui->chordConfig->Save(s.fileName(),FormConfig::Chord);
   ui->textConfig->Save(s.fileName(),FormConfig::Text);
   ui->lyricsConfig->Save(s.fileName(),FormConfig::Lyrics);
   close();
}
