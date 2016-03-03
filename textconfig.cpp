#include "textconfig.h"

TextConfig::TextConfig(QWidget *parent):FormConfig(parent)
{   disableWidgets(QRegExp("ChordDiagramHorizontalSize$"));
   disableWidgets(QRegExp("ChordLang$"));
   disableWidgets(QRegExp("ChordInText$"));
}
