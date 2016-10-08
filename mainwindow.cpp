#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialogabout.h"
#include "dialogconfiguration.h"
#include "util.h"
#include "processortext.h"
#include "settings.h"
#include "logmessages.h"

#include <QDebug>
#include <QFileDialog>
#include <QSettings>
#include <QFileInfo>
#include <QTranslator>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tabWidget->setCurrentIndex(0);
    m_lastmenu= new QMenu(tr("Last Projects"));
    ui->actionLast_Project=ui->menuFile->insertMenu(ui->actionSave_Current_as_Defaut,m_lastmenu);
    setMenuLastProject();
    connect(m_lastmenu,SIGNAL(triggered(QAction*)),this,SLOT(LastProjectOpen(QAction*)));
    connect(ui->checkBoxChordMode,SIGNAL(stateChanged(int)),this,SLOT(setChordMode(int)));
    connect(ui->checkBoxLyricsMode,SIGNAL(stateChanged(int)),this,SLOT(setLyricsMode(int)));
    connect(ui->checkBoxTextMode,SIGNAL(stateChanged(int)),this,SLOT(setTextMode(int)));
    connect(ui->checkBoxMemoryMode,SIGNAL(stateChanged(int)),this,SLOT(setMemoryMode(int)));
    InitProject();
    connect(ui->actionNew_Project,SIGNAL(triggered(bool)),this,SLOT(newProject(bool)));
    connect(ui->actionOpen_Project,SIGNAL(triggered(bool)),this,SLOT(openProject(bool)));
    connect(ui->actionOpen_Song_File,SIGNAL(triggered(bool)),this,SLOT(openChoFile(bool)));
    connect(ui->actionSave,SIGNAL(triggered(bool)),this,SLOT(Save(bool)));
    connect(ui->actionSave_As,SIGNAL(triggered(bool)),this,SLOT(SaveAs(bool)));
    connect(ui->actionQuit,SIGNAL(triggered(bool)),this,SLOT(close()));
    //connect(ui->pushButtonPrintPDF_3,SIGNAL(triggered(bool)),this,SLOT(ProducePDF()));
    connect(ui->actionPreferences,SIGNAL(triggered(bool)),this,SLOT(Configuration()));
    connect(ui->actionReset_Preference_as_origine,SIGNAL(triggered(bool)),this,SLOT(PreferencesAsOrigine()));
    connect(ui->actionSave_Current_as_Defaut,SIGNAL(triggered(bool)),this,SLOT(CurrentAsDefault()));
    connect(ui->pushButtonPrintPDF,SIGNAL(clicked(bool)),this,SLOT(ProducePDF()));
    connect(ui->toolButtonInputFile,SIGNAL(clicked(bool)),this,SLOT(SetInputFile()));
    connect(ui->actionAbout,SIGNAL(triggered()),this,SLOT(About()));
    QString file=getFileInArg();
    if ( ! file.isEmpty() )
    {
        QFileInfo fi(file) ;
        if ( ! fi.exists())
        {
            qInfo()<<tr("%1 does'nt exit. Bye !") ;
            exit(1);
        }
        openProject(file);
    }
    if ( testMode())
    {
        ProducePDF();
        exit(0);
    }

  }

 QString MainWindow::getFileInArg()
{
    QStringList list=qApp->arguments();
    if ( list.empty()) return ("");
    list.removeFirst();
    foreach ( QString arg,list )
    {
        if ( ! arg.startsWith("-")) return arg;
    }
    return ("");
}

bool MainWindow::testMode()
{
    foreach ( QString arg, qApp->arguments() )
    {
        if (  arg== "-t" || arg =="--test" ) return true;
    }
    return false;
}

void MainWindow::PreferencesAsOrigine()
{
    QSettings s;
    QFile file(s.fileName());

    file.remove();
    ui->widgetChordMode->InitDefault(FormConfig::Chord);
    ui->widgetLyricsMode->InitDefault(FormConfig::Lyrics);
    ui->widgetMemoryMode->InitDefault(FormConfig::Memory);
    ui->widgetTextMode->InitDefault(FormConfig::Text);
    // TODO restore global elem.

}

void MainWindow::CurrentAsDefault()
{
    QSettings s;
    Save(s.fileName());
}

void MainWindow::openChoFile(bool)
{
   QString file=QFileDialog::getOpenFileName(this,tr("Open text file"),Util::getLastDirectory(),tr("cho3 file(*.cho3)"));
   ui->lineEditInputFile->setText(file);
   Util::setLastDirectory(file);
   openChoFile(file);

}

void MainWindow::SetInputFile()
{
    QSettings s;
    QString file=QFileDialog::getOpenFileName(this,tr("Open text file"),Util::getLastDirectory(),tr("cho3 file(*.cho3)"));
    ui->lineEditInputFile->setText(file);
    openChoFile(file);
}

