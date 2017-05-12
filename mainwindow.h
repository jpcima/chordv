#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include "editorhighlighter.h"
#include <QTranslator>
#include <QToolButton>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setTranstator(QTranslator *tr) { m_translator= tr;}
private:
    Ui::MainWindow *ui;
    EditorHighlighter *m_editorhighlight;
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
    bool SaveCho3(QString file);
    QString m_pdffilename;
    void ReplaceLongShort(QString a, QString b);
    QString m_buffreplace;
    void GenericInsert(QToolButton *w, QString token, QString label1, QString label2);
    bool m_found;
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
    void SetInputFile();
    void Configuration();
    void openChoFile(QString filename);
    void openChoFile(bool);
    void PreferencesAsOrigine();
    void CurrentAsDefault();
    void Info(QString info);

    void ProducePDFAndShow();
    void PDFReaderChanged();
    void ConversionDone(QString filename);
    void InsertT();
    void ToogleLongShort();
    void InsertST();
    void InsertCol();
    void InsertCompress();
    void InsertCS();
    void InsertCT();
    void InsertEOC();
    void InsertSOC();
    void InsertRef();
    void InsertCB();
    void ChordDefinition();
    void SystemInfo();
    void Search();
    void Replace();
    void Search(QString text, bool casesensitive, bool wordonly);
    void SearchBack(QString text, bool casesensitive, bool wordonly);
    void Replace(QString textfrom, QString textto, bool all, bool casesensitive, bool wordonly, bool back);
};

#endif // MAINWINDOW_H
