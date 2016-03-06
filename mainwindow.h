#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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
private slots:
    void newProject(bool);
    void openProject(bool);
    void setChordMode(int i);
    void setLyricsMode(int i);
    void setTextMode(int i);
    void Log(QString message);
    void Save(bool);
    void SaveAs(bool);
};

#endif // MAINWINDOW_H
