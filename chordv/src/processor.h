#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "pagesize.h"
#include "formconfig.h"
#include "fontbutton.h"
#include "mainwindow.h"

#include <QString>
#include <QStringList>
#include <QDate>
#include <QMap>

#include <podofo/podofo.h>
#include <podofo/podofo-base.h>

///
/// \brief Processor::Processor is the parent class for chordprocessor, lyricsprocessor
/// and textprocessor. This class is in charge to make PDF common for all of the booklet modes.
/// \param ui1 : a pointer on UI::MainWindow with all the MainWindow graphics elements
/// \param ui2 : a pointer on UI::FormConfig containing a the FormConfig repeated and modified
/// for each type of booklet
///
class Processor : public QObject

{
    Q_OBJECT

    void setVersion(QString version);
public:
    enum Align {left,center,right};
    Processor(Ui::MainWindow *ui1, Ui::FormConfig *ui2  );
    void run();
    ~Processor();
    void process();
    void setCompress(bool compress);
    virtual void setColNumber(int columber);
    virtual void setBpm(double bpm);
    virtual void setRytm(QString rythm);
    virtual bool isChorus(QString text);
    void setCoverMade(bool status){m_covermade=status;}
    bool getCoverMade(){return m_covermade ;}
    virtual void setCoverTitle(QString covertitle);
    QString getCoverTitle(){return m_covertitle;}
    virtual void setCoverSubtitle(QString coversubtitle);
    QString getCoverSubtitle(){return m_coversubtitle;}
    QString getVersion();
    void setSocMode(bool socmode);
    void setRefrain( bool refrain);


    // virtual e section
    virtual void newPage();
    ///
    /// \brief displayPageTitle display the title on each page
    /// \param title : QString for the title of page
    ///
    virtual void displayPageTitle(QString title);
    ///
    /// \brief displayPageSubtitle display the subtitle on each page
    /// \param subtitle : QStgring for the subtitle of page
    ///
    virtual void displayPageSubtitle( QString subtitle )  ;
    ///
    /// \brief displayLyrics display the lyrics
    ///
    virtual void displayLyrics();
    ///
    /// \brief Cover display the cover with title and subtitle
    /// \param title : QString for title
    /// \param subtitle : QString for subtitle
    ///
    virtual void Cover(QString title, QString subtitle,QString version);
    ///
    /// \brief doChords display chords
    ///
    virtual void doChords();
    ///
    /// \brief displayChordsForSong
    ///
    virtual void displayChordsForSong();
    virtual void setColBreak(QString line);
    virtual void doColumnBreak(QString line);
    virtual void save();
    virtual void addFooter();
    ///
    /// \brief makePageNumber display page number on each page
    /// the page number are made following the enumerations :
    ///  - PageNumber { No, Center, Outside }
    ///  - PageStyle { Number, NumberAndTiret, NumberDivideByPageNUmber, NumberAndArrows}
    ///  - Plex { Simplex, Duplex}
    ///
    virtual void makePageNumber();
    virtual PoDoFo::PdfRect PageSize(double left=0, double bottom=0, double width=210, double height=297);
    void includeInfo(QString author="", QString title="",QString subtitle="",QString date=QDate::currentDate().toString("dd/MM/aaaa"));
    virtual int calcColumn();
    virtual int calcLine();
    virtual void FollowingLine();
    ///
    /// \brief includeChorus Include chorus
    /// \param text : chords for the chorus
    ///
    virtual void includeChorus(QString text);
    ///
    /// \brief includeSoc include start of chorus
    ///
    virtual void includeSoc();
    ////
    /// \brief includeEoc include end of chorus
    ///
    virtual void includeEoc();
    ///
    /// \brief includeRefrain include refrain
    /// \param text QString for refrain
    ///
    virtual void includeRefrain(QString text);
    ///
    /// \brief includeSor include Start of Refrain
    ///
    virtual void includeSor();
    ///
    /// \brief includeEor include End of Refrain
    ///
    virtual void includeEor();
    ///
    /// \brief m_category category in config file  (file.conf) Chordbook,LyricsBook,MemoryMode,TextBook
    ///
    virtual QString Category();    
    double mm(int value);

protected:
    ///
    /// \brief m_compress allow to compress lines to fill a page
    ///
    bool m_compress;
    ///
    /// \brief m_covermade true if the cover is made
    ///
    bool m_covermade;

    ///
    /// \brief m_covertitleexist true if there is a cover title is present in doc
    ///
    bool m_covertitleexist;

    ///
    /// \brief m_covertsubtitleexisttrue if there is a subtitlecover is present in doc
    ///
    ///
    bool m_covertsubtitleexist;

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
    QStringList m_subtitle;
    ///
    /// \brief m_title title of song
    ///
    QString m_title;
    ///
    /// \brief m_chorus
    ///
    bool m_chorus;
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
    ///
    /// \brief m_uiconfig a pointer on type of processor include widget
    ///
    Ui::FormConfig *m_uiconfig;
    ///
    /// \brief m_uimainwindow a pointer on mainwindow to get all the common information
    ///
    Ui::MainWindow *m_uimainwindow;

