#include     "pdfviewer.h"

#include <QSettings>
#include <QProcess>
#include <QMessageBox>
#include <QDebug>
#include <QApplication>
#include <QFileInfo>

PdfViewer::PdfViewer(QString filename, QWidget *parent)
{
    QSettings s;
    m_filename=filename;
    QString command =s.value("PDFReader").toString();
    QFileInfo fi(filename);
    if ( ! fi.exists() )
    {
        QMessageBox::warning(parent,qApp->translate("pdfReader","File not found")
                             ,qApp->translate("pdfReader","PDF file %1 not yet generated !").arg(filename)
                             ,qApp->translate("pdfReader","Ok"));
        m_status=false;
        m_error= qApp->translate("pdfReader","PdfReader: file %1 not found").arg(filename);

    }

    else if ( command.isEmpty())
    {
        QMessageBox::warning(parent,qApp->translate("pdfReader","Variable PDFReader not set in Configuration")
                             ,qApp->translate("pdfReader","Go to Tools/Preference and set the PDF Reader name and path ")
                             ,qApp->translate("pdfReader","Ok"));
        m_status=false;
        m_error= qApp->translate("pdfReader","PdfReader: PDFReader not configured");

    }
    else
    {
        QStringList arg;
        arg<<m_filename;
        m_status =QProcess::startDetached(command,arg);
        m_error=qApp->translate("pdfReader","PdfReader: Unknown error");

     }

}

bool PdfViewer::getStatus()
{
    return m_status ;
}

QString PdfViewer::getStatusError()
{
    return m_error;
}

QString PdfViewer::getStatusInfo()
{
    return (qApp->translate("pdfReader","PdfReader: %1 launched").arg(m_filename));
}
