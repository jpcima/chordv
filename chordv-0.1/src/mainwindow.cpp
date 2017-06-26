#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "dialogabout.h"
#include "dialogconfiguration.h"
#include "dialogchorddefinition.h"
#include "dialogsysteminfo.h"
#include "dialogsearch.h"
#include "dialogreplace.h"
#include "dialogbar.h"
#include "dialogdocumentation.h"
#include "dialogtwolinestochordpro.h"
#include "dialogchangechordname.h"

#include "lyricsconfig.h"
#include "formconfig.h"
#include "textconfig.h"
#include "memoryconfig.h"
#include "formconfig.h"
#include "chord.h"

#include "chordutil.h"
#include "processortext.h"
#include "processorlyrics.h"
#include "processorchord.h"
#include "settings.h"
#include "logmessages.h"
#include "language.h"
#include "pdfviewer.h"

#include <QDebug>
#include <QFileDialog>
#include <QSettings>
#include <QFileInfo>
#include <QTranslator>
#include <QProcess>
#include <QInputDialog>
#include <QShortcut>
#include "ui_formconfig.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QSettings s;
    QList <int> size;
    size<<700<<100;
    m_labelactivestacked= new QLabel(this);
    ui->statusBar->addWidget(m_labelactivestacked);
    m_liststacked<<tr("Editor")<<tr("Global definitions")<<tr("Text and chord Mode")<<tr("Chord Mode")<<tr("Text mode")<<tr("Memory Mode");
    ShowStacked(0);
    ui->splitter->setSizes(size);
    ui->actionSelectEditor->setChecked(true);
    Language::setLanguageComboBox( ui->comboBoxChordLanguage);
    ui->comboBoxMinorNotation->addItems(Language::ListMinor(s.value("InterfaceLanguage").toString()));
    ui->stackedWidget->setCurrentIndex(0);
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
    connect(ui->actionExport_tho_cho3_file,SIGNAL(triggered(bool)),this,SLOT(ExportCho3File()));
    connect(ui->actionSave,SIGNAL(triggered(bool)),this,SLOT(Save(bool)));
    connect(ui->actionSave_As,SIGNAL(triggered(bool)),this,SLOT(SaveAs(bool)));
    connect(ui->actionQuit,SIGNAL(triggered(bool)),this,SLOT(close()));
    connect(ui->actionPreferences,SIGNAL(triggered(bool)),this,SLOT(Configuration()));
    connect(ui->actionChord_defintion,SIGNAL(triggered(bool)),this,SLOT(ChordDefinition()));
    connect(ui->actionReset_Preferences_as_Origin,SIGNAL(triggered(bool)),this,SLOT(PreferencesAsOrigine()));
    connect(ui->actionSave_Current_as_Defaut,SIGNAL(triggered(bool)),this,SLOT(CurrentAsDefault()));
    connect(ui->actionSearch,SIGNAL(triggered(bool)),this,SLOT(Search()));
    connect (ui->actionZoomIn,SIGNAL(triggered(bool)),this,SLOT(ZoomIn()));
    connect (ui->actionZoomOut,SIGNAL(triggered(bool)),this,SLOT(ZoomOut()));
    connect(ui->actionReplace,SIGNAL(triggered(bool)),this,SLOT(Replace()));
    connect (ui->actionSystem_Info,SIGNAL(triggered(bool)),this,SLOT(SystemInfo()));
    connect(ui->pushButtonMakePDF,SIGNAL(clicked(bool)),this,SLOT(ProducePDF()));
    connect(ui->pushButtonMakeAndShowPDF,SIGNAL(clicked(bool)),this,SLOT(ProducePDFAndShow()));
    connect(ui->actionAbout,SIGNAL(triggered()),this,SLOT(About()));
    connect(ui->action2Line2chordpro,SIGNAL(triggered(bool)),this,SLOT(TwoLines2Chordpro()));
    connect(ui->actionChangeChordLang,SIGNAL(triggered(bool)),this,SLOT(ChangeChordLang()));
    connect (ui->actionSelectDefinition,SIGNAL(triggered(bool)),this,SLOT(ShowDefinition()));
    connect (ui->actionSelectMemory,SIGNAL(triggered(bool)),this,SLOT(ShowMemoryMode()));
    connect (ui->actionSelectText,SIGNAL(triggered(bool)),this,SLOT(ShowTextMode()));
    connect (ui->actionSelectLyrics,SIGNAL(triggered(bool)),this,SLOT(ShowLyricsMode()));
    connect (ui->actionSelectChord,SIGNAL(triggered(bool)),this,SLOT(ShowChordMode()));
    connect(ui->actionSelectEditor,SIGNAL(triggered(bool)),this,SLOT(ShowEditor()));
    connect (ui->actionBuildText,SIGNAL(triggered(bool)),this,SLOT(BuildTextPdf()));
    connect (ui->actionBuildLyrics,SIGNAL(triggered(bool)),this,SLOT(BuildLyricsPdf()));
    connect (ui->actionBuildChord,SIGNAL(triggered(bool)),this,SLOT(BuildChordPdf()));
    connect (ui->actionBuildMemory,SIGNAL(triggered(bool)),this,SLOT(BuildMemoryPdf()));
    connect (ui->actionViewText,SIGNAL(triggered(bool)),this,SLOT(ViewTextPdf()));
    connect (ui->actionViewLyrics,SIGNAL(triggered(bool)),this,SLOT(ViewLyricsPdf()));
    connect (ui->actionViewChord,SIGNAL(triggered(bool)),this,SLOT(ViewChordPdf()));
    connect (ui->actionViewMemory,SIGNAL(triggered(bool)),this,SLOT(ViewMemoryPdf()));
    connect (ui->actionViewLastbuilt,SIGNAL(triggered(bool)),this,SLOT(ViewLastBuildPdf()));
    connect (ui->actionBuildAndViewText,SIGNAL(triggered(bool)),this,SLOT(BuildAndViewText()));
    connect (ui->actionBuildAndViewLyrics,SIGNAL(triggered(bool)),this,SLOT(BuildAndViewLyrics()));
    connect (ui->actionBuildAndViewChord,SIGNAL(triggered(bool)),this,SLOT(BuildAndViewChord()));
    connect (ui->actionBuildAndViewMemory,SIGNAL(triggered(bool)),this,SLOT(BuildAndViewMemory()));
    connect (ui->actionViewLastbuilt,SIGNAL(triggered(bool)),this,SLOT(ViewLastBuildPdf()));
    connect (ui->actionDocumentation,SIGNAL(triggered(bool)),this,SLOT(Documentation()));
    connect(ui->stackedWidget,SIGNAL(currentChanged(int)),this,SLOT(ShowStacked(int)));


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
    else
        if ( ! s.value("LastOpenedFile","").toString().isEmpty() && s.value("OpenLastFileOnStart","").toBool() )
        {
            openProject(s.value("LastOpenedFile","").toString());
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
   QString file=QFileDialog::getOpenFileName(this,tr("Open text file"),ChordUtil::getLastDirectory(),tr("cho3 file(*.cho3)"));
   ChordUtil::setLastDirectory(file);
   openChoFile(file);

}

