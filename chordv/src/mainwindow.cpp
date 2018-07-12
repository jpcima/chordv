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
#include "dialogtranspose.h"
#include "dialogprocessmemory.h"

#include "lyricsconfig.h"
#include "formconfig.h"
#include "textconfig.h"
#include "memoryconfig.h"
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
#include <QMessageBox>
#include <QDesktopWidget>
#include <QApplication>
#include <QFontMetrics>
#include <QModelIndex>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setSongNumberStatusbar(0);
    QSettings s;
    QList <int> size;
    size<<700<<100;
    m_demofile=false;
    m_labelactivestacked= new QLabel(this);
    ui->statusBar->addWidget(m_labelactivestacked);
    m_labelactivestacked->setStyleSheet("Background-color:#d5e6ef;Color:#5d5555;font: bold 12px; ");
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
    InitProject();
    connect(ui->actionNew_Project,SIGNAL(triggered(bool)),this,SLOT(newProject(bool)));
    connect(ui->actionOpen_Project,SIGNAL(triggered(bool)),this,SLOT(openProject(bool)));
    connect(ui->actionOpen_Song_File,SIGNAL(triggered(bool)),this,SLOT(openChoFile(bool)));
    connect(ui->actionExport_tho_cho3_file,SIGNAL(triggered(bool)),this,SLOT(ExportCho3File()));
    connect(ui->actionSave,SIGNAL(triggered(bool)),this,SLOT(Save(bool)));
    connect(ui->actionSave_As,SIGNAL(triggered(bool)),this,SLOT(SaveAs(bool)));
    connect(ui->actionClose,SIGNAL(triggered(bool)),this,SLOT(Close()));
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
    connect(ui->actionAbout,SIGNAL(triggered()),this,SLOT(About()));
    connect(ui->action2Line2chordpro,SIGNAL(triggered(bool)),this,SLOT(TwoLines2Chordpro()));
    connect(ui->actionChangeChordLang,SIGNAL(triggered(bool)),this,SLOT(ChangeChordLang()));
    connect(ui->actionTranspose_chords,SIGNAL(triggered(bool)),this,SLOT(TransposeChords()));
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
    connect(qApp,SIGNAL(aboutToQuit()),this,SLOT(AskSaveOnQuit()));
    connect (ui->actionLoad_demo_file,SIGNAL(triggered(bool)),this,SLOT(LoadDemoFile()));
    connect( ui->textEditCho3File,SIGNAL(Toc(QStringList)),this,SLOT(SetTocInMemoryMode(QStringList)));
    connect (ui->pushButtonLaunchMemory,SIGNAL(clicked(bool)),this,SLOT(LaunchMemory()));
    connect (ui->widgetMemory,SIGNAL(SynchroMode(bool)),this,SLOT(SetSynchroDisplay(bool)));
    connect (ui->textEditCho3File,SIGNAL(SongSelected(QString)),this,SLOT(SelectSongInMemory(QString)));
    connect (&m_protectStatusBar,SIGNAL(clicked(bool)),&m_selectedsongStatusBar,SLOT(setDisabled(bool)));
    connect (ui->tableWidgetToc,SIGNAL(clicked(QModelIndex)),this,SLOT(SetSelected(QModelIndex)));
    connect (ui->actionCopy,SIGNAL(triggered(bool)),ui->textEditCho3File,SIGNAL(Copy()));
    connect (ui->actionCut,SIGNAL(triggered(bool)),ui->textEditCho3File,SIGNAL(Cut()));
    connect (ui->actionPaste,SIGNAL(triggered(bool)),ui->textEditCho3File,SIGNAL(Paste()));

    ui->tableWidgetToc->setColumnCount(1);
    ui->tableWidgetToc->setColumnWidth(0,65532);
    ui->tableWidgetToc->setSelectionMode(QAbstractItemView::SingleSelection);
    QStringList list;
    list<<tr("Songs list");
    ui->tableWidgetToc->setHorizontalHeaderLabels(list);
    QString file=getFileInArg();
    if ( ! file.isEmpty() )
    {
        QFileInfo fi(file) ;
        if ( ! fi.exists())
        {
            qDebug()<<tr("%1 does'nt exit. Bye !") ;
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
    Chord A("La7b","fr");
    ui->widgetMemory->SynchroMode(s.value("Memory/JackSynchro",false).toBool());
    ui->statusBar->addWidget(&m_filenameStatusBar);
    ui->statusBar->addWidget(&m_dirnameStatusBar);
    ui->statusBar->addWidget(&m_songnumberStatusBar);
    m_selectedsongStatusBar.setStyleSheet("QLineEdit:disabled{background-color:#e8e99c;Color:#5d5555};QLineEdit{font: bold 12px;}");
    m_songnumberStatusBar.setStyleSheet("Background-color:#d5e6ef;Color:#5d5555;font: bold 12px;");
    ui->statusBar->addWidget(&m_selectedsongStatusBar);
    ui->statusBar->addWidget(&m_protectStatusBar);
    m_protectStatusBar.setStyleSheet("Background-color:#d5e6ef;Color:#5d5555;font: bold 12px;");
    m_protectStatusBar.setText(tr("Keep selected Song"));
}

void MainWindow::setFilenameStatusbar(QString filename)
{
    QFileInfo fi(filename);
    if ( fi.isWritable() )
         m_filenameStatusBar.setStyleSheet("Background-color:#95ce7e;Color:#5d5555;font: bold 12px;");
    else
         m_filenameStatusBar.setStyleSheet("Background-color:#dd8585;Color:#5d5555;font: bold 12px;");
    m_filenameStatusBar.setText(fi.fileName());
}

void MainWindow::setDirNameStatusbar(QString filename)
{

    QFileInfo fi(filename);
    if ( fi.isWritable() )
         m_dirnameStatusBar.setStyleSheet("Background-color:#95ce7e;Color:#5d5555;font: bold 12px;");
    else
         m_dirnameStatusBar.setStyleSheet("Background-color:#dd8585;Color:#5d5555;font: bold 12px;");
   m_dirnameStatusBar.setText(fi.absolutePath());
}
void MainWindow::setSongNumberStatusbar(int number)
{
    m_songnumberStatusBar.setText(tr("%1 song(s)").arg(number));
}

void MainWindow::setSelectedSongStatusBar(QString songname)
{

    if ( ! m_protectStatusBar.isChecked())   m_selectedsongStatusBar.setText(songname);
}





void MainWindow::AskSaveOnQuit()
{
    if ( m_initialbuffer!= ui->textEditCho3File->document()->toPlainText())
    {
        int i = QMessageBox::warning(this,tr("Buffer as changed"),tr("Do you want to save ? "),
                          QMessageBox::Yes,QMessageBox::No   );
        if ( i==QMessageBox::Yes)
            Save(true);

    }
}

void MainWindow::Close()
{
    AskSaveOnQuit();
    ui->textEditCho3File->clear();
    m_initialbuffer.clear();
    InitDefault();
    ClearInfoFile();

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
    InitDefault();
    // TODO restore global elem.

}

void MainWindow::InitDefault()
{
    ui->widgetChordMode->InitDefault("Chord");
    ui->widgetLyricsMode->InitDefault("Lyrics");
    ui->widgetTextMode->InitDefault("Text");
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
    if ( filename.isEmpty()) return;
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) ui->log->Error(QString(tr("Cannot open file : %1").arg(filename)));
    else
    {
        QTextStream in(&file);
        ui->textEditCho3File->append(in.readAll());
        QTextCursor textCursor = ui->textEditCho3File->textCursor();
        textCursor.movePosition(QTextCursor::Start, QTextCursor::MoveAnchor);
        ui->textEditCho3File->setTextCursor(textCursor);
        DisplayInfoFile(filename);
    }
}


