#include "processorlyrics.h"
#include "ui_formconfig.h"
#include "chord.h"

#include <QDebug>
#include <QStringList>
ProcessorLyrics::ProcessorLyrics(Ui::MainWindow *ui1, Ui::FormConfig *ui2):Processor(ui1,ui2)
{

}

void ProcessorLyrics::displayChordsForSong()
{
  QStringList chords=m_BufChords;
  QStringList chordswithouttempo=Chord::removeDupplicateWhithoutTempo(chords,m_uiconfig->comboBoxChordLang->currentData().toString());
  if (m_uiconfig->comboBoxChordInText->currentIndex()==0)
  {
      foreach ( QString chord, chordswithouttempo)
    {
        displayChord(chord,m_line,m_column,m_uiconfig->spuChordHorizontalSize->getPdfU());
    }
  }
  m_column=m_uiconfig->spuHorizontalMargin->getPdfU();
  m_line-=m_uiconfig->spuChordHorizontalSize->getPdfU();


}
