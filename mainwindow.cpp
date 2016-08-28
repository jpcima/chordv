#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialogabout.h"
#include "dialogconfiguration.h"
#include "util.h"
#include "processortext.h"
#include "settings.h"

#include <QDebug>
#include <QFileDialog>
#include <QSettings>
#include <QFileInfo>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tabWidget->setCurrentIndex(0);
    m_lastmenu= new QMenu(tr("Last Projects"));
    ui->actionLast_Project=ui->menuFile->insertMenu(ui->actionSave_Current_as_Defaut,m_lastmenu);
    connect(m_lastmenu,SIGNAL(triggered(QAction*)),this,SLOT(LastProjectOpen(QAction*)));
    setMenuLastProject();
    InitProject();
    connect(ui->actionNew_Project,SIGNAL(triggered(bool)),this,SLOT(newProject(bool)));
    connect(ui->actionOpen_Project,SIGNAL(triggered(bool)),this,SLOT(openProject(bool)));
    connect(ui->actionOpen_Song_File,SIGNAL(triggered(bool)),this,SLOT(openChoFile(bool)));
    connect(ui->actionSave,SIGNAL(triggered(bool)),this,SLOT(Save(bool)));
    connect(ui->actionSave_As,SIGNAL(triggered(bool)),this,SLOT(SaveAs(bool)));
    connect(ui->actionQuit,SIGNAL(triggered(bool)),this,SLOT(close()));
    connect(ui->actionProduce_PDF_files,SIGNAL(triggered(bool)),this,SLOT(ProducePDF()));
    connect(ui->actionPreferences,SIGNAL(triggered(bool)),this,SLOT(Configuration()));
    connect(ui->actionReset_Preference_as_origine,SIGNAL(triggered(bool)),this,SLOT(PreferencesAsOrigine()));
    connect(ui->actionSave_Current_as_Defaut,SIGNAL(triggered(bool)),this,SLOT(CurrentAsDefault()));
    connect(ui->pushButtonPrintPDF,SIGNAL(clicked(bool)),this,SLOT(ProducePDF()));
    connect(ui->toolButtonInputFile,SIGNAL(clicked(bool)),this,SLOT(SetInputFile()));
    connect(ui->checkBoxChordMode,SIGNAL(stateChanged(int)),this,SLOT(setChordMode(int)));
    connect(ui->checkBoxLyricsMode,SIGNAL(stateChanged(int)),this,SLOT(setLyricsMode(int)));
    connect(ui->checkBoxTextMode,SIGNAL(stateChanged(int)),this,SLOT(setTextMode(int))); 
    connect(ui->checkBoxMemoryMode,SIGNAL(stateChanged(int)),this,SLOT(setMemoryMode(int)));
    connect(ui->actionAbout,SIGNAL(triggered()),this,SLOT(About()));
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
   QSettings s;
   QString file=QFileDialog::getOpenFileName(this,tr("Open text file"),s.value("DirCurrentProject").toString(),tr("cho3 file(*.cho3)"));
   ui->lineEditInputFile->setText(file);
   openFile(file);

}

void MainWindow::SetInputFile()
{
    QSettings s;
    QString file=QFileDialog::getOpenFileName(this,tr("Open text file"),s.value("DirCurrentProject").toString(),tr("cho3 file(*.cho3)"));
    ui->lineEditInputFile->setText(file);
    openFile(file);
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
    qDebug()<<s.value("%General/File","")<<s.fileName();
    ui->lineEditCreatorName->setText(s.value("Creator","").toString());
    ui->lineEditInputFile->setText(s.value("File","").toString());
    ui->checkBoxChordMode->setChecked(s.value("Chord","1").toBool());
    ui->checkBoxLyricsMode->setChecked(s.value("Lyrics","1").toBool());
    ui->checkBoxTextMode->setChecked(s.value("Text","1").toBool());
    ui->checkBoxMemoryMode->setChecked(s.value("Memory","1").toBool());
    openFile(ui->lineEditInputFile->text());
}


