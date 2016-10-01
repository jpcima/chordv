#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "pagesize.h"
#include "formconfig.h"
#include "fontbutton.h"

#include <QString>
#include <QStringList>
#include <podofo/podofo.h>
#include <podofo/podofo-base.h>
#include <QDate>


class Processor : public QObject

{
    Q_OBJECT
public:
    enum Align {left,center,right};
    Processor(QString SongText,QString dir, Ui::FormConfig *ui  );
    void run();
    ~Processor();
    void process();
    void setCompress(bool compress);
    void setColNumber(int columber);
    void setCoverMade(bool status){m_covermade=status;}
    bool getCoverMade(){return m_covermade ;}
    void setCoverTitle(QString covertitle);
    QString getCoverTitle(){return m_covertitle;}
    void setCoverSubtitle(QString coversubtitle);
    QString getCoverSubtitle(){return m_coversubtitle;}
    void setSocMode(bool socmode);
    void setRefrain( bool refrain);

    QString keepChords(QString line);

    // virtual e section
    virtual void newPage();
    virtual void displayTitle(QString title );
    virtual void displayPageSubtitle( QString subtitle )  ;
    virtual void displayLyrics();
    virtual void Cover(QString title, QString subtitle);
    virtual void doChords();
    virtual void displayChordsForSong();
    virtual void displayPageTitle();
    virtual void setColBreak();
    virtual void save();
    virtual void addFooter();
    virtual void makePageNumber();
    virtual PoDoFo::PdfRect PageSize(double left=0, double bottom=0, double width=210, double height=297);
    void includeInfo(QString author="", QString title="",QString subtitle="",QString date=QDate::currentDate().toString("dd/MM/aaaa"));
    virtual int calcColumn();
    virtual int calcLine();
    virtual void FollowingLine();
    virtual void includeChorus(QString text);
    ///
    /// \brief m_category category in config file  (file.conf) Chordbook,LyricsBook,MemoryMode,TextBook
    ///
    virtual QString Category();    
    double mm(int value);
private:
    ///
    /// \brief m_compress allow to compress lines to fill a page
    ///
    bool m_compress;
    ///
    /// \brief m_covermade true if the cover is made
    ///
    bool m_covermade;
    ///
    /// \brief m_colnumber number of column if avalaible for the media
    ///
    int m_colnumber;
    ///
    /// \brief m_covertitle : title of the cover
    ///
    QString m_covertitle;
    ///
    /// \brief m_coversubtitle subtile of the cover
    ///
    QString m_coversubtitle;
    ///
    /// \brief m_subtitle subtitle of the cover
    ///
    QString m_subtitle;
    ///
    /// \brief m_title title of song
    ///
    QString m_title;
    ///
    /// \brief m_socmode
    ///
    bool m_socmode;
    ///
    /// \brief m_refrain this is refrain ?
    ///
    bool m_refrain;
    ///
    /// \brief m_file dir where product the output file
    ///
    QString m_file;

    bool m_firstline;

    QString m_text;

    double m_initialhposition;
    Ui::FormConfig *m_uiconfig;

    PoDoFo::PdfStreamedDocument *m_document;
    PoDoFo::PdfMemDocument *m_mdocument;
    PoDoFo::PdfPage* m_page;
    PoDoFo::PdfPainter m_painter;
    PoDoFo::PdfRect *m_dimension;

    bool m_documentAllocation;
    bool m_pageAllocation;

    QMap <QString,int> m_tocpages;


    ///
    /// \brief m_line current line printed
    ///
    int m_line;
    ///
    /// \brief m_column current column printed
    ///
    int m_column;

    ///
    /// \brief m_BufLyrics buffer with lyrics
    ///
    QStringList m_BufLyrics;

    ///
    /// \brief m_BufChords buffer with chords
    ///
    QStringList m_BufChords;

    ///
    /// \brief m_NormalPages pages for annotation links not in toc
    ///
    QList <PoDoFo::PdfObject *> m_NormalPages;

    ///
    /// \brief m_TocPages pages for annotation links in toc
    ///
    QList <PoDoFo::PdfObject *> m_TocPages;

    double TitlePosition();
    double ImagePosition();
    ///
    /// \brief Text
    /// \param text
    /// \param x : if left it is the start of print, if center it is the center point, it left it is end of print
    /// \param y : the y point
    /// \param fb : ButtonFont containing informations about Font, color etc...
    /// \param align : Processor::left Processor::center or Processor::right
    /// \param scale : 1 no scale >1 will grow the default font <1 decrease the default font
    /// \return return the x position of the end of text

    double Text(PoDoFo::PdfDocument *doc,QString text, double x, double y, FontButton *fb, Align align=left, double scale=1);


    virtual void NextLine();
    virtual int currentColumn();
    virtual int nextColumn( int current);
    virtual PoDoFo::PdfRect LineToc(QString text, double width, double x, double y, FontButton *fb, int pagenumber);
    int TocColSize();
    void savemem();
    void openExistingFile();
signals:
    void PDFMade( QString file);
protected:
    virtual void addToc();
    virtual void addLinkInToc();
};

#endif // PROCESSOR_H