void MainWindow::setMenuLastProject()
{
    m_lastmenu->clear();
    foreach ( QString l, ChordUtil::LastProjects())
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
    ui->actionSelectChord->setEnabled(i!=0);
    ui->actionBuildChord->setEnabled(i!=0);
    ui->actionViewChord->setEnabled(i!=0);
    ui->actionBuildAndViewChord->setEnabled(i!=0);
}

void MainWindow::setTextMode(int i)
{
    ui->actionSelectText->setEnabled(i!=0);
    ui->actionBuildText->setEnabled(i!=0);
    ui->actionViewText->setEnabled(i!=0);
    ui->actionBuildAndViewText->setEnabled(i!=0);

}

void MainWindow::setMemoryMode(int i)
{
    ui->actionSelectMemory->setEnabled(i!=0);
    ui->actionBuildMemory->setEnabled(i!=0);
    ui->actionViewMemory->setEnabled(i!=0);
    ui->actionBuildAndViewMemory->setEnabled(i!=0);
}

void MainWindow::setLyricsMode(int i)
{
    ui->actionSelectLyrics->setEnabled(i!=0);
    ui->actionBuildLyrics->setEnabled(i!=0);
    ui->actionViewLyrics->setEnabled(i!=0);
    ui->actionBuildAndViewLyrics->setEnabled(i!=0);

}