void MainWindow::openFile( QString filename)
{
    QFileInfo fi(filename);
    QSettings s;
    if ( !filename.isEmpty())   s.setValue("LastOpenedDirectory",fi.absolutePath());
    QDir dir(fi.dir());
    s.setValue("DirCurrentProject",dir.absolutePath());
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) ui->log->Error(QString(tr("Cannot open file : %1").arg(filename)));
    else
    {
        QTextStream in(&file);
        ui->textEditCho3File->clear();
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
    QSettings p(filename,QSettings::IniFormat);
    ui->lineEditInputFile->setText(p.value("General/File").toString());
    ui->lineEditCreatorName->setText(p.value("General/Creator").toString());
    ui->comboBoxChordLanguage->setCurrentText(p.value("General/ChordLang").toString());

    ui->widgetChordMode->SetConfigFromFile(filename);
    ui->widgetChordMode->InitDefault(FormConfig::Chord);
    ui->widgetLyricsMode->SetConfigFromFile(filename);
    ui->widgetLyricsMode->InitDefault(FormConfig::Lyrics);
    ui->widgetMemoryMode->SetConfigFromFile(filename);
    ui->widgetMemoryMode->InitDefault(FormConfig::Memory);
    ui->widgetTextMode->SetConfigFromFile(filename);
    ui->widgetTextMode->InitDefault(FormConfig::Text);
}

void MainWindow::openProject ( bool)

{
   QSettings s;
   QString filename=QFileDialog::getOpenFileName(this,tr("Open conf file"),s.value("LastOpenedDirectory").toString(),"*.conf");
   openProject(filename);
   Util::MemorizeProject(filename);
   setMenuLastProject();

}



void MainWindow::Save(QString filename)
{
    QSettings sf(filename,QSettings::IniFormat);
    sf.clear();
    sf.setValue("General/Creator",ui->lineEditCreatorName->text());
    sf.setValue("General/File",ui->lineEditInputFile->text());
    sf.setValue("General/ChordLang",ui->comboBoxChordLanguage->currentText());
    sf.sync();
    if ( ui->checkBoxChordMode->isChecked()) ui->widgetChordMode->Save(filename,FormConfig::Chord);
    if ( ui->checkBoxLyricsMode->isChecked()) ui->widgetLyricsMode->Save(filename,FormConfig::Lyrics);
    if ( ui->checkBoxTextMode->isChecked()) ui->widgetTextMode->Save(filename,FormConfig::Text);
    if ( ui->checkBoxMemoryMode->isChecked()) ui->widgetMemoryMode->Save(filename,FormConfig::Memory);
}


void MainWindow::Save(bool)
{
    if ( m_currentproject.isEmpty())
        SaveAs(true);
    QSettings sf(m_currentproject,QSettings::IniFormat);
    sf.clear();
    sf.setValue("General/Creator",ui->lineEditCreatorName->text());
    sf.setValue("General/File",ui->lineEditInputFile->text());
    sf.setValue("General/ChordLang",ui->comboBoxChordLanguage->currentText());
    sf.sync();
    if ( ui->checkBoxChordMode->isChecked()) ui->widgetChordMode->Save(m_currentproject,FormConfig::Chord);
    if ( ui->checkBoxLyricsMode->isChecked()) ui->widgetLyricsMode->Save(m_currentproject,FormConfig::Lyrics);
    if ( ui->checkBoxTextMode->isChecked()) ui->widgetTextMode->Save(m_currentproject,FormConfig::Text);
    if ( ui->checkBoxMemoryMode->isChecked()) ui->widgetMemoryMode->Save(m_currentproject,FormConfig::Memory);
}


void MainWindow::SaveAs(bool)
{
    QSettings s;
    m_currentproject=QFileDialog::getSaveFileName(this,tr("Save project as"),s.value("LastOpenedDirectory").toString(),tr("Save as (*.conf)"));
    if (!m_currentproject.isEmpty() )   Save(true);
}


void MainWindow::ProducePDF()
{
 //Save(true);
  if (ui->checkBoxTextMode->isChecked())
      ProcessorText Go(ui->textEditCho3File->document()->toPlainText(),
                  ui->lineEditInputFile->text(),ui->widgetTextMode->getUi());
}


void MainWindow::About()
{
  DialogAbout *d = new DialogAbout(this) ;
  d->exec();
}


void MainWindow::Configuration()
{
    DialogConfiguration dial(this);
    dial.exec();
}
