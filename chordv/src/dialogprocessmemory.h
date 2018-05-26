#ifndef DIALOGPROCESSMEMORY_H
#define DIALOGPROCESSMEMORY_H

#include <QDialog>
#include <QMap>
#include <QTimer>


namespace Ui {
class DialogProcessMemory;
}

class DialogProcessMemory : public QDialog
{
    Q_OBJECT

public:
    explicit DialogProcessMemory(QWidget *parent ,QString allsongs,int position, QString title,  bool showrythm, QFont font, QColor text, QColor background,bool fullscreen, bool twolines);
    ~DialogProcessMemory();

private slots:
    void displaySong();
    void showRythm();
    void eraseBull();
private:
    Ui::DialogProcessMemory *ui;
    int m_tempo;
    int m_timeup;
    QTimer *m_timer;
    QTimer *m_timerrythm;
    QTimer *m_timerclearrythm;
    QMap <int,int> m_seconds;
    QMap <int,QString> m_lyrics;
    QStringList m_refrain;
    QMap <int,int>m_refrainnbbeat;
    QMap <int,int>m_coupletnbbeat;
    int m_nblinecouplet;
    int m_nblinerefrain;
    int m_nblyrics;
    bool m_showrythm;
    QFont m_font;
    QColor m_textcolor;
    QColor m_backgroundcolor;
    int m_msecPerBar;
    int m_indice;
    int m_countrythm;
    ///
    /// \brief getInfo get all the information in song file, about the song named title
    /// \param songs : the whole songs buffer
    /// \param title : the title of song searched
    ///
    void getInfo(QString songs,QString title);
    ///
    /// \brief MillisecondPerBar find number of milliseconds to play from a tempo and with a timeup/timedown time signature
    /// \param tempo : int for tempo. For example 120 fot 120 quarter note per minute
    /// \param timeup : int for timeup. For example 3 for walz. 3/4 timeup is 3
    /// \param timedown : int for timedown : 3/4 timedown is 4
    /// \return : the number of second for a bar
    ///
    int MillisecondPerBeat(int tempo);
    int getNumberOfBeat(QString &line, int timeup);
    void displayLine();
    QColor getColorBetween(QColor color1, QColor color2);
};

#endif // DIALOGPROCESSMEMORY_H
