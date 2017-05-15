#include "processorlyrics.h"
#include "ui_formconfig.h"
#include <QDebug>
#include <QStringList>
ProcessorLyrics::ProcessorLyrics(Ui::MainWindow *ui1, Ui::FormConfig *ui2):Processor(ui1,ui2)
{

}

void ProcessorLyrics::displayChordsForSong()
{
  QStringList chords=m_BufChords;
  chords.removeDuplicates();
  if (m_uiconfig->comboBoxChordInText->currentIndex()==0)
  {
      foreach ( QString chord, chords)
    {
        displayChord(chord,m_line,m_column,m_uiconfig->spuChordHorizontalSize->getValue());
        m_line-=m_uiconfig->spuChordHorizontalSize->getValue();
        m_column+= m_uiconfig->spuChordHorizontalSize->getValue();
    }
  }

}
