#include "formeditor.h"
#include "ui_formeditor.h"

#include "dialogbar.h"

#include <QInputDialog>
#include <QDebug>

FormEditor::FormEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormEditor)
{
    ui->setupUi(this);
    connect(ui->toolButtonCB,SIGNAL(clicked(bool)),this,SLOT(InsertCB()));
    connect(ui->toolButtonCol,SIGNAL(clicked(bool)),this,SLOT(InsertCol()));
    connect(ui->toolButtonTempo,SIGNAL(clicked(bool)),this,SLOT(InsertTempo()));
    connect(ui->toolButtonTime,SIGNAL(clicked(bool)),this,SLOT(InsertTime()));
    connect(ui->toolButtonCS,SIGNAL(clicked(bool)),this,SLOT(InsertCS()));
    connect(ui->toolButtonCT,SIGNAL(clicked(bool)),this,SLOT(InsertCT()));
    connect(ui->toolButtonSOC,SIGNAL(clicked(bool)),this,SLOT(InsertSOC()));
    connect(ui->toolButtonEOC,SIGNAL(clicked(bool)),this,SLOT(InsertEOC()));
    connect(ui->toolButtonSOR,SIGNAL(clicked(bool)),this,SLOT(InsertSOR()));
    connect(ui->toolButtonEOR,SIGNAL(clicked(bool)),this,SLOT(InsertEOR()));
    connect(ui->toolButtonSOV,SIGNAL(clicked(bool)),this,SLOT(InsertSOV()));
    connect(ui->toolButtonEOV,SIGNAL(clicked(bool)),this,SLOT(InsertEOV()));
    connect(ui->toolButtonSOG,SIGNAL(clicked(bool)),this,SLOT(InsertSOG()));
    connect(ui->toolButtonEOG,SIGNAL(clicked(bool)),this,SLOT(InsertEOG()));
    connect(ui->toolButtonAlbum,SIGNAL(clicked(bool)),this,SLOT(InsertAlbum()));
    connect(ui->toolButtonComposer,SIGNAL(clicked(bool)),this,SLOT(InsertComposer()));
    connect(ui->toolButtonArtist,SIGNAL(clicked(bool)),this,SLOT(InsertArtist()));
    connect(ui->toolButtonCopyright,SIGNAL(clicked(bool)),this,SLOT(InsertCopyright()));
    connect(ui->toolButtonYear,SIGNAL(clicked(bool)),this,SLOT(InsertYear()));
    connect(ui->toolButtonKey,SIGNAL(clicked(bool)),this,SLOT(InsertKey()));
    connect(ui->toolButtonDuration,SIGNAL(clicked(bool)),this,SLOT(InsertDuration()));
    connect(ui->toolButtonLyricist,SIGNAL(clicked(bool)),this,SLOT(InsertLyricist()));
    connect(ui->toolButtonArranger,SIGNAL(clicked(bool)),this,SLOT(InsertArranger()));
    connect(ui->toolButtonST,SIGNAL(clicked(bool)),this,SLOT(InsertST()));
    connect(ui->toolButtonT,SIGNAL(clicked(bool)),this,SLOT(InsertT()));
    connect(ui->toolButtonPageBreak,SIGNAL(clicked(bool)),this,SLOT(InsertPageBreak()));
    connect(ui->toolButtonComment,SIGNAL(clicked(bool)),this,SLOT(InsertComment()));
    connect(ui->toolButtonCommentItalic,SIGNAL(clicked(bool)),this,SLOT(InsertCommentItalic()));
    connect(ui->toolButtonCommentBox,SIGNAL(clicked(bool)),this,SLOT(InsertCommentBox()));

    connect(ui->checkBoxLongShort,SIGNAL(clicked(bool)),this,SLOT(ToogleLongShort()));
}



void FormEditor::clear()
{
    ui->textEdit->clear();
}

void FormEditor::append(QString value)
{
    ui->textEdit->append(value );
}

QTextCursor FormEditor::textCursor()
{
    return ui->textEdit->textCursor();
}

void FormEditor::setTextCursor (QTextCursor textcursor)
{
    ui->textEdit->setTextCursor(textcursor);
}

void FormEditor::setText(QString text)

{
    ui->textEdit->setText(text);
    ui->checkBoxLongShort->setChecked(ui->textEdit->document()->toPlainText().contains("{title:",Qt::CaseInsensitive));
}

QTextDocument *FormEditor::document()
{
    return ui->textEdit->document();
}

void FormEditor::copy()
{
    ui->textEdit->copy();
}

void FormEditor::insertPlainText(QString text)
{
    ui->textEdit->insertPlainText(text);
}

