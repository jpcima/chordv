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
    connect (ui->actionNew_Project,SIGNAL(triggered(bool)),this,SLOT(newProject(bool)));
    connect (ui->actionOpen_Project,SIGNAL(triggered(bool)),this,SLOT(openProject(bool)));
    connect(ui->actionQuit,SIGNAL(triggered(bool)),this,SLOT(close()));
    connect (ui->checkBoxChordMode,SIGNAL(stateChanged(int)),this,SLOT(setChordMode(int)));
    connect (ui->checkBoxLyricsMode,SIGNAL(stateChanged(int)),this,SLOT(setLyricsMode(int)));
    connect (ui->checkBoxTextMode,SIGNAL(stateChanged(int)),this,SLOT(setTextMode(int)));
   // connect (ui->LyricsMode,SIGNAL(),this,SLOT(Log(QString)));
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