void MainWindow::Log(QString message)
{
    ui->log->Error(message);
}

void MainWindow::Info(QString info)
{
    ui->log->Info(info);
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
        //m_editorhighlight = new EditorHighlighter(ui->textEditCho3File->document());
        //

    }
}

void MainWindow::openProject(QString filename)
{
    QSettings s;
    ui->log->clear();
    QFileInfo fi(filename);
    m_currentprojectname=fi.baseName();
    m_currentprojectdir=fi.absolutePath();
    s.setValue("LastOpenedFile",filename);
    QDir::setCurrent(m_currentprojectdir);
    m_currentprojectfile=filename;
    ui->labelNameProjectName->setText(m_currentprojectname);
    ui->labelNameDirProject->setText(m_currentprojectdir);
    QSettings p(filename,QSettings::IniFormat);
    ui->lineEditCreatorName->setText(p.value("Creator").toString());
    ui->comboBoxChordLanguage->setCurrentIndex(p.value("ChordLang").toInt());
    ui->comboBoxMinorNotation->setCurrentText(p.value("ChordMinor").toString());
    ui->lineEditWatermark->setText(p.value("Watermark").toString());
    ui->checkBoxChordMode->setChecked(p.value("ChordMode").toBool());
    ui->checkBoxLyricsMode->setChecked(p.value("LyricsMode").toBool());
    ui->checkBoxMemoryMode->setChecked(p.value("MemoryMode").toBool());
    ui->checkBoxTextMode->setChecked(p.value("TextMode").toBool());
    ui->widgetChordMode->SetConfigFromFile(filename);
    ui->widgetChordMode->InitDefault(FormConfig::Chord);
    ui->widgetChordMode->setProjectPath(m_currentprojectdir);
    ui->widgetLyricsMode->SetConfigFromFile(filename);
    ui->widgetLyricsMode->InitDefault(FormConfig::Lyrics);
    ui->widgetLyricsMode->setProjectPath(m_currentprojectdir);
    ui->widgetMemoryMode->SetConfigFromFile(filename);
    ui->widgetMemoryMode->InitDefault(FormConfig::Memory);
    ui->widgetMemoryMode->setProjectPath(m_currentprojectdir);
    ui->widgetTextMode->SetConfigFromFile(filename);
    ui->widgetTextMode->InitDefault(FormConfig::Text);
    ui->widgetTextMode->setProjectPath(m_currentprojectdir);
    ui->textEditCho3File->setText(p.value("Content").toString());
    //ui->checkBoxLongShort->setChecked(ui->textEditCho3File->document()->toPlainText().contains("{covertitle:",Qt::CaseInsensitive));

}

void MainWindow::openProject ( bool)

{
   QSettings s;
   QString filename=QFileDialog::getOpenFileName(this,tr("Open conf file"),ChordUtil::getLastDirectory(),"*.chop");
   openProject(filename);
   ChordUtil::setLastDirectory(filename);
   ChordUtil::MemorizeProject(filename);
   setMenuLastProject();
}

void MainWindow::ZoomIn()
{
    ui->textEditCho3File->zoomIn();
}