    ///
    /// \brief m_document pointer on document open in creation mode
    ///
    PoDoFo::PdfStreamedDocument *m_document;
    ///
    /// \brief m_mdocument pointer on document open in addition mode
    ///
    PoDoFo::PdfMemDocument *m_mdocument;
    ///
    /// \brief m_page pointer on PdfPage
    ///
    PoDoFo::PdfPage* m_page;
    ///
    /// \brief m_painter pointer on PdfPainter
    ///
    PoDoFo::PdfPainter m_painter;
    ///
    /// \brief m_dimension pointer current dimention
    ///
    PoDoFo::PdfRect *m_dimension;

    ///
    /// \brief m_documentAllocation m_document received a new ( delete to be done )
    ///
    bool m_documentAllocation;
    ///
    /// \brief m_pageAllocation m_page recevived a new ( delete to be done )
    ///
    bool m_pageAllocation;

    ///
    /// \brief m_tocpages number of pages per song ( sorted in stupid alphabetic order)
    ///
    QMap <QString,int> m_tocpages;
    ///
    /// \brief m_toc list of song in incremental order
    ///
    QStringList m_toc;

    ///
    /// \brief m_line y  current line printed
    ///
    int m_line;


    int m_lineindex;
    ///
    /// \brief m_column x current column printed
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

    QString m_projectpath;
    int m_nbrealpages;

    int m_positiontoc;

    ///
    /// \brief m_mode : generic, text, lyrics, memory, chord
    ///
    QString m_mode;

    double TitlePosition();
    double ImagePosition();
    ///
    /// \brief Text
    /// \param doc :
    /// \param text :
    /// \param x : if left it is the start of print, if center it is the center point, it left it is end of print
    /// \param y : the y point
    /// \param fb : ButtonFont containing information about Font, color etc...
    /// \param align : Processor::left Processor::center or Processor::right
    /// \param scale : 1 no scale >1 will grow the default font <1 decrease the default font
    /// \return return the x position of the end of text
    double Text(PoDoFo::PdfDocument *doc,QString text, double x, double y, FontButton *fb, Align align=left, double scale=1);

    double TextInBox(PoDoFo::PdfDocument *doc, QString text, double x, double y, FontButton *fb, Align align=left, double scale=1);
    virtual void NextLine( int num=0);
    virtual int currentColumn();
    virtual int nextColumn( int current);

    ///
    /// \brief LineToc print each line in toc
    /// \param text : text to print
    /// \param width : width limited to print
    /// \param x : x point to print
    /// \param y :  y point to print
    /// \param fb : font button where to find font to print
    /// \param pagenumber : the page number
    /// \return a rectangle of region. Used by annotation link in toc
    ///
    virtual PoDoFo::PdfRect LineToc(QString text, double width, double x, double y, FontButton *fb, int pagenumber);

    int TocColSize();
    void savemem();
    void openExistingFile();
    ///
    /// \brief NbPagesInToc return the number in toc
    /// \return
    ///
    int NbPagesInToc( int nbNormalPages);
    ///
    /// \brief FinishPage replace painter.FinishPage, usefull to add watermark
    /// \param painter painter on the current page
    ///
    void FinishPage(PoDoFo::PdfPainter *painter);
    void addTocAtBegining();
    void addTocAtEnd();
    int FirstPageNumber();
    int NbPageCover();
    ///
    /// \brief memorizeChords memorize Chord for the song in m_BufChords;
    /// \param line the line read
    ///
    ///
    void memorizeChords(QString line);
    QString m_version;
signals:
    void PDFMade( QString file);
    void Error(QString message);
protected:
    ///
    /// \brief addToc add toc
    ///
    virtual void addToc();
    ///
    /// \brief addLinkInToc add link in toc
    ///
    virtual void addLinkInToc();
    void displayChord(QString chord, int &line, int &column,int size,QString lang);
    virtual  void displayRytm();
    virtual void displayBpm();
    bool isColBreak(QString line);
    void BufLyricsNormailisation();
    void addCol(int &col, int num);
    ///
    /// \brief AllocatePage
    ///
    virtual void AllocatePage();

    double m_tempo;
    QString m_time;
    QString m_composer;
    QString m_lyricist;
    QString m_arranger;
    QString m_artist;
    QString m_album;
    QString m_copyright;
    int m_year;
    QString m_duration;
    QString m_key;
    bool m_fatalerror;


    virtual void setDuration(QString duration);
    virtual void setKey(QString key);
    virtual void setYear(int year);
    virtual void setCopyright(QString copyright);
    virtual void setAlbum(QString album);
    virtual void setArtist(QString artist);
    virtual void setArranger(QString arranger);
    virtual void setLyricist(QString lyricist);
    virtual void setComposer(QString composer);

};

#endif // PROCESSOR_H
