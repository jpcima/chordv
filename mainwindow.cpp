#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "dialogabout.h"
#include "dialogconfiguration.h"
#include "dialogchorddefinition.h"
#include "dialogsysteminfo.h"
#include "dialogsearch.h"
#include "dialogreplace.h"

#include "util.h"
#include "processortext.h"
#include "settings.h"
#include "logmessages.h"

#include <QDebug>
#include <QFileDialog>
#include <QSettings>
#include <QFileInfo>
#include <QTranslator>
#include <QProcess>
#include <QInputDialog>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tabWidget->setCurrentIndex(0);
    m_lastmenu= new QMenu(tr("Last Projects"));
    ui->actionLast_Project=ui->menuFile->insertMenu(ui->actionSave_Current_as_Defaut,m_lastmenu);
    setMenuLastProject();
    connect(m_lastmenu,SIGNAL(triggered(QAction*)),this,SLOT(LastProjectOpen(QAction*)));
    connect(ui->checkBoxChordMode,SIGNAL(stateChanged(int)),this,SLOT(setChordMode(int)));
    connect(ui->checkBoxLyricsMode,SIGNAL(stateChanged(int)),this,SLOT(setLyricsMode(int)));
    connect(ui->checkBoxTextMode,SIGNAL(stateChanged(int)),this,SLOT(setTextMode(int)));
    connect(ui->checkBoxMemoryMode,SIGNAL(stateChanged(int)),this,SLOT(setMemoryMode(int)));
    InitProject();
    connect(ui->actionNew_Project,SIGNAL(triggered(bool)),this,SLOT(newProject(bool)));
    connect(ui->actionOpen_Project,SIGNAL(triggered(bool)),this,SLOT(openProject(bool)));
    connect(ui->actionOpen_Song_File,SIGNAL(triggered(bool)),this,SLOT(openChoFile(bool)));
    connect(ui->actionSave,SIGNAL(triggered(bool)),this,SLOT(Save(bool)));
    connect(ui->actionSave_As,SIGNAL(triggered(bool)),this,SLOT(SaveAs(bool)));
    connect(ui->actionQuit,SIGNAL(triggered(bool)),this,SLOT(close()));
    connect(ui->actionPreferences,SIGNAL(triggered(bool)),this,SLOT(Configuration()));
    connect(ui->actionChord_defintion,SIGNAL(triggered(bool)),this,SLOT(ChordDefinition()));
    connect(ui->actionReset_Preference_as_origine,SIGNAL(triggered(bool)),this,SLOT(PreferencesAsOrigine()));
    connect(ui->actionSave_Current_as_Defaut,SIGNAL(triggered(bool)),this,SLOT(CurrentAsDefault()));
    connect(ui->actionSearch,SIGNAL(triggered(bool)),this,SLOT(Search()));
    connect(ui->actionReplace,SIGNAL(triggered(bool)),this,SLOT(Replace()));
    connect (ui->actionSystem_Info,SIGNAL(triggered(bool)),this,SLOT(SystemInfo()));
    connect(ui->pushButtonMakePDF,SIGNAL(clicked(bool)),this,SLOT(ProducePDF()));
    connect(ui->pushButtonMakeAndShowPDF,SIGNAL(clicked(bool)),this,SLOT(ProducePDFAndShow()));
    connect(ui->toolButtonInputFile,SIGNAL(clicked(bool)),this,SLOT(SetInputFile()));
    connect(ui->actionAbout,SIGNAL(triggered()),this,SLOT(About()));
    connect(ui->toolButtonCB,SIGNAL(clicked(bool)),this,SLOT(InsertCB()));
    connect(ui->toolButtonCol,SIGNAL(clicked(bool)),this,SLOT(InsertCol()));
    connect(ui->toolButtonCompress,SIGNAL(clicked(bool)),this,SLOT(InsertCompress()));
    connect(ui->toolButtonCS,SIGNAL(clicked(bool)),this,SLOT(InsertCS()));
    connect(ui->toolButtonCT,SIGNAL(clicked(bool)),this,SLOT(InsertCT()));
    connect(ui->toolButtonEOC,SIGNAL(clicked(bool)),this,SLOT(InsertEOC()));
    connect(ui->toolButtonREF,SIGNAL(clicked(bool)),this,SLOT(InsertRef()));
    connect(ui->toolButtonSOC,SIGNAL(clicked(bool)),this,SLOT(InsertSOC()));
    connect(ui->toolButtonST,SIGNAL(clicked(bool)),this,SLOT(InsertST()));
    connect(ui->toolButtonT,SIGNAL(clicked(bool)),this,SLOT(InsertT()));
    connect(ui->checkBoxLongShort,SIGNAL(clicked(bool)),this,SLOT(ToogleLongShort()));

    QString file=getFileInArg();
    if ( ! file.isEmpty() )
    {
        QFileInfo fi(file) ;
        if ( ! fi.exists())
        {
            qInfo()<<tr("%1 does'nt exit. Bye !") ;
            exit(1);
        }
        openProject(file);
    }
    if ( testMode())
    {
        ProducePDF();
        exit(0);
    }

  }

 QString MainWindow::getFileInArg()
{
    QStringList list=qApp->arguments();
    if ( list.empty()) return ("");
    list.removeFirst();
    foreach ( QString arg,list )
    {
        if ( ! arg.startsWith("-")) return arg;
    }
    return ("");
}