void MainWindow::ZoomOut()
{
    ui->textEditCho3File->zoomOut();
}
void MainWindow::Save(QString filename)
{
    ui->log->clear();
    if ( ! filename.endsWith(".chop") && !filename.endsWith(".conf")) filename+=".chop";
    QSettings sf(filename,QSettings::IniFormat);
    sf.clear();
    sf.setValue("Creator",ui->lineEditCreatorName->text());
    sf.setValue("ChordLang",ui->comboBoxChordLanguage->currentIndex());
    sf.setValue("ChordMinor",ui->comboBoxMinorNotation->currentText());
    sf.setValue("LyricsMode",ui->checkBoxLyricsMode->isChecked());
    sf.setValue("TextMode",ui->checkBoxTextMode->isChecked());
    sf.setValue("MemoryMode",ui->checkBoxMemoryMode->isChecked());
    sf.setValue("ChordMode",ui->checkBoxChordMode->isChecked());
    sf.sync();
    ui->widgetChordMode->Save(filename,FormConfig::Chord);
    ui->widgetLyricsMode->Save(filename,FormConfig::Lyrics);
    ui->widgetTextMode->Save(filename,FormConfig::Text);
    ui->widgetMemoryMode->Save(filename,FormConfig::Memory);
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
    sf.setValue("ChordMode",ui->checkBoxChordMode->isChecked());
    sf.setValue("LyricsMode",ui->checkBoxLyricsMode->isChecked());
    sf.setValue("TextMode",ui->checkBoxTextMode->isChecked());
    sf.setValue("MemoryMode",ui->checkBoxMemoryMode->isChecked());
    sf.setValue("ChordLang",ui->comboBoxChordLanguage->currentIndex());
    sf.setValue("ChordMinor",ui->comboBoxMinorNotation->currentText());
    sf.setValue("Content",ui->textEditCho3File->document()->toPlainText());
    sf.sync();
    ui->widgetChordMode->Save(m_currentprojectfile,FormConfig::Chord);
    ui->widgetLyricsMode->Save(m_currentprojectfile,FormConfig::Lyrics);
    ui->widgetTextMode->Save(m_currentprojectfile,FormConfig::Text);
    ui->widgetMemoryMode->Save(m_currentprojectfile,FormConfig::Memory);

}


void MainWindow::SaveAs(bool)
{
    m_currentprojectfile=QFileDialog::getSaveFileName(this,tr("Save project as"),ChordUtil::getLastDirectory(),tr("(*.chop)"));
    if (!m_currentprojectfile.isEmpty() )
    {
        QFileInfo fi( m_currentprojectfile);
        m_currentprojectname=fi.baseName();
        m_currentprojectdir=fi.absolutePath();
        Save(true);
        ChordUtil::setLastDirectory(m_currentprojectfile);
    }
}

void MainWindow::ActualizeProject( QString )
{

}

void MainWindow::ProducePDF()
{
  if (ui->checkBoxTextMode->isChecked())
  {
     BuildTextPdf();
  }
  if (ui->checkBoxLyricsMode->isChecked())
  {
     BuildLyricsPdf();
  }
  if ( ui->checkBoxChordMode->isChecked())
  {
      BuildChordPdf();
  }
  if ( ui->checkBoxMemoryMode->isChecked())
  {
      BuildMemoryPdf();
  }
}


void MainWindow::ProducePDFAndShow()
{
   ProducePDF();


}


void MainWindow::BuildTextPdf()
{
    ProcessorText *p;
    p= new ProcessorText(ui,ui->widgetTextMode->getUi());
    connect(p,SIGNAL(PDFMade(QString)),this, SLOT(ConversionDone(QString)));
    p->run() ;
    p->deleteLater();
}

void MainWindow::BuildLyricsPdf()
{
    ProcessorLyrics *p;
    p= new ProcessorLyrics(ui,ui->widgetLyricsMode->getUi());
    connect(p,SIGNAL(PDFMade(QString)),this, SLOT(ConversionDone(QString)));
    p->run() ;
    p->deleteLater();
}

void MainWindow::BuildChordPdf()
{
    ProcessorChord *p;
    p = new ProcessorChord(ui,ui->widgetChordMode->getUi());
    connect(p,SIGNAL(PDFMade(QString)),this, SLOT(ConversionDone(QString)));
    p->run();
    p->deleteLater();
}

void MainWindow::BuildMemoryPdf()
{

}


QString MainWindow::getPdfFileName(QString text )
{
   QString project=m_currentprojectfile;
   return  project.replace(QRegExp("\\.chop"),QString("_%1.pdf").arg(text));
}

