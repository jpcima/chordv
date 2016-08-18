#include "processor.h"



#include <QRegExp>
#include <QDebug>
#include <QFileInfo>

using namespace PoDoFo;


Processor::Processor(QString text, QString file)
{

    m_documentAllocation=false;
    m_pageAllocation=false;
    m_tocindex=-1;
    m_line=0;
    m_column=0;
    QFileInfo fi(file);
    m_file=file.replace(QRegExp("."+fi.completeSuffix()+"$"),".pdf");
    if (m_file.isEmpty()) return;

    m_document = new PdfStreamedDocument(m_file.toStdString().c_str());
    m_dimension = new PdfRect(PageSize());
    m_documentAllocation=true;

    QRegExp NewSongREX("^ *\\{(new_song|ns) *\\} *$");
    QRegExp CompressREX("^ *\\{compress\\} * *$");
    QRegExp ColumnsREX("^ *\\{(?:col|columns): *([^}]*) *\\}");
    QRegExp ColumnBreakREX("^ *\\{(column_break|colb) *\\}");
    QRegExp CoverTitleREX("^ *\\{*(?:covertitle|ct): *([^}]+)\\}");
    QRegExp CoverSubTitleREX("^ *\\{(?:coversubtitle|cs): *([^}]+)\\}");
    QRegExp SubTitleREX("^ *\\{(?:subtitle|st): *([^}])\\}");
    QRegExp TitleREX("^ *\\{(?:title|t): *([^}]*)\\}");
    QRegExp SocREX("^ *\\{(?:soc|start_of_chorus)\\}");
    QRegExp EocREX("^ *\\{(?:eoc|end_of_chorus)\\}");
    QRegExp RefrainREX("^Refrain *: *$");
    QRegExp ChordRex("\\[[^]]+\\]");

    m_compress=false;
    m_socmode=false;
    m_refrain=false;

    QStringList Buf;

    bool first=true;
    setCoverMade(false);

    foreach ( QString line, text.split(QRegExp("\n")) )
    {

        if ( line.contains(NewSongREX) )
            {}
        else if ( line.contains(CompressREX) )
            { setCompress(true); }
        else if ( line.contains(ColumnsREX) )
            { setColNumber(ColumnsREX.cap(1).toInt()); }
        else if ( line.contains(ColumnBreakREX) )
            { setColBreak();}
        //breakCol($pdflyrics,$pagelyrics,\$lyricsline,\$lyricscol,$vspacing,0,$vmargin,$hmargin);
        else if ( line.contains(CoverTitleREX) )
            {  setCoverTitle(CoverTitleREX.cap(1)); }
        else if ( line.contains(CoverSubTitleREX) )
            {  setCoverSubtitle(CoverSubTitleREX.cap(1)); }
        else if ( line.contains(SubTitleREX) )
        {
            QString subtitle=SubTitleREX.cap(1);
            setSubTitle(subtitle);
            displayPageSubtitle(subtitle) ;
            //my ($llx,$lly,$urx,$ury)=$pagelyrics->get_mediabox();
            //$vmargin=$ury-$ury*(19/20-1/70*$subtitley);
        }
        else if ( line.contains(TitleREX) )
        {
              setTitle(TitleREX.cap(1));
//            $subtitley=1;
              printChordsForSong();

//            if ( $AnnotationAuth!~/^$/ )
//            {
//              my ($llx,$lly,$urx,$ury)=$pagechords->get_mediabox();
//              my $ant=$pagechords->annotation();
//              $ant->rect($llx,$ury*19/20,$urx,$ury);
//              $ant->text($AnnotationAuth);
//              $AnnotationAuth="";
//            }
            if ( ! getCoverMade()  )
            {
                 Cover(getCoverTitle(),getCoverSubtitle());
                 setCoverMade(true);
                ;
//                my ($llx, $lly, $urx, $ury) = $TocsChords[0]->get_mediabox;
//                $MaxLine=$lyricsline=($ury-$lly)*190/210;
//                $InfoChords{"InitialLine"}=($ury-$lly)*46/50;
//                $InfoLyrics{"InitialLine"}=($ury-$lly)*46/50;
//                $InfoChords{"l"}=$InfoChords{"InitialLine"};
//                $InfoLyrics{"l"}=$InfoLyrics{"InitialLine"};
//                $InfoChords{"InitialCol"}=Util::convert($Config->{ChordBook}->{MarginHorizontal});
//                $InfoLyrics{"InitialCol"}=Util::convert($Config->{LyricsBook}->{MarginHorizontal});
//                $InfoChords{"c"}=$InfoChords{"InitialCol"};
//                $InfoLyrics{"c"}=$InfoLyrics{"InitialCol"};
                  displayTocTitle();
//            }
              if ( first == false ) doChords();
              newPage();




//            $MaxLine=$lyricsline=($ury-$lly)*190/210;
//            $lyricscol=$llx+Util::convert(${Config}->{LyricsBook}->{MarginHorizontal});
              first=false;
              Buf.clear();
//            $CurrentColor=$Config->{ChordBook}->{NormalColor};
//            $vmargin=Util::convert($Config->{"LyricsBook"}->{MarginVertical});
              displayPageTitle();
//            $vmargin=$ury-$ury*192/200;
              addTitleToc();
              setCompress(false);

        }
        else if ( line.contains(SocREX) )
        {
            Buf<<QObject::tr("Chorus");
            setSocMode(true);
        }
        else if ( line.contains(EocREX) )
        {
            Buf<<QObject::tr("Endchorus");
            setSocMode(false);
        }
        else if ( line.contains(RefrainREX) )
        {
            setRefrain(true);
            Buf<<QObject::tr("Refrain");
        }
        else if   ( line.contains(ChordRex) )
        {

              displayLyrics(line);
              line=keepChords(line);

              QStringList s=line.split("|");
              Buf<<s;
        }
        else if ( first  )
        {
           displayLyrics(line);
        }
    }

}


doChords();
printChordsForSong();

save();
open();
addFooter();
addLinkInToc();
makePageNumber();
save();
}