void MainWindow::DisplayInfoFile( QString filename)
{
 setDirNameStatusbar(filename);
 setFilenameStatusbar(filename);
}

void MainWindow::ClearInfoFile()
{
  m_filenameStatusBar.clear();
  m_dirnameStatusBar.clear();
}
void MainWindow::openProject(QString filename)
{
    QSettings s;
    ui->log->clear();
    QFileInfo fi(filename);
    m_currentprojectname=fi.baseName();
    m_currentprojectdir=fi.absolutePath();
    if (! m_demofile)
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
    ui->widgetChordMode->SetConfigFromFile(filename);
    ui->widgetChordMode->InitDefault("Chord");
    ui->widgetChordMode->setProjectPath(m_currentprojectdir);
    ui->widgetLyricsMode->SetConfigFromFile(filename);
    ui->widgetLyricsMode->InitDefault("Lyrics");
    ui->widgetLyricsMode->setProjectPath(m_currentprojectdir);
    ui->widgetTextMode->SetConfigFromFile(filename);
    ui->widgetTextMode->InitDefault("Text");
    ui->widgetTextMode->setProjectPath(m_currentprojectdir);
    ui->widgetMemory->Init(filename);
    m_initialbuffer=p.value("Content").toString();
    ui->textEditCho3File->setText(m_initialbuffer);
    //ui->checkBoxLongShort->setChecked(ui->textEditCho3File->document()->toPlainText().contains("{covertitle:",Qt::CaseInsensitive));
    DisplayInfoFile(filename);
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
    ui->widgetChordMode->Save(filename,"Chord");
    ui->widgetLyricsMode->Save(filename,"Lyrics");
    ui->widgetTextMode->Save(filename,"Text");
    ui->widgetMemory->Save(filename);
    m_initialbuffer=ui->textEditCho3File->document()->toPlainText();
    m_demofile=false;
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
    if ( m_currentprojectname.isEmpty() )
        SaveAs(true);
    else m_currentprojectfile=m_currentprojectdir+"/"+m_currentprojectname+".chop";
    QSettings sf(m_currentprojectfile,QSettings::IniFormat);
    sf.clear();
    sf.setValue("Creator",ui->lineEditCreatorName->text());
    sf.setValue("ChordLang",ui->comboBoxChordLanguage->currentIndex());
    sf.setValue("ChordMinor",ui->comboBoxMinorNotation->currentText());
    sf.setValue("Content",ui->textEditCho3File->document()->toPlainText());
    sf.sync();
    ui->widgetChordMode->Save(m_currentprojectfile,"Chord");
    ui->widgetLyricsMode->Save(m_currentprojectfile,"Lyrics");
    ui->widgetTextMode->Save(m_currentprojectfile,"Text");
    ui->widgetMemory->Save(m_currentprojectfile);
    m_initialbuffer=ui->textEditCho3File->document()->toPlainText();
}


