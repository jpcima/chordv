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
    ///
    /// \brief InsertSong Insert so from dialogNewSong
    /// \param title : title of song
    /// \param subtitle : subtitle of song
    /// \param compressed : compressed (true/false)
    /// \param column : number of column ( no output for default 1)
    /// \param time1 : time1 for time1/time2
    /// \param time2 : time2 for time1/time2
    /// \param tempp : beat per minute
    ///
    void InsertSong(QString title, QString subtitle, bool compressed, int column, int time1, int time2,int tempo);
};

#endif // FORMEDITOR_H