void FormEditor::retranslate()
{
    ui->retranslateUi(this);
}

void FormEditor::zoomIn()
{
    ui->textEdit->zoomIn();
}

void FormEditor::zoomOut()
{
    ui->textEdit->zoomOut();
}

bool FormEditor::find(QString text, QTextDocument::FindFlags flag)
{
     return ui->textEdit->find( text,flag);
}

FormEditor::~FormEditor()
{
    delete ui;
}
void FormEditor::GenericInsert(QToolButton*w,QString token,QString label1, QString label2 )
{
    QString selected=ui->textEdit->textCursor().selectedText();
    if (! selected.isEmpty())
    {
        ui->textEdit->textCursor().removeSelectedText();
        ui->textEdit->insertPlainText(QString(token).arg(selected));
    }
    else
    {
        QString val;
        val=QInputDialog::getText(w,label1,label2);
        if ( !val.isEmpty() )
        {
            ui->textEdit->insertPlainText(QString(token).arg(val));
        }
    }

}




void FormEditor::InsertT()
{
    GenericInsert(ui->toolButtonT,ui->checkBoxLongShort->isChecked()?QString("{title:%1}"):QString("{t:%1}"),QObject::tr("Enter title"),QObject::tr("Title"));
}

void FormEditor::InsertST()
{
    GenericInsert(ui->toolButtonST,ui->checkBoxLongShort->isChecked()?QString("{subtitle:%1}"):QString("{st:%1}"),QObject::tr("Enter sub title"),QObject::tr("Sub Title"));
}

void FormEditor::InsertAlbum()
{
    GenericInsert(ui->toolButtonAlbum,QString("{album:%1}"),QObject::tr("Enter album"),QObject::tr("Album"));
}

void FormEditor::InsertArtist()
{
    GenericInsert(ui->toolButtonArtist,QString("{artist:%1}"),QObject::tr("Enter artist"),QObject::tr("Artist"));
}

void FormEditor::InsertComposer()
{
    GenericInsert(ui->toolButtonComposer,QString("{composer:%1}"),QObject::tr("Enter composer"),QObject::tr("Composer"));
}

void FormEditor::InsertLyricist()
{
    GenericInsert(ui->toolButtonLyricist,QString("{lyricist:%1}"),QObject::tr("Enter lyricist"),QObject::tr("Lyricist"));
}
void FormEditor::InsertArranger()
{
    GenericInsert(ui->toolButtonArranger,QString("{arranger:%1}"),QObject::tr("Enter arranger"),QObject::tr("Arranger"));
}



void FormEditor::InsertCopyright()
{
    GenericInsert(ui->toolButtonCopyright,QString("{copyright:%1}"),QObject::tr("Enter copyright"),QObject::tr("Copyright"));
}

void FormEditor::InsertYear()
{
    GenericInsert(ui->toolButtonYear,QString("{year:%1}"),QObject::tr("Enter year"),QObject::tr("Year"));
}

void FormEditor::InsertKey()
{
    GenericInsert(ui->toolButtonKey,QString("{key:%1}"),QObject::tr("Enter key"),QObject::tr("Key"));
}

void FormEditor::InsertDuration()
{
    GenericInsert(ui->toolButtonDuration,QString("{duration:%1}"),QObject::tr("Enter duration"),QObject::tr("Duration"));
}

void FormEditor::InsertComment()
{
    GenericInsert(ui->toolButtonComment,ui->checkBoxLongShort->isChecked()?QString("{comment:%1}"):QString("{c:%1}"),QObject::tr("Enter comment"),QObject::tr("Comment"));
}

void FormEditor::InsertCommentItalic()
{
    GenericInsert(ui->toolButtonCommentItalic,ui->checkBoxLongShort->isChecked()?QString("{comment_Italic:%1}"):QString("{ci:%1}"),QObject::tr("Enter comment"),QObject::tr("Comment italic"));
}

void FormEditor::InsertCommentBox()
{
    GenericInsert(ui->toolButtonCommentBox,ui->checkBoxLongShort->isChecked()?QString("{comment_box:%1}"):QString("{ci:%1}"),QObject::tr("Enter comment"),QObject::tr("Comment box"));
}


void FormEditor::InsertCol()
{
    QString token=ui->checkBoxLongShort->isChecked()?QString("{columns:%1}"):QString("{col:%1}");
    int i=QInputDialog::getInt(ui->toolButtonTempo,tr("Enter columns number"),tr("Column number"),1,1,3);
    ui->textEdit->insertPlainText(QString(token).arg(QString("%1").arg(i)));
}



