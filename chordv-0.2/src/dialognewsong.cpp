#include "dialognewsong.h"
#include "ui_dialognewsong.h"

DialogNewSong::DialogNewSong(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogNewSong)
{
    ui->setupUi(this);
    ActiveInsertButton();
    connect (ui->lineEditTitle,SIGNAL(textChanged(QString)),this,SLOT(ActiveInsertButton()));
    connect (ui->pushButtonCancel,SIGNAL(clicked(bool)),this,SLOT(close()));
    connect (ui->pushButtonInsert,SIGNAL(clicked(bool)),this,SLOT(Insert()));
}

DialogNewSong::~DialogNewSong()
{
    delete ui;
}


void DialogNewSong::ActiveInsertButton()
{
    ui->pushButtonInsert->setDisabled( ui->lineEditTitle->text().isEmpty());
}

void DialogNewSong::Insert()
{
    emit InsertSong(ui->lineEditTitle->text(),ui->lineEditSubtitle->text(),ui->checkBoxCompress->isChecked(),ui->spinBoxColumn->value(),
            ui->spinBoxTime1->value(),ui->spinBoxTime2->value(),ui->spinBoxTempo->value());
    close();
}