void MainWindow::ViewTextPdf()
{   
    PdfViewer viewer(getPdfFileName(ui->widgetTextMode->getUi()->lineEditOutFile->text()),this);
    if ( ! viewer.getStatus())  Log(viewer.getStatusError());
    else Info(viewer.getStatusInfo());
}


void MainWindow::ViewLyricsPdf()
{
    PdfViewer viewer(getPdfFileName(ui->widgetLyricsMode->getUi()->lineEditOutFile->text()),this);
    if ( ! viewer.getStatus())  Log(viewer.getStatusError());
    else Info(viewer.getStatusInfo());
}

void MainWindow::ViewChordPdf()
{
    PdfViewer viewer(getPdfFileName(ui->widgetChordMode->getUi()->lineEditOutFile->text()),this);
    if ( ! viewer.getStatus())  Log(viewer.getStatusError());
    else Info(viewer.getStatusInfo());
}

void MainWindow::ViewMemoryPdf()
{

}

void MainWindow::ViewLastBuildPdf()
{
    PdfViewer viewer(m_pdffilename,this);
    if ( ! viewer.getStatus())  Log(viewer.getStatusError());
    else Info(viewer.getStatusInfo());
}


void MainWindow::BuildAndViewText()
{
   BuildTextPdf();
   ViewTextPdf();
}

void MainWindow::BuildAndViewLyrics()
{
   BuildLyricsPdf();
   ViewLyricsPdf();
}

void MainWindow::BuildAndViewChord()
{
   BuildChordPdf();
   ViewChordPdf();
}

void MainWindow::BuildAndViewMemory()
{
   BuildMemoryPdf();
   ViewMemoryPdf();
}

void MainWindow::ConversionDone( QString filename)
{
    m_pdffilename=filename;
    Info(tr("Conversion done for : %1").arg(filename));
}




void MainWindow::About()
{
  DialogAbout *d = new DialogAbout(this) ;
  d->exec();
}


void MainWindow::PDFReaderChanged()
{
    QSettings s;
   // ui->pushButtonMakeAndShowPDF->setEnabled( ! ui->textEditCho3File->toPlainText().isNull() && ! s.value("PDFReader").isNull());
}

void MainWindow::Configuration()
{
    DialogConfiguration * dial = new DialogConfiguration(this);
    dial->setTranslator(m_translator);
    connect ( dial,SIGNAL(LanguageChanged(QString)),this,SLOT(ChangeLanguage(QString)));
    connect ( dial,SIGNAL(PdfReaderChanged()),this,SLOT(PDFReaderChanged()));
    dial->exec();
    delete dial;
}


void MainWindow::ChordDefinition()
{
    DialogChordDefinition * dial = new DialogChordDefinition(this);
    dial->SetChordLanguage(ui->comboBoxChordLanguage->currentText(),ui->comboBoxMinorNotation->currentText());
    connect (dial,SIGNAL(Error(QString)),this,SLOT(Log(QString)));
    dial->exec();
    delete dial;
}

void MainWindow::ChangeLanguage(QString )
{
    ui->retranslateUi(this);
    ui->widgetChordMode->Retranslate();
    ui->widgetLyricsMode->Retranslate();
    ui->widgetMemoryMode->Retranslate();
    ui->widgetTextMode->Retranslate();
}



void MainWindow::ExportCho3File()
{
    QString cho3file=m_currentprojectfile;
    cho3file.replace(QRegExp("\\.chop$"),".cho3");
   QFile file( cho3file);
   if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
   {
       ui->log->Error(tr("Cannot write file : %1").arg(cho3file));
       return;
   }
    QTextStream out(&file);
    out << ui->textEditCho3File->document()->toPlainText();
    file.close();
    ui->log->Info(tr("%1 file exported").arg(cho3file));
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
    ui->stackedWidget->setCurrentIndex(0);
    QFlags<QTextDocument::FindFlag> flag;
    if (casesensitive ) flag =QTextDocument::FindCaseSensitively;
    if (wordonly) flag|=QTextDocument::FindWholeWords;
    m_found=ui->textEditCho3File->find(text,flag);
}

