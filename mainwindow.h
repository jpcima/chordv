#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include "editorhighlighter.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    EditorHighlighter *m_editorhighlight;
    QString m_currentproject;
    QMenu *m_lastmenu;

    void setMenuLastProject();
    void InitProject();
    void openFile(QString filename);
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

};

#endif // MAINWINDOW_H