void MainWindow::SaveAs(bool)
{
    m_currentprojectfile=QFileDialog::getSaveFileName(this,tr("Save project as"),ChordUtil::getLastDirectory(),tr("(*.chop)"));
    if (!m_currentprojectfile.isEmpty() )
    {
        QFileInfo fi( m_currentprojectfile);
        m_currentprojectname=fi.baseName();
        m_currentprojectdir=fi.absolutePath();
        QDir::setCurrent(m_currentprojectdir);
        ui->labelNameProjectName->setText(m_currentprojectname);
        ui->labelNameDirProject->setText(m_currentprojectdir);
        Save(true);
        ChordUtil::setLastDirectory(m_currentprojectfile);
    }
}

void MainWindow::ActualizeProject( QString )
{

}

void MainWindow::ProducePDF()
{
//  if (ui->checkBoxTextMode->isChecked())
//  {
     BuildTextPdf();
//  }
//  if (ui->checkBoxLyricsMode->isChecked())
//  {
     BuildLyricsPdf();
//  }
//  if ( ui->checkBoxChordMode->isChecked())
//  {
      BuildChordPdf();
//  }
//  if ( ui->checkBoxMemoryMode->isChecked())
//  {
      BuildMemoryPdf();
//  }
}





void MainWindow::BuildTextPdf()
{
    ProcessorText *p;
    p= new ProcessorText(ui,ui->widgetTextMode->getUi());
    connect(p,SIGNAL(PDFMade(QString)),this, SLOT(ConversionDone(QString)));
    connect(p,SIGNAL(Error(QString)),this,SLOT(DisplayError(QString)));
    p->run() ;
    p->deleteLater();
}

void MainWindow::BuildLyricsPdf()
{
    ProcessorLyrics *p;
    p= new ProcessorLyrics(ui,ui->widgetLyricsMode->getUi());
    connect(p,SIGNAL(PDFMade(QString)),this, SLOT(ConversionDone(QString)));
    connect(p,SIGNAL(Error(QString)),this,SLOT(DisplayError(QString)));
    p->run() ;
    p->deleteLater();
}

