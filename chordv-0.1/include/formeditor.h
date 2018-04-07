#ifndef FORMEDITOR_H
#define FORMEDITOR_H

#include <QWidget>
#include <QTextCursor>
#include <QTextDocument>
#include <QToolButton>
#include <QModelIndex>
#include "dialognewsong.h"


namespace Ui {
class FormEditor;
}

class FormEditor : public QWidget
{
    Q_OBJECT

public:
    explicit FormEditor(QWidget *parent = 0);
    ~FormEditor();
    void clear();
    void append(QString);
    QTextCursor textCursor();
    void setTextCursor(QTextCursor textcursor);
    void setText(QString text);
    QTextDocument *document();
    void copy();
    void insertPlainText(QString text);
    void retranslate();
    bool find(QString text, QTextDocument::FindFlags flag);
public slots:
    void zoomIn();
    void zoomOut();
private:
    Ui::FormEditor *ui;
    void ReplaceLongShort(QString a, QString b);
    QString m_buffreplace;
    void resizeEvent(QResizeEvent *event);
    DialogNewSong *m_dialognewsong;
    void Init();
private slots:
    void InsertTempo();
    void InsertTime();
    void InsertT();
    void ToogleLongShort();
    void InsertST();
    void InsertCol();
    void InsertCompress();
    void InsertCS();
    void InsertCT();
    void InsertEOC();
    void InsertSOC();
    void InsertSOR();
    void InsertEOR();
    void InsertCB();
    void GenericInsert(QToolButton *w, QString token, QString label1, QString label2);
    void InsertPageBreak();
    void InsertSOV();
    void InsertEOV();
    void InsertAlbum();
    void InsertComposer();
    void InsertArtist();
    void InsertCopyright();
    void InsertYear();
    void InsertKey();
    void InsertDuration();
    void InsertLyricist();
    void InsertArranger();
    void InsertCommentItalic();
    void InsertComment();
    void InsertSOG();
    void InsertEOG();
    void InsertCommentBox();
    void TocUpdate();
    void TocToText(QModelIndex);
    void InsertNewSong();
    void InsertSong(QString title, QString subtitle, bool compressed, int column);
};

#endif // FORMEDITOR_H