void FormEditor::ReplaceLongShort(  QString a, QString b)
{

    if ( ui->checkBoxLongShort->isChecked())
                 m_buffreplace.replace(a,b,Qt::CaseInsensitive);
             else
                 m_buffreplace.replace(b,a,Qt::CaseInsensitive);

}
    void FormEditor::InsertCompress()
    {
        ui->textEdit->insertPlainText("{compress}");

    }



    void FormEditor::InsertCT()
    {
        GenericInsert(ui->toolButtonCT,ui->checkBoxLongShort->isChecked()?QString("{cover_title:%1}"):QString("{ct:%1}"),QObject::tr("Enter cover title"),QObject::tr("Cover title"));
    }

    void FormEditor::InsertEOC()
    {
        ui->textEdit->insertPlainText(ui->checkBoxLongShort->isChecked()?QString("{end_of_chorus}"):QString("{eoc}"));
    }


    void FormEditor::InsertSOC()
    {
        ui->textEdit->insertPlainText(ui->checkBoxLongShort->isChecked()?QString("{start_of_chorus}"):QString("{soc}"));
    }

    void FormEditor::InsertPageBreak()
    {
        ui->textEdit->insertPlainText(ui->checkBoxLongShort->isChecked()?QString("{new_page}"):QString("{np}"));
    }


    void FormEditor::InsertSOR()
    {
        ui->textEdit->insertPlainText(ui->checkBoxLongShort->isChecked()?QString("{start_of_refrain}"):QString("{sor}"));
    }

    void FormEditor::InsertEOR()
    {
        ui->textEdit->insertPlainText(ui->checkBoxLongShort->isChecked()?QString("{end_of_refrain}"):QString("{eor}"));
    }

    void FormEditor::InsertSOV()
    {
        ui->textEdit->insertPlainText(ui->checkBoxLongShort->isChecked()?QString("{start_of_verse}"):QString("{sov}"));
    }


    void FormEditor::InsertEOV()
    {
        ui->textEdit->insertPlainText(ui->checkBoxLongShort->isChecked()?QString("{end_of_verse}"):QString("{eov}"));
    }

    void FormEditor::InsertSOG()
    {
        ui->textEdit->insertPlainText(QString("{start_of_grid}"));
    }


    void FormEditor::InsertEOG()
    {
        ui->textEdit->insertPlainText(QString("{end_of_grid}"));
    }

    void FormEditor::InsertCB()
    {
       ui->textEdit->insertPlainText(ui->checkBoxLongShort->isChecked()?QString("{column_break}"):QString("{colb}"));
    }

    void FormEditor::InsertTempo()
    {
        int i=QInputDialog::getInt(ui->toolButtonTempo,tr("Enter tempo"),tr("Beats per minute"),120,20,250);
        ui->textEdit->insertPlainText(QString("{tempo:%1}").arg(QString("%1").arg(i)));
    }

    void FormEditor::InsertTime()
    {
        DialogBar time(ui->toolButtonTime);
        time.exec();
        if ( !time.canceled())
        {
            ui->textEdit->insertPlainText(QString("{time:%1}").arg(time.value()));
            ui->textEdit->insertPlainText(QString(QChar(0x2028)));
        }
    }

    void FormEditor::InsertCS()
    {
        GenericInsert(ui->toolButtonCS,ui->checkBoxLongShort->isChecked()?QString("{cover_subtitle:%1}"):QString("{cs:%1}"),QObject::tr("Enter  cover subtitle"),QObject::tr("Cover Subtitle"));
    }



    void FormEditor::ToogleLongShort()
    {
        m_buffreplace=ui->textEdit->toPlainText();
        ReplaceLongShort("{t:","{title:");
        ReplaceLongShort("{st:","{subtitle:" );
        ReplaceLongShort("{ct:","{cover_title:");
        ReplaceLongShort("{cs:","{cover_subtitle:");
        ReplaceLongShort("{col:","{columns:");
        ReplaceLongShort("{colb}","{column_break}");
        ReplaceLongShort("{ns}","{new_Song}");
        ReplaceLongShort("{soc}","{start_of_chorus}");
        ReplaceLongShort("{eoc}","{end_of_chorus}");
        ReplaceLongShort("{sor}","{start_of_refrain}");
        ReplaceLongShort("{eor}","{end_of_refrain}");
        ReplaceLongShort("{sov}","{start_of_verse}");
        ReplaceLongShort("{eov}","{end_of_verse}");
        ReplaceLongShort("{enp}","{new_page}");
        ReplaceLongShort("{c:","{comment:");
        ReplaceLongShort("{ci:","{comment_italic:");
        ReplaceLongShort("{ci:","{comment_italic:");
        ReplaceLongShort("{cb:","{comment_box:");
        ui->textEdit->setText(m_buffreplace);
    }

