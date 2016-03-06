#include "mainwindow.h"
#include "ui_mainwindow.h"


#include <QDebug>
#include <QFileDialog>
#include <QSettings>
#include <QFileInfo>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actionNew_Project,SIGNAL(triggered(bool)),this,SLOT(newProject(bool)));
    connect(ui->actionOpen_Project,SIGNAL(triggered(bool)),this,SLOT(openProject(bool)));
    connect(ui->actionSave,SIGNAL(triggered(bool)),this,SLOT(Save(bool)));
    connect(ui->actionSave_As,SIGNAL(triggered(bool)),this,SLOT(SaveAs(bool)));
    connect(ui->actionQuit,SIGNAL(triggered(bool)),this,SLOT(close()));
    connect(ui->checkBoxChordMode,SIGNAL(stateChanged(int)),this,SLOT(setChordMode(int)));
    connect(ui->checkBoxLyricsMode,SIGNAL(stateChanged(int)),this,SLOT(setLyricsMode(int)));
    connect(ui->checkBoxTextMode,SIGNAL(stateChanged(int)),this,SLOT(setTextMode(int)));
  }

void MainWindow::setChordMode( int i)
{
    ui->tabWidget->setTabEnabled(2,i!=0);
}

void MainWindow::setTextMode(int i)
{
    ui->tabWidget->setTabEnabled(3,i!=0);
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

}

void MainWindow::openProject ( bool)

{
   QSettings s;
   QString filename=QFileDialog::getOpenFileName(this,tr("Open conf file"),s.value("LastOpenedDirectory").toString(),"*.conf");
   QFileInfo fi(filename);
   if ( !filename.isEmpty())
   {
               s.setValue("LastOpenedDirectory",fi.absolutePath());
   }

   QSettings p(filename,QSettings::IniFormat,this);
   QString inputfile=fi.absolutePath()+QString("/")+p.value("File").toString();
   m_currentproject=inputfile;
   ui->lineEditInputFile->setText(inputfile);

   QFile file(inputfile);
   if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) ui->log->Error(QString(tr("Cannot open file : %1").arg(inputfile)));
   else
   {
       QTextStream in(&file);
       ui->textEdit->clear();
       ui->textEdit->append(in.readAll());
       QTextCursor textCursor = ui->textEdit->textCursor();
       textCursor.movePosition(QTextCursor::Start, QTextCursor::MoveAnchor);
       ui->textEdit->setTextCursor(textCursor);
       m_editorhighlight = new EditorHighlighter(ui->textEdit->document());
       m_editorhighlight->highlightBlock(ui->textEdit->document()->toPlainText());
   }
   ui->lineEditCreatorName->setText(p.value("Creator").toString());
   p.beginGroup("LyricsBook");
   ui->checkBoxLyricsMode->setChecked(p.allKeys().count()!=0);
   foreach ( QString key, p.allKeys())
   {
      ui->widgetLyricsMode->setValue(key,p.value(key));
   }
   p.endGroup();
   p.beginGroup("ChordBook");
   ui->checkBoxChordMode->setChecked(p.allKeys().count()!=0);
   foreach ( QString key, p.allKeys())
   {
      ui->widgetChordMode->setValue(key,p.value(key));
   }
   p.endGroup();
   p.beginGroup("TextBook");
   ui->checkBoxTextMode->setChecked(p.allKeys().count()!=0);
   foreach ( QString key, p.allKeys())
   {
      ui->widgetTextMode->setValue(key,p.value(key));
   }
   p.endGroup();
}


void MainWindow::Save(bool)
{
    if ( m_currentproject.isEmpty())
        SaveAs(true);
    QSettings sf(m_currentproject,QSettings::IniFormat,this);
    sf.clear();
    sf.setValue("General/Creator",ui->lineEditCreatorName->text());
    sf.setValue("General/File",ui->lineEditInputFile->text());
    sf.setValue("General/ChordLang",ui->comboBoxChordLanguage->currentText());
    if ( ui->checkBoxChordMode->isChecked()) ui->widgetChordMode->Save(m_currentproject,"ChordBook");
    if ( ui->checkBoxLyricsMode->isChecked()) ui->widgetLyricsMode->Save(m_currentproject,"LyricsBook");
    if ( ui->checkBoxTextMode->isChecked()) ui->widgetTextMode->Save(m_currentproject,"TextBook");

}


void MainWindow::SaveAs(bool)
{
    QSettings s;
    m_currentproject=QFileDialog::getSaveFileName(this,tr("Save project as"),s.value("LastOpenedDirectory").toString(),tr("Save as (*.conf)"));
    if (!m_currentproject.isEmpty() )   Save(true);
}