Processor::~Processor()
{
    if ( m_documentAllocation )
    {
      delete m_document;
      delete m_dimension;
      if (m_pageAllocation) delete m_painter;
    }

    m_documentAllocation=false;
    m_pageAllocation=false;
}



void Processor::setCompress(bool compress)
{
    m_compress=compress;
}

void Processor::setColNumber(int colnumber)
{
    m_colnumber=colnumber;
}

void Processor::setCoverTitle(QString covertitle)
{
    m_covertitle=covertitle;
    includeInfo();
}


void Processor::includeInfo(QString author, QString title,QString subtitle,QString date)
{
   m_document->GetInfo()->SetCreator ( PdfString("Chord V") );
   m_document->GetInfo()->SetAuthor  ( PdfString(author.toStdString()) );
   m_document->GetInfo()->SetTitle   ( PdfString(title.toStdString()) );
   m_document->GetInfo()->SetSubject ( PdfString(subtitle.toStdString()) );
   m_document->GetInfo()->SetKeywords( PdfString(date.toStdString()));
}

int Processor::calcColumn()
{
  return 1 ;
}

int Processor::calcLine()
{
 return 1 ;
}

void Processor::setCoverSubtitle(QString coversubtitle)
{
    m_coversubtitle=coversubtitle;
}

void Processor::setSubTitle(QString subtitle)
{
    m_subtitle=subtitle;
}

void Processor::setTitle(QString title)
{
    m_title=title;
    m_tocindex++;
    m_tocpages<<title;
    m_colnumber=1;
}

void Processor::setSocMode(bool socmode)
{
    m_socmode=socmode;
}

void Processor::setRefrain(bool refrain)
{
    m_refrain=refrain;
}


QString Processor::keepChords(QString line)
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


void Processor::newPage()
{

    m_pageAllocation=true;
    m_page = m_document->CreatePage(*m_dimension);
    if ( ! m_page )  { PODOFO_RAISE_ERROR( ePdfError_InvalidHandle );
        qDebug()<<"error page not well created";
    }
    m_painter=new PdfPainter();
    m_painter->SetPage(m_page);

    PdfFont* pFont;
    pFont = m_document->CreateFont( "Arial" );
    if( !pFont )
       {
           PODOFO_RAISE_ERROR( ePdfError_InvalidHandle );
       }
    pFont->SetFontSize( 18.0 );
    m_painter->SetFont( pFont );
}

void Processor::displayPageSubtitle(QString )
{

}

void Processor::displayLyrics(QString )
{
    //m_painter->DrawText( 56.69, m_page->GetPageSize().GetHeight() - 56.69,line.toLocal8Bit() );

}

void Processor::Cover(QString title, QString subtitle)
{
 Q_UNUSED(title)
 Q_UNUSED(subtitle)
}

void Processor::doChords()
{

}

void Processor::printChordsForSong()
{

}

void Processor::displayPageTitle()
{

}

void Processor::displayTocTitle()
{

}

void Processor::addTitleToc()
{

}

void Processor::setColBreak()
{

}

void Processor::save()
{
    if ( m_pageAllocation)  m_painter->FinishPage();
    if ( m_documentAllocation) m_document->Close();
}

void Processor::open()
{

}

void Processor::addFooter()
{

}

void Processor::addLinkInToc()
{

}

void Processor::makePageNumber()
{

}

PdfRect Processor::PageSize( double left, double bottom, double width, double height )
{
    PdfRect size(left,bottom,width,height);
    qDebug()<<left<<bottom<<width<<height;
    return size;
}

void Processor::FollowingLine()
{

}

QString Processor::Category()
{
    return QString("TextBook");
}