bool MainWindow::testMode()
{
    foreach ( QString arg, qApp->arguments() )
    {
        if (  arg== "-t" || arg =="--test" ) return true;
    }
    return false;
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
   QString file=QFileDialog::getOpenFileName(this,tr("Open text file"),Util::getLastDirectory(),tr("cho3 file(*.cho3)"));
   ui->lineEditInputFile->setText(file);
   Util::setLastDirectory(file);
   openChoFile(file);

}

void MainWindow::SetInputFile()
{
    QSettings s;
    QString file=QFileDialog::getOpenFileName(this,tr("Open text file"),Util::getLastDirectory(),tr("cho3 file(*.cho3)"));
    ui->lineEditInputFile->setText(getRelativeFilename(file));
    openChoFile(file);
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
    ui->lineEditCreatorName->setText(s.value("Creator","").toString());
    ui->lineEditInputFile->setText(s.value("File","").toString());
    ui->lineEditWatermark->setText(s.value("Watermark","").toString());
    ui->checkBoxChordMode->setChecked(s.value("ChordMode",true).toBool());
    ui->checkBoxLyricsMode->setChecked(s.value("LyricsMode",true).toBool());
    ui->checkBoxTextMode->setChecked(s.value("TextMode",true).toBool());
    ui->checkBoxMemoryMode->setChecked(s.value("MemoryMode",true).toBool());
    QString file=getFileInArg();
    if ( file.isEmpty())
    {
        m_currentprojectdir=s.value("LastOpenedDirectory","").toString();
        m_currentprojectname="";
        m_currentprojectfile="" ;
    }
    else
    {
        QFileInfo fi(file);
        m_currentprojectdir= fi.absolutePath();
        m_currentprojectname=fi.baseName();
        m_currentprojectfile=file;
    }
    ui->labelNameDirProject->setText(m_currentprojectdir);
    ui->labelNameProjectName->setText(m_currentprojectname);
    openChoFile(m_currentprojectfile);
}



void MainWindow::openChoFile( QString filename)
{
    QSettings s;
    QFile file(filename);
    ui->textEditCho3File->clear();
    ui->pushButtonMakePDF->setDisabled(true);
    if ( ! s.value("PDFReader").isNull() ) ui->pushButtonMakeAndShowPDF->setDisabled(true);
    if ( filename.isEmpty()) return;
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) ui->log->Error(QString(tr("Cannot open file : %1").arg(filename)));
    else
    {
        ui->pushButtonMakePDF->setDisabled(false);
        ui->pushButtonMakeAndShowPDF->setDisabled(false);
        QTextStream in(&file);
        ui->textEditCho3File->append(in.readAll());
        QTextCursor textCursor = ui->textEditCho3File->textCursor();
        textCursor.movePosition(QTextCursor::Start, QTextCursor::MoveAnchor);
        ui->textEditCho3File->setTextCursor(textCursor);
        m_editorhighlight = new EditorHighlighter(ui->textEditCho3File->document());
        ui->checkBoxLongShort->setChecked(ui->textEditCho3File->document()->toPlainText().contains("{covertitle:",Qt::CaseInsensitive));
    }
}

