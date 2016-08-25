#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "pagesize.h"
#include "formconfig.h"
#include <QString>
#include <QStringList>
#include <podofo/podofo.h>
#include <QDate>

class Processor
{
public:
    Processor(QString SongText,QString dir, Ui::FormConfig *ui  );
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
    void setSubTitle(QString covertitle);
    void setTitle(QString title );
    void setSocMode(bool socmode);
    void setRefrain( bool refrain);

    QString keepChords(QString line);
    virtual void newPage();
    // virtual pure section
    virtual void displayPageSubtitle( QString subtitle )  ;
    virtual void displayLyrics(QString line);
    virtual void Cover(QString title, QString subtitle);
    virtual void doChords();
    virtual void printChordsForSong();
    virtual void displayPageTitle();
    virtual void displayTocTitle();
    virtual void addTitleToc();
    virtual void setColBreak();
    virtual void save();
    virtual void open();
    virtual void addFooter();
    virtual void addLinkInToc();
    virtual void makePageNumber();
    virtual PoDoFo::PdfRect PageSize(double left=0, double bottom=0, double width=210, double height=297);
    void includeInfo(QString author="", QString title="",QString subtitle="",QString date=QDate::currentDate().toString("dd/MM/aaaa"));
    virtual int calcColumn();
    virtual int calcLine();
    virtual void FollowingLine();
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
    Ui::FormConfig *m_uiconfig;

    PoDoFo::PdfStreamedDocument *m_document;
    PoDoFo::PdfPage* m_page;
    PoDoFo::PdfPainter *m_painter;
    PoDoFo::PdfRect *m_dimension;

    bool m_documentAllocation;
    bool m_pageAllocation;

    QStringList m_tocpages;
    int m_tocindex;

    ///
    /// \brief m_line current line printed
    ///
    int m_line;
    ///
    /// \brief m_column current column printed
    ///
    int m_column;




    double TitlePosition();
    double red(QColor value);
    double green(QColor value);
    double blue(QColor value);
    double ImagePosition();
};

#endif // PROCESSOR_H
