#ifndef LYRICSBOOK_H
#define LYRICSBOOK_H

#include "processor.h"

class LyricsBook : public Processor
{
public:
    LyricsBook(QString text, QString dir);

};

#endif // LYRICSBOOK_H
