#include "dialogchorddefinition.h"
#include "ui_dialogchorddefinition.h"
#include "util.h"
#include "logmessages.h"
#include "dialogchoosegoodchord.h"

#include <QVector>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QTextCursor>
#include <QTextBlock>
#include <QGraphicsScene>
#include <QRegExp>
#include <QSqlError>


DialogChordDefinition::DialogChordDefinition(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogChordDefinition)
{
    ui->setupUi(this);
    connect ( ui->pushButtonCancel,SIGNAL(clicked(bool)),this,SLOT(close()));
    connect (ui->pushButtonImport,SIGNAL(clicked(bool)),this,SLOT(Import()));
    connect ( ui->neck,SIGNAL(ChordsDetected(QStringList,QString)),this,SLOT(ShowChords(QStringList,QString)));
    connect (ui->listWidgetChords,SIGNAL(clicked(QModelIndex)),this,SLOT(ShowChord(QModelIndex)));
    connect (ui->toolButtonPlus,SIGNAL(clicked(bool)),this,SLOT(AddChord()));
    m_model=new QSqlTableModel(this);
    m_model->setTable("Chords");
    m_model->setHeaderData(0,Qt::Horizontal,tr("Name"));
    m_model->setHeaderData(1,Qt::Horizontal,tr("Value"));
    m_model->setHeaderData(2,Qt::Horizontal,tr("Index"));
    m_model->select();
    ui->tableView->setModel(m_model);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::ContiguousSelection);
    ui->pushButtonInsertChord->setVisible(false);
    connect(ui->tableView,SIGNAL(clicked(QModelIndex)),this,SLOT(ChordClicked(QModelIndex)));
    connect (ui->pushButtonModify,SIGNAL(clicked(bool)),this,SLOT(ModifyChord()));
    connect (ui->pushButtonDelete,SIGNAL(clicked(bool)),this,SLOT(DeleteChord()));
    connect (ui->radioButtonChordName,SIGNAL(clicked(bool)),this,SLOT(SortOnChord(bool)));
    connect (ui->radioButtonFret,SIGNAL(clicked(bool)),this,SLOT(SortOnFret(bool)));
    connect (ui->radioButtonSortIndex,SIGNAL(clicked(bool)),this,SLOT(SortOnIndex(bool)));
    connect (ui->toolButtonClearFilter,SIGNAL(clicked(bool)),ui->lineEditFilter,SLOT(clear()));
    connect (ui->lineEditFilter,SIGNAL(textChanged(QString)),this,SLOT(SetFilter(QString)));
    connect (ui->pushButtonInsertChord,SIGNAL(clicked(bool)),this,SLOT(InsertChord(bool)));
}

void DialogChordDefinition::ActiveInsertButton()
{
    ui->pushButtonInsertChord->setVisible(true);
    ui->tabWidget->setCurrentIndex(1);
    ui->tabWidget->removeTab(2);
    ui->tabWidget->removeTab(0);
    this->setWindowTitle(tr("Chord insertion"));
}

void DialogChordDefinition::InsertChord(bool )
{
  if ( ! ui->lineEditNameIndex->text().isEmpty()) emit ChordToInsert(QString("[%1]").arg(ui->lineEditNameIndex->text()));
  close();
}

void DialogChordDefinition::SetFilter(QString filter)
{
    m_model->setFilter(QString("name LIKE '%1%'").arg(filter));
    m_model->select();
}

void DialogChordDefinition::SortOnFret(bool checked)
{
    if ( checked ) m_model->setSort(1,Qt::AscendingOrder);
    m_model->select();
}


void DialogChordDefinition::SortOnIndex( bool checked)
{
    if (checked ) m_model->setSort(2,Qt::AscendingOrder);
    m_model->select();
}


void DialogChordDefinition::SortOnChord( bool checked)
{
    if (checked) m_model->setSort(0,Qt::AscendingOrder);
    m_model->select();
}

void DialogChordDefinition::ModifyChord()
{
    QSqlQuery q(QString("UPDATE Chords SET name='%1', value='%1' WHERE Index='%3'")
                .arg(ui->lineEditNameIndex->text()).arg(ui->lineEditValueIndex->text())
                .arg(m_index));
    m_model->select();
}

void DialogChordDefinition::DeleteChord()
{
    foreach ( QModelIndex index, ui->tableView->selectionModel()->selectedIndexes())
    {
        QSqlQuery q(QString("DELETE FROM Chords WHERE  Id=%1")
                    .arg(index.sibling(index.row(),2).data().toString()));
    }
    m_model->select();
}

void DialogChordDefinition::ChordClicked(QModelIndex index)
{
    QString name=index.sibling(index.row(),1).data().toString();
    ui->lineEditNameIndex->setText(index.sibling(index.row(),0).data().toString());
    ui->lineEditValueIndex->setText(name);
    m_index=index.sibling(index.row(),2).data().toInt();
    ui->widget->setDiagram(ui->lineEditValueIndex->text());

}

