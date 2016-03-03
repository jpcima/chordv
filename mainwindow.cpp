#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect (ui->actionNew_Project,SIGNAL(triggered(bool)),this,SLOT(newProject(bool)));
    connect (ui->actionOpn_Project,SIGNAL(triggered(bool)),this,SLOT(openProject(bool)));
    connect(ui->actionQuit,SIGNAL(triggered(bool)),this,SLOT(close()));
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

}
