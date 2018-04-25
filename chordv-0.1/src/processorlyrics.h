#ifndef PROCESSORLYRICS_H
#define PROCESSORLYRICS_H

#include "processor.h"
#include "mainwindow.h"
#include "fontbutton.h"
#include <podofo/podofo.h>
#include <podofo/podofo-base.h>

///
/// \brief The ProcessorLyrics class allows to print lyrics and chord on booklet
/// the chord can be printed with its name or with the diagram of chord inside text
///
class ProcessorLyrics : public Processor
{
public:
    ///
    /// \brief ProcessorLyrics the constructor take ui pointer on mainwindow and FormConfig pointer
    /// \param ui1 : pointer on Ui::MainWindow
    /// \param ui2 : pointer on FormConfig
    ///
    ProcessorLyrics(Ui::MainWindow *ui1,Ui::FormConfig *ui2);
private:
    ///
    /// \brief displayChordsForSong displays all the chords at the begining of the song when
    /// this mode is selected
    ///
    void displayChordsForSong();
    ///
    /// \brief displayLyrics displays lyrics and chord or diagrams when needed
    ///
    void displayLyrics();
    void includeEor(){}
    void includeEoc(){}
    void doColumnBreak(QString line);
    void Drawline(double pos, int num, FontButton *ptr);
};

#endif // PROCESSORLYRICS_H