void MainWindow::setMenuLastProject()
{
    m_lastmenu->clear();
    foreach ( QString l, Util::LastProjects())
    {
        QAction *a= new QAction(l,this);
        m_lastmenu->addAction(a);
    }
}

void MainWindow::LastProjectOpen(QAction *action )
{
    openProject(action->text());
}

void MainWindow::setChordMode( int i)
{
    ui->tabWidget->setTabEnabled(2,i!=0);
}

void MainWindow::setTextMode(int i)
{
    ui->tabWidget->setTabEnabled(3,i!=0);
}

void MainWindow::setMemoryMode(int i)
{
    ui->tabWidget->setTabEnabled(4,i!=0);
}

void MainWindow::Log(QString message)
{
    ui->log->Error(message);
}

void MainWindow::setLyricsMode(int i)
{
    ui->tabWidget->setTabEnabled(1,i!=0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newProject( bool)
{
 InitProject();
}


void MainWindow::InitProject()
{
    Settings s;
    ui->lineEditCreatorName->setText(s.value("Creator","").toString());
    ui->lineEditInputFile->setText(s.value("File","").toString());
    ui->lineEditWatermark->setText(s.value("Watermark","").toString());
    ui->checkBoxChordMode->setChecked(s.value("Chord",true).toBool());
    ui->checkBoxLyricsMode->setChecked(s.value("Lyrics",true).toBool());
    ui->checkBoxTextMode->setChecked(s.value("Text",true).toBool());
    ui->checkBoxMemoryMode->setChecked(s.value("Memory",true).toBool());
    QString file=getFileInArg();
    if ( file.isEmpty())
        m_currentdirproject=s.value("LastOpenedDirectory","").toString();
    else
    {
        QFileInfo fi(file);
        m_currentdirproject= fi.absolutePath();
    }
    m_currentproject=ui->lineEditInputFile->text().replace(QRegExp(".cho3$"),"");
    ui->labelNameDirProject->setText(m_currentdirproject);
    ui->labelNameProjectName->setText(m_currentproject);
    openChoFile(m_currentdirproject+"/"+ui->lineEditInputFile->text());
}



void MainWindow::openChoFile( QString filename)
{
    QFile file(filename);
    ui->textEditCho3File->clear();
    ui->pushButtonPrintPDF->setDisabled(true);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) ui->log->Error(QString(tr("Cannot open file : %1").arg(filename)));
    else
    {
        ui->pushButtonPrintPDF->setDisabled(false);
        QTextStream in(&file);
        ui->textEditCho3File->append(in.readAll());
        QTextCursor textCursor = ui->textEditCho3File->textCursor();
        textCursor.movePosition(QTextCursor::Start, QTextCursor::MoveAnchor);
        ui->textEditCho3File->setTextCursor(textCursor);
        m_editorhighlight = new EditorHighlighter(ui->textEditCho3File->document());
        m_editorhighlight->highlightBlock(ui->textEditCho3File->document()->toPlainText());
    }
}

void MainWindow::openProject(QString filename)
{

    QFileInfo fi(filename);
    m_currentproject=fi.baseName();
    m_currentdirproject=fi.absolutePath();
    ui->labelNameProjectName->setText(m_currentproject);
    ui->labelNameDirProject->setText(m_currentdirproject);
    QSettings p(filename,QSettings::IniFormat);
    ui->lineEditInputFile->setText(p.value("File").toString());
    ui->lineEditCreatorName->setText(p.value("Creator").toString());
    ui->comboBoxChordLanguage->setCurrentIndex(p.value("ChordLang").toInt());
    ui->lineEditWatermark->setText(p.value("Watermark").toString());
    ui->checkBoxChordMode->setChecked(p.value("ChordMode").toBool());
    ui->checkBoxLyricsMode->setChecked(p.value("LyricsMode").toBool());
    ui->checkBoxMemoryMode->setChecked(p.value("MemoryMode").toBool());
    ui->checkBoxTextMode->setChecked(p.value("TextMode").toBool());
    ui->widgetChordMode->SetConfigFromFile(filename);
    ui->widgetChordMode->InitDefault(FormConfig::Chord);
    ui->widgetLyricsMode->SetConfigFromFile(filename);
    ui->widgetLyricsMode->InitDefault(FormConfig::Lyrics);
    ui->widgetMemoryMode->SetConfigFromFile(filename);
    ui->widgetMemoryMode->InitDefault(FormConfig::Memory);
    ui->widgetTextMode->SetConfigFromFile(filename);
    ui->widgetTextMode->InitDefault(FormConfig::Text);
    openChoFile(m_currentdirproject+"/"+ui->lineEditInputFile->text());
}

void MainWindow::openProject ( bool)

{
   QSettings s;
   QString filename=QFileDialog::getOpenFileName(this,tr("Open conf file"),Util::getLastDirectory(),"*.chop");
   openProject(filename);
   Util::setLastDirectory(filename);
   Util::MemorizeProject(filename);
   setMenuLastProject();
}



void MainWindow::Save(QString filename)
{
    if ( ! filename.endsWith(".chop") && !filename.endsWith(".conf")) filename+=".chop";
    QSettings sf(filename,QSettings::IniFormat);
    sf.clear();
    sf.setValue("Creator",ui->lineEditCreatorName->text());
    sf.setValue("File",getRelativeFilename(ui->lineEditInputFile->text(),filename));
    sf.setValue("ChordLang",ui->comboBoxChordLanguage->currentIndex());
    sf.setValue("Lyrics",ui->checkBoxLyricsMode->isChecked());
    sf.setValue("Text",ui->checkBoxTextMode->isChecked());
    sf.sync();
    ui->widgetChordMode->Save(filename,FormConfig::Chord);
    ui->widgetLyricsMode->Save(filename,FormConfig::Lyrics);
    ui->widgetTextMode->Save(filename,FormConfig::Text);
    ui->widgetMemoryMode->Save(filename,FormConfig::Memory);
}

QString MainWindow::getRelativeFilename( QString chofilename, QString chopfilename )
{
    QFileInfo fi(chopfilename);
    QDir dir (fi.absoluteDir());
    QString d=dir.relativeFilePath(chofilename);
    return d;

}

void MainWindow::Save(bool)
{
    QSettings s;
    if ( m_currentproject.isEmpty())
        SaveAs(true);
    else m_currentproject+=".chop";

    QSettings sf(m_currentdirproject + "/"+m_currentproject,QSettings::IniFormat);
    sf.clear();
    sf.setValue("Creator",ui->lineEditCreatorName->text());
    sf.setValue("File",getRelativeFilename(ui->lineEditInputFile->text(),m_currentproject));
    sf.setValue("ChordLang",ui->comboBoxChordLanguage->currentText());
    sf.setValue("Lyrics",ui->checkBoxLyricsMode->isChecked());
    sf.setValue("Chord",ui->checkBoxChordMode->isChecked());
    sf.setValue("Memory",ui->checkBoxMemoryMode->isChecked());
    sf.setValue("Text",ui->checkBoxTextMode->isChecked());
    sf.setValue("ChordMode",ui->checkBoxChordMode->isChecked());
    sf.setValue("LyricsMode",ui->checkBoxLyricsMode->isChecked());
    sf.setValue("TextMode",ui->checkBoxTextMode->isChecked());
    sf.setValue("MemoryMode",ui->checkBoxMemoryMode->isChecked());
    sf.sync();
    ui->widgetChordMode->Save(m_currentdirproject + "/"+m_currentproject,FormConfig::Chord);
    ui->widgetLyricsMode->Save(m_currentdirproject + "/"+m_currentproject,FormConfig::Lyrics);
    ui->widgetTextMode->Save(m_currentdirproject + "/"+m_currentproject,FormConfig::Text);
    ui->widgetMemoryMode->Save(m_currentdirproject + "/"+m_currentproject,FormConfig::Memory);
}


void MainWindow::SaveAs(bool)
{
    QSettings s;
    m_currentproject=QFileDialog::getSaveFileName(this,tr("Save project as"),Util::getLastDirectory(),tr("Save as (*.chop)"));

    if (!m_currentproject.isEmpty() )
    {
        Save(true);
        Util::setLastDirectory(m_currentproject);
    }
}


void MainWindow::ProducePDF()
{
 //Save(true);
  if (ui->checkBoxTextMode->isChecked())
  {
      ProcessorText *p;
      p= new ProcessorText(ui,ui->widgetTextMode->getUi());
      connect(p,SIGNAL(PDFMade(QString)),this, SLOT(Info(QString)));
      p->run() ;
      p->deleteLater();
  }
}

void MainWindow::Info(QString info)
{
    ui->log->Info(info);
}


void MainWindow::About()
{
  DialogAbout *d = new DialogAbout(this) ;
  d->exec();
}


void MainWindow::Configuration()
{
    DialogConfiguration * dial = new DialogConfiguration(this);
    connect ( dial,SIGNAL(LanguageChanged(int)),this,SLOT(ChangeLanguage(int)));
    dial->exec();
    delete dial;
}

void MainWindow::ChangeLanguage(int)
{
    ui->retranslateUi(this);
    ui->widgetChordMode->Retranslate();
    ui->widgetLyricsMode->Retranslate();
    ui->widgetMemoryMode->Retranslate();
    ui->widgetTextMode->Retranslate();
}
