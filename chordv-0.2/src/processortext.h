#ifndef PROCESSORTEXT_H
#define PROCESSORTEXT_H

#include "processor.h"
#include "mainwindow.h"
class ProcessorText : public Processor
{
public:
    ProcessorText(Ui::MainWindow *ui1,Ui::FormConfig *ui2);
private:
    void includeChorus(QString ){}
    void includeEoc(){}
    void includeSoc(){}
    void includeEor(){}
};

#endif // PROCESSORTEXT_H
