#ifndef PROCESSORTEXT_H
#define PROCESSORTEXT_H

#include "processor.h"

class ProcessorText : public Processor
{
public:
    ProcessorText(QString SontText, QString dir,Ui::FormConfig *ui);
};

#endif // PROCESSORTEXT_H
