#ifndef DIALOGPROCESSMEMORY_H
#define DIALOGPROCESSMEMORY_H

#include <QDialog>
#include <QMap>
#include <QTimer>
#include <QMediaPlayer>
#include <jack/jack.h>
#include <jack/transport.h>



namespace Ui {
class DialogProcessMemory;
}

class DialogProcessMemory : public QDialog
{
    Q_OBJECT

public:
    explicit DialogProcessMemory(QWidget *parent ,QString allsongs,int position, QString title,  bool showrythm, bool click, int volume, bool firstaccentued,
                                 QFont font, QColor text, QColor background,bool fullscreen, bool twolines,double advance, int nbbarsbefore, bool jacksynchro);
    ~DialogProcessMemory();
    bool getJackConnected() { return m_jacksynchro ;}

private slots:
    void displaySong();
    void showRythm();
    void eraseBull();
    void Close();
    void JackMessages();
private:
    enum State{NotStarted,Running,Paused,Finished};
    Ui::DialogProcessMemory *ui;
    bool m_stop;
    bool m_firststart;
    bool m_pause;
    double m_tempo;
    int m_timeup;
    bool m_click;
    bool m_accentuedfirst;
    State m_status;
    int m_volume;
    int m_timebefore;
    double m_advance;
    QTimer *m_timerend;
    QTimer *m_timerrythm;
    QTimer *m_timerclearrythm;
    QTimer *m_timerlyrics;
    QTimer *m_timerbefore;
    QTimer *m_timeline;
    QMap <int,int> m_seconds;
    QMap <int,QString> m_lyrics;
    QStringList m_refrain;
    QMap <int,int>m_refrainnbbeat;
    QMap <int,int>m_coupletnbbeat;
    int m_nblinecouplet;
    int m_nblinerefrain;
    int m_nblyrics;
    bool m_showrythm;
    bool m_jacksynchro;
    QFont m_font;
    QColor m_textcolor;
    QColor m_backgroundcolor;
    int m_indice;
    int m_countrythm;
    int m_period;
    int m_millisecondperbeat;
    int m_time;
    QMediaPlayer *m_player;
    jack_client_t *m_jackclient;

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
    int getNumberOfBeat(QString &line, int timeup);
    void displayLine();
    QColor getColorBetween(QColor color1, QColor color2);
    void DeleteAllTimers();
    void keyPressEvent(QKeyEvent *);
    void PauseFlipFlop();
};

#endif // DIALOGPROCESSMEMORY_H
