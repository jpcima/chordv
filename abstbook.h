#ifndef ABSTBOOK_H
#define ABSTBOOK_H
#include <QString>
class ChordBook;

class AbstBook
{
public:
    AbstBook();
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
    void includeInfo();
    QString keepChords(QString line);
    // virtual pure section
    virtual void displayPageSubtitle( QString subtitle ) = 0 ;
    virtual void displayLyrics(QString line)=0;
    virtual void Cover(QString title, QString subtitle)=0;
    virtual void doChords()=0;
    virtual void printChordsForSong()=0;
private:
    bool m_compress;
    bool m_covermade;
    int m_colnumber;
    QString m_covertitle;
    QString m_coversubtitle;
    QString m_subtitle;
    QString m_title;
    bool m_socmode;
    bool m_refrain;



};

#endif // ABSTBOOK_H
