#include "dialogtwolinestochordpro.h"
#include "ui_dialogtwolinestochordpro.h"

#include <QDebug>

DialogTwoLinesToChordPro::DialogTwoLinesToChordPro(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogTwoLinesToChordPro)
{
    ui->setupUi(this);
    connect ( ui->pushButtonClose,SIGNAL(clicked(bool)),this,SLOT(close()));
    connect (ui->pushButtonConvert,SIGNAL(clicked(bool)),this,SLOT(Convert()));
    connect(ui->pushButtonClear,SIGNAL(clicked(bool)),ui->textEdit,SLOT(clear()));
}

DialogTwoLinesToChordPro::~DialogTwoLinesToChordPro()
{
    delete ui;
}

void DialogTwoLinesToChordPro::Convert()
{
    QStringList out;
    QStringList lines=ui->textEdit->document()->toPlainText().split("\n");
    foreach ( QString line, lines)
    {
      if( isChords(line) )
          ConvertToMap(line);
      else
          if (MapIsEmpty()) out <<line;
          else
            {
              out<<mixLineAndMap(line);
              ClearMap();
            }
    }
    ui->textEdit->clear();
    ui->textEdit->insertPlainText(out.join("\n"));

}

bool DialogTwoLinesToChordPro::isChords(QString line)
{
    line.replace(QRegExp(" +")," ");
    QStringList words=line.split(" ");
    foreach ( QString word, words)
    {
         if ( ! word.contains(QRegExp("^[ABCDEFG]")))
             return false;
    }
    return true;
}

void DialogTwoLinesToChordPro::ConvertToMap( QString line)
{
    QString listbeginingchord="ABCDEFG";
    for ( int i=0; i< line.count();i++)
    {
        QChar c=line[i];
        if (listbeginingchord.contains(c))
            if (i==0 || line[i-1]==' ')
            {
                QString w;
                int j=i;
                while ( j!=line.count() && line[j] != ' ' )
                {
                    w+=line[j];
                    j++;
                }
                m_chords[i]=w;
            }
    }
}


bool DialogTwoLinesToChordPro::MapIsEmpty()
{
    return m_chords.count()==0;
}

void DialogTwoLinesToChordPro::ClearMap()
{
    m_chords.clear();
}

QString DialogTwoLinesToChordPro::mixLineAndMap(QString line)
{
    foreach ( int i, m_chords.keys())
    {
        line.insert(i,QString("[%1]").arg(m_chords[i]));
    }
    return line;
}
