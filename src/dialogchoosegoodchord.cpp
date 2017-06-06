#include "dialogchoosegoodchord.h"
#include "ui_dialogchoosegoodchord.h"

#include <QSqlQuery>

DialogChooseGoodChord::DialogChooseGoodChord(QString oldname, QString oldvalue, QString newname, QString newvalue,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogChooseGoodChord)
{
    ui->setupUi(this);
    ui->lineEditNewName->setText(newname);
    ui->lineEditOldName->setText(oldname);
    ui->widgetNew->setDiagram(newvalue);
    ui->widgetOld->setDiagram(oldvalue);
    connect (ui->pushButtonKeepOld,SIGNAL(clicked(bool)),this,SLOT(close()));
    connect (ui->pushButtonReplaceOld,SIGNAL(clicked(bool)),this,SLOT(TryToSave()));
}

DialogChooseGoodChord::~DialogChooseGoodChord()
{
    delete ui;
}


void DialogChooseGoodChord::TryToSave()
{
    QString name=ui->lineEditNewName->text();
    QString value=ui->widgetNew->getDiagram();
    QSqlQuery q(QString("SELECT name,value FROM Chords WHERE name='%1' AND approved=1").arg(name));
    if (q.next())
    {
        QString oldname=q.value("name").toString();
        QString oldvalue=q.value("value").toString();
        ui->lineEditOldName->setText(oldname);
        ui->widgetOld->setDiagram(oldvalue);
        emit Error(tr("Warning : Chord name exist in the database with the same name and same value"));
    }
    else
        QSqlQuery qinsert(QString ("INSERT INTO Chords (name,value) VALUES ('%1','%2')").arg(name).arg(value));
}
