#ifndef PDFVIEWER_H
#define PDFVIEWER_H

#include <QProcess>
#include <QWidget>

class PdfViewer : public QWidget
{
    Q_OBJECT
public:
    PdfViewer( QString filename,QWidget *parent);
private slots:
    void endProcess(int);
private:
    QProcess *m_process;
};

#endif // PDFVIEWER_H
