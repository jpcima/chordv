#include "abstbook.h"
#include <QRegExp>

AbstBook::AbstBook()
{
    m_compress=false;
    m_socmode=false;
    m_refrain=false;
            ;
}


void AbstBook::setCompress(bool compress)
{
    m_compress=compress;
}

void AbstBook::setColNumber(int colnumber)
{
    m_colnumber=colnumber;
}

void AbstBook::setCoverTitle(QString covertitle)
{
    m_covertitle=covertitle;
    includeInfo();
}


void AbstBook::includeInfo()
{
//        my ($pdf,$type)=@_;
//        my %info = $pdf->info (
//            'filename'     => "$file.pdf",
//            'Author'       => $Config->{general}->{creator},
//            'Title'        =>  $covertitle,
//            'Creator'  	   =>'chordIII.pl',
//            'Subject'      =>  $type=~/ChordBook/i ? __ sprintf ("%s  Chord book of %s","$covertitle"):  __ sprintf ("%s  Lyrics and chords book of %s","$covertitle") ,
//            'CreationDate' => [ localtime ]
//            )

}

void AbstBook::setCoverSubtitle(QString coversubtitle)
{
    m_coversubtitle=coversubtitle;
}

void AbstBook::setSubTitle(QString subtitle)
{
    m_subtitle=subtitle;
}

void AbstBook::setTitle(QString title)
{
    m_subtitle=title;
}

void AbstBook::setSocMode(bool socmode)
{
    m_socmode=socmode;
}

void AbstBook::setRefrain(bool refrain)
{
    m_refrain=refrain;
}


QString AbstBook::keepChords(QString line)
{
   // suppress before first []
   line.replace(QRegExp("^[^[]*"),"") ;
   // suppress end  after last  []
   line.replace(QRegExp("[^]]*$"),"");
   // suppress after all []
   line.replace(QRegExp("\\[([^]]+)\\][^[]+"),"\\1");
   // suppress (V)
    line.replace(QRegExp("\\(([^)]*)\\)"),"");
    // line=&Translate(line);
   line.replace("][","|");
   line.replace("]","");
   line.replace("[","");
   return line;
}
