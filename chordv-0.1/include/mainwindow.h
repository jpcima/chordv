#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "pdfviewer.h"
#include "chordconfig.h"

#include <QTranslator>
#include <QToolButton>
#include <QProcess>
#include <QMainWindow>
#include <QMenu>
#include <QLabel>
namespace Ui {
class MainWindow;
}

/// \mainpage General documentation for ChordV developpers
/// \section Introduction
///
/// ChordV allow to edit song booklet with lyrics and text of song, or only chords
/// output, or only Luyrics output
/// All feature are accessible from the MainWindow.
/// All the MainWindow features are accessible from Menu
/// There are many mode :
/// - Edition mode where users can enter text, chords and lyrics
/// - Lyrics mode where users can define the Lyrics mode booklets
/// - Text mode where users can define the Text booklets
/// - Text and Chors mode where users can define the options for the Text and chord booklets
/// In preferences dialog option you can design the general booklet definition and change
/// the behaviour for each booklet from the behaviour defined in option.
/// \section Edition
///
/// \section "Chord mode"
///
///



///
/// \brief The MainWindow class
///
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setTranstator(QTranslator *tr) { m_translator= tr;}
private:
    Ui::MainWindow *ui;
    QString m_currentprojectname;
    QString m_currentprojectfile;
    QString m_currentprojectdir;
    QMenu *m_lastmenu;
    QTranslator *m_translator;
    void setMenuLastProject();
    void InitProject();
    void openchoFile(QString filename);
    ///
    /// \brief Save : save the current project in a file name
    /// \param filename
    ///
    void Save(QString filename);
    ///
    /// \brief getFileInArg allows  to retrieve the name of file to open if chordV is called
    /// with a filename argument
    /// \return return the first file in arguments of main, no starting with -
    ///
    QString  getFileInArg();
    ///
    /// \brief testMode test if chordV is called with -t or --test argument
    /// \return true if there is -t or --test argument false else
    ///
    bool testMode();
    QString getRelativeFilename(QString chofilename);
    void ActualizeProject(QString file);
    QString m_pdffilename;


    bool m_found;
    void setChecked(int i);
    QString getPdfFileName(QString  text);
    QLabel *m_labelactivestacked;
    QStringList m_liststacked;

    QString m_initialbuffer;

    void InitDefault();
public slots:
    void ChangeLanguage(QString );

private slots:
    void newProject(bool);
    void openProject(bool);
    void setChordMode(int i);
    void setLyricsMode(int i);
    void setTextMode(int i);
    void setMemoryMode(int i);
    void Log(QString message);
    void Save(bool);
    void SaveAs(bool);
    void LastProjectOpen(QAction *action);
    void openProject(QString filename);
    void ProducePDF();
    void About();
    void Configuration();
    void openChoFile(QString filename);
    void openChoFile(bool);
    void PreferencesAsOrigine();
    void CurrentAsDefault();
    void Info(QString info);
    void Close();
    void ProducePDFAndShow();
    void PDFReaderChanged();
    void ConversionDone(QString filename);

    void ChordDefinition();
    void SystemInfo();
    void Search();
    void Replace();
    void Search(QString text, bool casesensitive, bool wordonly);
    void SearchBack(QString text, bool casesensitive, bool wordonly);
    void Replace(QString textfrom, QString textto, bool all, bool casesensitive, bool wordonly, bool back);
    void ShowDefinition();
    void ShowLyricsMode();
    void ShowMemoryMode();
    void ShowChordMode();
    void ShowTextMode();

    void ShowEditor();
    void BuildTextPdf();
    void BuildLyricsPdf();
    void BuildChordPdf();
    void BuildMemoryPdf();
    void ViewLastBuildPdf();
    void ViewTextPdf();
    void ViewLyricsPdf();
    void ViewChordPdf();
    void ViewMemoryPdf();

    void ExportCho3File();
    void ShowStacked(int i);
    void BuildAndViewText();
    void BuildAndViewMemory();
    void BuildAndViewChord();
    void BuildAndViewLyrics();
    void ZoomIn();
    void ZoomOut();
    void Documentation();
    void TwoLines2Chordpro();
    void ChangeChordLang();
    void AskSaveOnQuit();
    void TransposeChords();
};

#endif // MAINWINDOW_H