void MainWindow::openProject(QString filename)
{

    ui->log->clear();
    QFileInfo fi(filename);
    m_currentprojectname=fi.baseName();
    m_currentprojectdir=fi.absolutePath();
    QDir::setCurrent(m_currentprojectdir);
    m_currentprojectfile=filename;
    ui->labelNameProjectName->setText(m_currentprojectname);
    ui->labelNameDirProject->setText(m_currentprojectdir);
    QSettings p(filename,QSettings::IniFormat);
    ui->lineEditInputFile->setText(p.value("File").toString());
    ui->lineEditCreatorName->setText(p.value("Creator").toString());
    ui->comboBoxChordLanguage->setCurrentIndex(p.value("ChordLang").toInt());
    ui->lineEditWatermark->setText(p.value("Watermark").toString());
    ui->checkBoxChordMode->setChecked(p.value("ChordMode").toBool());
    ui->checkBoxLyricsMode->setChecked(p.value("LyricsMode").toBool());
    ui->checkBoxMemoryMode->setChecked(p.value("MemoryMode").toBool());
    ui->checkBoxTextMode->setChecked(p.value("TextMode").toBool());
    ui->widgetChordMode->SetConfigFromFile(filename);
    ui->widgetChordMode->InitDefault(FormConfig::Chord);
    ui->widgetLyricsMode->SetConfigFromFile(filename);
    ui->widgetLyricsMode->InitDefault(FormConfig::Lyrics);
    ui->widgetMemoryMode->SetConfigFromFile(filename);
    ui->widgetMemoryMode->InitDefault(FormConfig::Memory);
    ui->widgetTextMode->SetConfigFromFile(filename);
    ui->widgetTextMode->InitDefault(FormConfig::Text);
    openChoFile(m_currentprojectdir+"/"+ui->lineEditInputFile->text());
}

void MainWindow::openProject ( bool)

{
   QSettings s;
   QString filename=QFileDialog::getOpenFileName(this,tr("Open conf file"),Util::getLastDirectory(),"*.chop");
   openProject(filename);
   Util::setLastDirectory(filename);
   Util::MemorizeProject(filename);
   setMenuLastProject();
}



void MainWindow::Save(QString filename)
{
    ui->log->clear();
    if ( ! filename.endsWith(".chop") && !filename.endsWith(".conf")) filename+=".chop";
    QSettings sf(filename,QSettings::IniFormat);
    sf.clear();
    sf.setValue("Creator",ui->lineEditCreatorName->text());
    sf.setValue("File",ui->lineEditInputFile->text());
    sf.setValue("ChordLang",ui->comboBoxChordLanguage->currentIndex());
    sf.setValue("LyricsMode",ui->checkBoxLyricsMode->isChecked());
    sf.setValue("TextMode",ui->checkBoxTextMode->isChecked());
    sf.setValue("MemoryMode",ui->checkBoxMemoryMode->isChecked());
    sf.setValue("ChordMode",ui->checkBoxChordMode->isChecked());
    sf.sync();
    ui->widgetChordMode->Save(filename,FormConfig::Chord);
    ui->widgetLyricsMode->Save(filename,FormConfig::Lyrics);
    ui->widgetTextMode->Save(filename,FormConfig::Text);
    ui->widgetMemoryMode->Save(filename,FormConfig::Memory);
    if ( SaveCho3(ui->lineEditInputFile->text()) )
        ui->log->Info(tr("File saved : %1").arg(filename));
    else
        ui->log->Info(tr("File not well saved : %1").arg(filename));
}

QString MainWindow::getRelativeFilename( QString chofilename )
{
    QDir dir (m_currentprojectdir);
    QString d=dir.relativeFilePath(chofilename);
    return d;
}

void MainWindow::Save(bool)
{
    ui->log->clear();
    QSettings s;
    if ( m_currentprojectname.isEmpty())
        SaveAs(true);
    else m_currentprojectfile=m_currentprojectdir+"/"+m_currentprojectname+".chop";
    QSettings sf(m_currentprojectfile,QSettings::IniFormat);
    sf.clear();
    sf.setValue("Creator",ui->lineEditCreatorName->text());
    sf.setValue("File",ui->lineEditInputFile->text());
    sf.setValue("ChordMode",ui->checkBoxChordMode->isChecked());
    sf.setValue("LyricsMode",ui->checkBoxLyricsMode->isChecked());
    sf.setValue("TextMode",ui->checkBoxTextMode->isChecked());
    sf.setValue("MemoryMode",ui->checkBoxMemoryMode->isChecked());
    sf.sync();
    ui->widgetChordMode->Save(m_currentprojectfile,FormConfig::Chord);
    ui->widgetLyricsMode->Save(m_currentprojectfile,FormConfig::Lyrics);
    ui->widgetTextMode->Save(m_currentprojectfile,FormConfig::Text);
    ui->widgetMemoryMode->Save(m_currentprojectfile,FormConfig::Memory);
    if ( SaveCho3(ui->lineEditInputFile->text()) )
        ui->log->Info(tr("File saved : %1").arg(m_currentprojectfile));
    else
        ui->log->Info(tr("File not well saved : %1").arg(m_currentprojectfile));
}


