#ifndef PDFVIEWER_H
#define PDFVIEWER_H

#include <QProcess>
#include <QWidget>

class PdfViewer
{
    Q_OBJECT
public:
    PdfViewer( QString filename);
private slots:
    void endProcess(int);
private:
    QProcess *m_process;
signals:
    void finished();
};

#endif // PDFVIEWER_H