void MainWindow::SearchBack(QString text, bool casesensitive, bool wordonly )
{
    ui->stackedWidget->setCurrentIndex(0);
    QFlags<QTextDocument::FindFlag> flag= QTextDocument::FindBackward;
    if (casesensitive ) flag |=QTextDocument::FindCaseSensitively;
    if (wordonly) flag|=QTextDocument::FindWholeWords;
    m_found=ui->textEditCho3File->find(text,flag);
}

void MainWindow::Replace ( QString textfrom, QString textto,bool all, bool casesensitive, bool wordonly, bool back)
{
    if (!m_found ) return;
    ui->stackedWidget->setCurrentIndex(0);
    if ( all )
    {
        while ( m_found )
        {
         ui->textEditCho3File->textCursor().clearSelection();
         ui->textEditCho3File->insertPlainText(textto);
         if ( back ) SearchBack(textfrom,casesensitive,wordonly);
         else Search(textfrom,casesensitive,wordonly);
        }
    }
    else
    {
        ui->textEditCho3File->textCursor().clearSelection();
        ui->textEditCho3File->insertPlainText(textto);
        if ( back ) SearchBack(textfrom,casesensitive,wordonly);
        else Search(textfrom,casesensitive,wordonly);
    }
}

void MainWindow::ShowEditor()
{
    ui->stackedWidget->setCurrentIndex(0);
    setChecked(0);
}

void MainWindow::ShowDefinition()
{
    ui->stackedWidget->setCurrentIndex(1);
    setChecked(1);
}

void MainWindow::ShowLyricsMode()
{
    ui->stackedWidget->setCurrentIndex(2);
    setChecked(2);

}

void MainWindow::ShowMemoryMode()
{
    ui->stackedWidget->setCurrentIndex(5);
    setChecked(5);
}

void MainWindow::ShowChordMode()
{
    ui->stackedWidget->setCurrentIndex(3);
    setChecked(3);
}

void MainWindow::ShowTextMode()
{
    ui->stackedWidget->setCurrentIndex(4);
    setChecked(4);
}

void MainWindow::setChecked(int i)
{
    ui->actionSelectChord->setChecked(i==3);
    ui->actionSelectDefinition->setChecked(i==1);
    ui->actionSelectEditor->setChecked(i==0);
    ui->actionSelectLyrics->setChecked(i==2);
    ui->actionSelectMemory->setChecked(i==5);
    ui->actionSelectText->setChecked(i==4);
}


void MainWindow::ShowStacked( int i )
{
    m_labelactivestacked->setText(m_liststacked.at(i));
}

void MainWindow::Documentation()
{
    DialogDocumentation *dial= new DialogDocumentation(this);
    dial->show();

}

void MainWindow::TwoLines2Chordpro()
{
  DialogTwoLinesToChordPro dial(this);
  dial.exec();
}

void MainWindow::ChangeChordLang()
{
 DialogChangeChordName dial(this);
 dial.setFromLang(ui->comboBoxChordLanguage->currentIndex());
 dial.setFromMin(ui->comboBoxMinorNotation->currentIndex());
 dial.setToLang(ui->comboBoxChordLanguage->currentIndex());
 dial.setToMin(ui->comboBoxMinorNotation->currentIndex());
 dial.exec();
 QStringList out;
 if (dial.OkDialog())
 {
   QStringList lines=ui->textEditCho3File->document()->toPlainText().split("\n");
   foreach (QString line , lines)
      {
       line=Language::TranslateLineWithchord(line,dial.getFromLang(),dial.getFromMin(),dial.getToLang(),dial.getToMin());
       out<<line;
      }
   }
 ui->textEditCho3File->document()->clear();
 ui->textEditCho3File->document()->setPlainText(out.join("\n"));
 ui->comboBoxChordLanguage->setCurrentIndex(dial.getToLangIndex());
 ui->comboBoxMinorNotation->setCurrentIndex(dial.getToMinIndex());
}
