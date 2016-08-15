#ifndef TEXTBOOK_H
#define TEXTBOOK_H

#include "processor.h"

class TextBook : public Processor
{
public:
    TextBook(QString text, QString dirfile);
};

#endif // TEXTBOOK_H