DialogChordDefinition::~DialogChordDefinition()
{
    delete ui;
}

void DialogChordDefinition::ShowChords(QStringList chordnames,QString chordstring)
{
   QString chordmin=tr("Undertermined");
   foreach ( QString chord, chordnames)
       if (chord.length()< chordmin.length() ) chordmin=chord;
   ui->lineEditChord->setText(chordmin);
   ui->listWidgetChords->clear();
   ui->listWidgetChords->addItems(chordnames);
   ui->lineEditNotation->setText(chordstring);
   ui->lineEditName->setText(findName(chordstring,chordmin));

}


QString DialogChordDefinition::findName( QString chordstring, QString chordname)
{
    int notemin=100;
    QStringList chord=chordstring.split("-");
    QVector <QString> notes(6);
    int i=0;
    bool ok=false;
    foreach ( QString string , chord)
    {
        if ( string != "x")
        {
            int note=string.toInt();
            if ( note < notemin) notemin = note;
            notes[i]=QString("%1").arg(note);
            ok =true;
        }
        else notes[i]="x";
        i++;
    }
    if (! ok) return("");
    if ( notemin > 2 )
    {
        for (int j=0; j<=5;j++)
        {
           if ( notes[j] != "x" )
           {   int n=notes[j].toInt();
               n-=notemin;
               notes[j]=QString("%1").arg(n);
           }
        }
    }
    else notemin=0;

   chordname.replace(QRegExp("M$"),"").replace(" ","");
   if ( notemin > 2 ) chordname=QString("%1(%2)").arg(chordname).arg(Util::toRomain(notemin));
   return QString("%1:%2 %3 %4 %5 %6 %7 %8")
           .arg(chordname).arg(notemin).arg(notes[0])
           .arg(notes[1]).arg(notes[2]).arg(notes[3])
           .arg(notes[4]).arg(notes[5]);
}

void DialogChordDefinition::ShowChord(QModelIndex index)
{
    QString chordname=index.data().toString();
    ui->lineEditChord->setText(chordname);
    QString newname=chordname;
    newname.replace(" ","");
    QString oldname= ui->lineEditName->text();
    QRegExp exp("^([^:(]+)((?:\\([^:]+){0,1}):");
    if ( oldname.indexOf(exp) != -1)
     {
      QString f=exp.cap(2);
      oldname.replace(exp,QString("%1%2:").arg(newname).arg(f));
     }
    ui->lineEditName->setText(oldname);
}


void DialogChordDefinition::Import()
{
    QStringList lines=ui->plainTextEditImport->toPlainText().split("\n");
    int linenumber=0;
    foreach ( QString line, lines)
    {
        linenumber=1;
        line.replace(QRegExp("^\\s+"),"").replace(QRegExp("\\+$"),"");
        QStringList records=line.split("=");
        if ( records.count()== 2 )
        {
         QSqlQuery q(QString("INSERT INTO Chords (Name,Value) VALUES ('%1', '%2')").arg(records.at(0)).arg(records.at(1)));
         if ( q.lastError().isValid())
             setError(tr("ERROR line %1 : %2").arg(linenumber).arg(q.lastError().text()),linenumber);
        }
        else
            setError(tr("ERROR line %1 :syntax error").arg(linenumber),linenumber);
    }
    m_model->select();


}

void DialogChordDefinition::setError(QString message,int linenumber)
{
    QTextCursor cursor(ui->plainTextEditImport->document()->findBlockByLineNumber(linenumber));
    cursor.select(QTextCursor::BlockUnderCursor);
    ui->plainTextEditImport->setTextCursor(cursor);
    emit Error(message);
}


void DialogChordDefinition::AddChord()
{
    QStringList chord=ui->lineEditName->text().replace("'","").split(":");
    QString name=chord.at(0);
    QString value=chord.at(1);
    QSqlQuery q(QString("SELECT name,value FROM Chords WHERE name='%1'").arg(name));
    if (q.next())
    {
        QString oldname=q.value("name").toString();
        QString oldvalue=q.value("value").toString();
        if ( oldname==name && oldvalue==value )
            emit Error(tr("Warning : Chord name exist in the database with the same name and same value"));
        else
        {
            DialogChooseGoodChord *dial = new DialogChooseGoodChord(oldname,oldvalue,name,value,this);
            connect (dial,SIGNAL(Error(QString)),this,SIGNAL(Error(QString)));
            dial->exec();
        }
    }
    else
        QSqlQuery qinsert(QString ("INSERT INTO Chords (name,value) VALUES ('%1','%2')").arg(name).arg(value));
    m_model->select();
}