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
    ui->lineEditInputFile->setText(getRelativeFilename(file));
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
    ui->checkBoxChordMode->setChecked(s.value("ChordMode",true).toBool());
    ui->checkBoxLyricsMode->setChecked(s.value("LyricsMode",true).toBool());
    ui->checkBoxTextMode->setChecked(s.value("TextMode",true).toBool());
    ui->checkBoxMemoryMode->setChecked(s.value("MemoryMode",true).toBool());
    QString file=getFileInArg();
    if ( file.isEmpty())
    {
        m_currentprojectdir=s.value("LastOpenedDirectory","").toString();
        m_currentprojectname="";
        m_currentprojectfile="" ;
    }
    else
    {
        QFileInfo fi(file);
        m_currentprojectdir= fi.absolutePath();
        m_currentprojectname=fi.baseName();
        m_currentprojectfile=file;
    }
    ui->labelNameDirProject->setText(m_currentprojectdir);
    ui->labelNameProjectName->setText(m_currentprojectname);
    openChoFile(m_currentprojectfile);
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

    ui->log->clear();
    QFileInfo fi(filename);
    m_currentprojectname=fi.baseName();
    m_currentprojectdir=fi.absolutePath();
    QDir::setCurrent(m_currentprojectdir);
    m_currentprojectfile=filename;
    ui->labelNameProjectName->setText(m_currentprojectname);
    ui->labelNameDirProject->setText(m_currentprojectdir);
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
    openChoFile(m_currentprojectdir+"/"+ui->lineEditInputFile->text());
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
    ui->log->clear();
    if ( ! filename.endsWith(".chop") && !filename.endsWith(".conf")) filename+=".chop";
    QSettings sf(filename,QSettings::IniFormat);
    sf.clear();
    sf.setValue("Creator",ui->lineEditCreatorName->text());
    sf.setValue("File",ui->lineEditInputFile->text());
    sf.setValue("ChordLang",ui->comboBoxChordLanguage->currentIndex());
    sf.setValue("LyricsMode",ui->checkBoxLyricsMode->isChecked());
    sf.setValue("TextMode",ui->checkBoxTextMode->isChecked());
    sf.setValue("MemoryMode",ui->checkBoxMemoryMode->isChecked());
    sf.setValue("ChordMode",ui->checkBoxChordMode->isChecked());
    sf.sync();
    ui->widgetChordMode->Save(filename,FormConfig::Chord);
    ui->widgetLyricsMode->Save(filename,FormConfig::Lyrics);
    ui->widgetTextMode->Save(filename,FormConfig::Text);
    ui->widgetMemoryMode->Save(filename,FormConfig::Memory);
    if ( SaveCho3(ui->lineEditInputFile->text()) )
        ui->log->Info(tr("File saved : %1").arg(filename));
    else
        ui->log->Info(tr("File not well saved : %1").arg(filename));
}

QString MainWindow::getRelativeFilename( QString chofilename )
{
    QDir dir (m_currentprojectdir);
    QString d=dir.relativeFilePath(chofilename);
    return d;
}

void MainWindow::Save(bool)
{
    ui->log->clear();
    QSettings s;
    if ( m_currentprojectname.isEmpty())
        SaveAs(true);
    else m_currentprojectfile=m_currentprojectdir+"/"+m_currentprojectname+".chop";
    QSettings sf(m_currentprojectfile,QSettings::IniFormat);
    sf.clear();
    sf.setValue("Creator",ui->lineEditCreatorName->text());
    sf.setValue("File",ui->lineEditInputFile->text());
    sf.setValue("ChordMode",ui->checkBoxChordMode->isChecked());
    sf.setValue("LyricsMode",ui->checkBoxLyricsMode->isChecked());
    sf.setValue("TextMode",ui->checkBoxTextMode->isChecked());
    sf.setValue("MemoryMode",ui->checkBoxMemoryMode->isChecked());
    sf.sync();
    ui->widgetChordMode->Save(m_currentprojectfile,FormConfig::Chord);
    ui->widgetLyricsMode->Save(m_currentprojectfile,FormConfig::Lyrics);
    ui->widgetTextMode->Save(m_currentprojectfile,FormConfig::Text);
    ui->widgetMemoryMode->Save(m_currentprojectfile,FormConfig::Memory);
    if ( SaveCho3(ui->lineEditInputFile->text()) )
        ui->log->Info(tr("File saved : %1").arg(m_currentprojectfile));
    else
        ui->log->Info(tr("File not well saved : %1").arg(m_currentprojectfile));
}


void MainWindow::SaveAs(bool)
{
    QSettings s;
    m_currentprojectfile=QFileDialog::getSaveFileName(this,tr("Save project as"),Util::getLastDirectory(),tr("Save as (*.chop)"));
    if (!m_currentprojectfile.isEmpty() )
    {
        Save(true);
        Util::setLastDirectory(m_currentprojectfile);
    }
}

void MainWindow::ActualizeProject( QString file)
{

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


bool MainWindow::SaveCho3(QString filename)
{
    QString f(m_currentprojectdir+"/"+filename);
    QFile file( f);
   if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
   {
       ui->log->Error(QString("Cannot write file : %1").arg(f));
       return false;
   }
    QTextStream out(&file);
    out << ui->textEditCho3File->document()->toPlainText();
    file.close();
    return true;
}