void MainWindow::SaveAs(bool)
{
    QSettings s;
    m_currentprojectfile=QFileDialog::getSaveFileName(this,tr("Save project as"),Util::getLastDirectory(),tr("Save as (*.chop)"));
    if (!m_currentprojectfile.isEmpty() )
    {
        Save(true);
        Util::setLastDirectory(m_currentprojectfile);
    }
}

void MainWindow::ActualizeProject( QString )
{

}

void MainWindow::ProducePDF()
{
 //Save(true);
  if (ui->checkBoxTextMode->isChecked())
  {
      ProcessorText *p;
      p= new ProcessorText(ui,ui->widgetTextMode->getUi());
      connect(p,SIGNAL(PDFMade(QString)),this, SLOT(ConversionDone(QString)));
      p->run() ;
      p->deleteLater();
  }
}


void MainWindow::ConversionDone( QString filename)
{
    m_pdffilename=filename;
    Info(tr("Conversion done for : %1").arg(filename));
}

void MainWindow::ProducePDFAndShow()
{
   ProducePDF();
   QSettings s;
   QProcess *myprocess = new QProcess(this);
   QStringList arg;
   arg<<m_pdffilename;
   myprocess->start(s.value("PDFReader").toString(),arg);

}

void MainWindow::Info(QString info)
{
    ui->log->Info(info);
}


void MainWindow::About()
{
  DialogAbout *d = new DialogAbout(this) ;
  d->exec();
}


void MainWindow::PDFReaderChanged()
{
    QSettings s;
    ui->pushButtonMakeAndShowPDF->setEnabled( ! ui->textEditCho3File->toPlainText().isNull() && ! s.value("PDFReader").isNull());
}

void MainWindow::Configuration()
{
    DialogConfiguration * dial = new DialogConfiguration(this);
    connect ( dial,SIGNAL(LanguageChanged(int)),this,SLOT(ChangeLanguage(int)));
    connect ( dial,SIGNAL(PdfReaderChanged()),this,SLOT(PDFReaderChanged()));
    dial->exec();
    delete dial;
}


void MainWindow::ChordDefinition()
{
    DialogChordDefinition * dial = new DialogChordDefinition(this);
    connect (dial,SIGNAL(Error(QString)),this,SLOT(Log(QString)));
    dial->exec();
    delete dial;
}

void MainWindow::ChangeLanguage(int)
{
    ui->retranslateUi(this);
    ui->widgetChordMode->Retranslate();
    ui->widgetLyricsMode->Retranslate();
    ui->widgetMemoryMode->Retranslate();
    ui->widgetTextMode->Retranslate();
}


bool MainWindow::SaveCho3(QString filename)
{
    QString f(m_currentprojectdir+"/"+filename);
    QFile file( f);
   if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
   {
       ui->log->Error(QString("Cannot write file : %1").arg(f));
       return false;
   }
    QTextStream out(&file);
    out << ui->textEditCho3File->document()->toPlainText();
    file.close();
    return true;
}

void MainWindow::GenericInsert(QToolButton*w,QString token,QString label1, QString label2 )
{
    QString selected=ui->textEditCho3File->textCursor().selectedText();
    if (! selected.isEmpty())
    {
        ui->textEditCho3File->textCursor().removeSelectedText();
        ui->textEditCho3File->insertPlainText(QString(token).arg(selected));
    }
    else
    {
        QString val=QInputDialog::getText(w,label1,label2);
        if ( !val.isEmpty() )ui->textEditCho3File->insertPlainText(QString(token).arg(val));
    }

}


void MainWindow::InsertT()
{
    GenericInsert(ui->toolButtonT,ui->checkBoxLongShort->isChecked()?QString("{Title:%1}"):QString("{t:%1}"),QObject::tr("Enter title"),QObject::tr("Title"));
}

void MainWindow::InsertST()
{
    GenericInsert(ui->toolButtonST,ui->checkBoxLongShort->isChecked()?QString("{SubTitle:%1}"):QString("{st:%1}"),QObject::tr("Enter sub title"),QObject::tr("Sub Title"));
}

void MainWindow::InsertCB()
{
    ui->textEditCho3File->insertPlainText(ui->checkBoxLongShort->isChecked()?QString("{column_break}"):QString("{colb}"));
}

void MainWindow::InsertCol()
{
    GenericInsert(ui->toolButtonCol,ui->checkBoxLongShort->isChecked()?QString("{Columns:%1}"):QString("{col:%1}"),QObject::tr("Enter columns number"),QObject::tr("Column number"));
}

