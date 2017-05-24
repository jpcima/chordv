#include "chordconfig.h"

ChordConfig::ChordConfig(QWidget *parent):FormConfig(parent)
{
   disableWidgets(QRegExp("ChordDiagramHorizontalSize$"));
   InitDefault(FormConfig::Chord);
   QStringList list;
   list<<tr("Name of chord");
   list<<tr("Diagram of chord");
   InitComboBoxChordInclusion(list);
}
