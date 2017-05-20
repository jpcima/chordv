#include     "pdfviewer.h"

#include <QSettings>
#include <QProcess>
#include <QMessageBox>
#include <QDebug>

PdfViewer::PdfViewer(QString filename)
{
    QSettings s;
    if ( s.value("PDFReader").toString().isEmpty())
    {
        QMessageBox::warning(this,tr("Variable PDFREader not set in Configuration")
                             ,tr("Go to Tools/Preference and set the PDF Reader name and path ")
                             ,tr("Ok"));
        m_process=0;

    }
    else
    {
        m_process = new QProcess(this);
        connect ( m_process,SIGNAL(finished(int)),this,SLOT(endProcess(int)));
        QStringList arg;
        arg<<filename;
        m_process->start(s.value("PDFReader").toString(),arg);
    }
}


void PdfViewer::endProcess(int)
{
    if ( m_process != 0 )
        delete m_process;
    emit finished();
}