void MainWindow::InsertCompress()
{
    ui->textEditCho3File->insertPlainText("{compress}");

}

void MainWindow::InsertCS()
{
    GenericInsert(ui->toolButtonCS,ui->checkBoxLongShort->isChecked()?QString("{Cover subtitle:%1}"):QString("{cs:%1}"),QObject::tr("Enter  cover subtitle"),QObject::tr("Cover Subtitle"));
}

void MainWindow::InsertCT()
{
    GenericInsert(ui->toolButtonCT,ui->checkBoxLongShort->isChecked()?QString("{Cover title:%1}"):QString("{ct:%1}"),QObject::tr("Enter cover title"),QObject::tr("Cover title"));
}

void MainWindow::InsertEOC()
{
    ui->textEditCho3File->insertPlainText(ui->checkBoxLongShort->isChecked()?QString("{end_of_chorus}"):QString("{eoc}"));
}


void MainWindow::InsertSOC()
{
    ui->textEditCho3File->insertPlainText(ui->checkBoxLongShort->isChecked()?QString("{start_of_chorus}"):QString("{soc}"));
}


void MainWindow::InsertRef()
{
    ui->textEditCho3File->insertPlainText("Refrain:");
}

void MainWindow::ReplaceLongShort(  QString a, QString b)
{

    if ( ui->checkBoxLongShort->isChecked())
        m_buffreplace.replace(a,b,Qt::CaseInsensitive);
    else
        m_buffreplace.replace(b,a,Qt::CaseInsensitive);

}

void MainWindow::ToogleLongShort()
{

    m_buffreplace=ui->textEditCho3File->toPlainText();
    ReplaceLongShort("{t:","{Title:");
    ReplaceLongShort("{st:","{SubTitle:" );
    ReplaceLongShort("{ct:","{CoverTitle:");
    ReplaceLongShort("{cs:","{CoverSubTitle:");
    ReplaceLongShort("{col:","{Columns:");
    ReplaceLongShort("{colb}","{Column_break}");
    ReplaceLongShort("{ns}","{New_Song}");
    ReplaceLongShort("{soc}","start_of_chorus");
    ReplaceLongShort("{eoc}","end_of_chorus");

    ui->textEditCho3File->setText(m_buffreplace);
}


void MainWindow::SystemInfo()
{
    DialogSystemInfo dial(this);
    dial.exec();
}


void MainWindow::Search()
{
  ui->textEditCho3File->copy();
  DialogSearch * dial = new DialogSearch(this);
  connect (dial,SIGNAL(Search(QString,bool,bool)),this,SLOT(Search(QString,bool,bool)));
  connect (dial,SIGNAL(SearchBack(QString,bool,bool)),this,SLOT(SearchBack(QString,bool,bool)));
  dial->show();
}


void MainWindow::Replace()
{
 ui->textEditCho3File->copy();
 DialogReplace *dial = new DialogReplace(this);
 connect (dial,SIGNAL(Search(QString,bool,bool)),this,SLOT(Search(QString,bool,bool)));
 connect (dial,SIGNAL(SearchBack(QString,bool,bool)),this,SLOT(SearchBack(QString,bool,bool)));
 connect (dial,SIGNAL(Replace(QString,QString,bool,bool,bool,bool)),this,SLOT(Replace(QString,QString,bool,bool,bool,bool)));
 dial->show();
}


void MainWindow::Search(QString text, bool casesensitive, bool wordonly )
{
    ui->tabWidget->setCurrentIndex(5);
    QFlags<QTextDocument::FindFlag> flag;
    if (casesensitive ) flag =QTextDocument::FindCaseSensitively;
    if (wordonly) flag|=QTextDocument::FindWholeWords;
    ui->textEditCho3File->find(text,flag);
}

void MainWindow::SearchBack(QString text, bool casesensitive, bool wordonly )
{
    ui->tabWidget->setCurrentIndex(5);
    QFlags<QTextDocument::FindFlag> flag= QTextDocument::FindBackward;
    if (casesensitive ) flag |=QTextDocument::FindCaseSensitively;
    if (wordonly) flag|=QTextDocument::FindWholeWords;
    ui->textEditCho3File->find(text,flag);
}

void MainWindow::Replace ( QString textfrom, QString textto,bool all, bool casesensitive, bool wordonly, bool back)
{
    ui->tabWidget->setCurrentIndex(5);
    ui->textEditCho3File->textCursor().clearSelection();
    ui->textEditCho3File->insertPlainText(textto);
    if ( back ) SearchBack(textfrom,casesensitive,wordonly);
    else Search(textfrom,casesensitive,wordonly);
}