void MainWindow::BuildChordPdf()
{
    ProcessorChord *p;
    p = new ProcessorChord(ui,ui->widgetChordMode->getUi());
    connect(p,SIGNAL(PDFMade(QString)),this, SLOT(ConversionDone(QString)));
    connect(p,SIGNAL(Error(QString)),this,SLOT(DisplayError(QString)));
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


void MainWindow::DisplayError(QString message)
{
    QMessageBox::warning(this,tr("Problem !"),message);
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
    ui->widgetTextMode->Retranslate();
    ui->textEditCho3File->retranslate();
    ui->widgetMemory->Retranslate();
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
         ui->textEditCho3File->insertPlainText(textto,false);
         if ( back ) SearchBack(textfrom,casesensitive,wordonly);
         else Search(textfrom,casesensitive,wordonly);
        }
    }
    else
    {
        ui->textEditCho3File->textCursor().clearSelection();
        ui->textEditCho3File->insertPlainText(textto,false);
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

///
/// \brief MainWindow::ChangeChordLang change the chord lang for the current Edited file
///
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


void MainWindow::TransposeChords()
{
   DialogTranspose dial(this);
   ui->textEditCho3File->setChordLanguage(ui->comboBoxChordLanguage->currentText());
   connect(&dial,SIGNAL(AskChange(int,int)),ui->textEditCho3File,SLOT(TransposeChord(int,int)));
   dial.exec();
}

void MainWindow::LoadDemoFile()
{
    QSettings s;
    QString language=s.value("InterfaceLanguage").toString();
    if (language.isEmpty()) language="English";

    QString filename=Language::getTranslationDemoFileName(language);
    openProject(filename);
    m_demofile=true;
}

void MainWindow::SetTocInMemoryMode(QStringList toc)
{
    ui->tableWidgetToc->clear();
    ui->tableWidgetToc->setRowCount(toc.count());
    int i=0;
    foreach ( QString elem , toc)
    {
        ui->tableWidgetToc->setItem(i,0, new QTableWidgetItem(elem));
        i++;
    }
    setSongNumberStatusbar(i);
}


void MainWindow::LaunchMemory()
{

    if ( m_selectedsongStatusBar.text().isEmpty() &&  ui->tableWidgetToc->selectedItems().count()==0)
    {
        QMessageBox::warning(this,tr("No title selected"),tr("You must select a title"));
        return;
    }
    QString title;
    if ( ! m_selectedsongStatusBar.text().isEmpty())
      title=m_selectedsongStatusBar.text();
    else
      title = ui->tableWidgetToc->selectedItems().at(0)->text();
    this->hide();
    DialogProcessMemory memory(this,
                                                          ui->textEditCho3File->document()->toPlainText(),
                                                          ui->widgetMemory->getPosition(),
                                                          title,
                                                          ui->widgetMemory->getShowRythm(),
                                                          ui->widgetMemory->getClick(),
                                                          ui->widgetMemory->getVolume(),
                                                          ui->widgetMemory->getAccentuedFirst(),
                                                          ui->widgetMemory->getFont(),
                                                          ui->widgetMemory->getTextColor(),
                                                          ui->widgetMemory->getBackgroundColor(),
                                                          ui->widgetMemory->getFullscreenMode(),
                                                          ui->widgetMemory->getShowTwoLines(),
                                                          ui->widgetMemory->getAdvance(),
                                                          ui->widgetMemory->getDelay(),
                                                          ui->widgetMemory->getJackSynchro(),
                                                          ui->widgetMemory->getTimeBeforeUnit()
                                                          );

    memory.exec();
    ui->widgetMemory->setJackSynchro(memory.getJackConnected());
    this->show();
}


void MainWindow::SetSynchroDisplay(bool val)
{
    if (val)
        ui->labelESCAPEPAUSE->setText(tr("< ESCAPE >  to abort monitoring window"));
    else
        ui->labelESCAPEPAUSE->setText(tr("< ESCAPE >  to abort monitoring window\n< PAUSE> to pause unpause"));
}


void MainWindow::SelectSongInMemory(QString song)
{
   ui->tableWidgetToc->selectionModel()->clearSelection();
     QList<QTableWidgetItem*> list=ui->tableWidgetToc->findItems(song,Qt::MatchExactly);
     if ( !list.empty() )
     {
         list.at(0)->setSelected(true);
     }
     setSelectedSongStatusBar(song);
}

void MainWindow::SetSelected(QModelIndex index)
{
    setSelectedSongStatusBar(index.data().toString());
}
