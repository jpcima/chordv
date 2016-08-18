#include "chordconfig.h"

ChordConfig::ChordConfig(QWidget *parent):FormConfig(parent)
{
   disableWidgets(QRegExp("ChordDiagramHorizontalSize$"));
   InitDefault(FormConfig::Chord);
}
