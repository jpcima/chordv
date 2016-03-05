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
  }

void MainWindow::setChordMode( int i)
{
    ui->tabWidget->setTabEnabled(2,i!=0);
}

void MainWindow::setTextMode(int i)
{
    ui->tabWidget->setTabEnabled(3,i!=0);
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
   if ( !filename.isEmpty())
   {
               QFileInfo fi(filename);
               s.setValue("LastOpenedDirectory",fi.absolutePath());
   }

   QSettings p(filename,QSettings::IniFormat,this);
   ui->lineEditInputFile->setText(p.value("File").toString());
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
   p.endGroup();
   p.beginGroup("TextBook");
   ui->checkBoxTextMode->setChecked(p.allKeys().count()!=0);
   p.endGroup();
}


