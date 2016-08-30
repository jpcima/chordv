#include "processor.h"
#include "ui_formconfig.h"
#include <QRegExp>
#include <QDebug>
#include <QFileInfo>


using namespace PoDoFo;


Processor::Processor(QString text, QString file, Ui::FormConfig *ui)
{
    m_uiconfig=ui;
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
              QString title=TitleREX.cap(1);
              setTitle(title);
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
    m_page= m_document->CreatePage(*m_dimension);
    m_painter=new PdfPainter;
    double x=m_uiconfig->spuPageWidth->getPdfU()/2;
    double y=m_uiconfig->spuPageHeight->getPdfU()-m_uiconfig->toolButtonTitleFont->getFont().pointSizeF()*2;
    QFont font(m_uiconfig->toolButtonTitleFont->getFont());
    PdfFont *pfont=m_document->CreateFont(font.family().toLatin1());
    m_painter->SetFont(pfont);
    pfont->SetFontSize(font.pointSize());
    pfont->SetUnderlined(font.underline());
    pfont->SetStrikeOut(font.strikeOut());
    m_painter->SetFont(pfont);
    QColor fontcolor=m_uiconfig->toolButtonTitleFont->getTextColor();
    m_painter->SetColor(fontcolor.redF(),fontcolor.greenF(),fontcolor.blueF());
    Text(title,x,y,m_uiconfig->toolButtonTitleFont,center);


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

        QString image=m_uiconfig->toolButtonCoverImage->getImage();
        QFont font(m_uiconfig->toolButtonCoverFont->getFont());
        QColor  fontcolor=QColor(m_uiconfig->toolButtonCoverFont->getTextColor());
        QColor backgroundcolor=QColor(m_uiconfig->toolButtonCoverFont->getBackgroundColor());
        m_page= m_document->CreatePage(*m_dimension);
        m_painter=new PdfPainter;
        m_painter->SetPage(m_page);
        m_painter->SetColor(backgroundcolor.redF(),backgroundcolor.greenF(),backgroundcolor.blueF());
        m_painter->Rectangle(0,0,m_uiconfig->spuPageWidth->getPdfU(),m_uiconfig->spuPageHeight->getPdfU());
        m_painter->Fill(true);
        if (! image.isEmpty())
          {
            QPixmap pix(image);
            double maxh=m_uiconfig->spuPageHeight->getPdfU()/4.0;
            double maxw=m_uiconfig->spuPageWidth->getPdfU()*0.75;
            double imageh=pix.size().height();
            double imagew=pix.size().width();
            double scale1,scale2;
            scale1=maxh/imageh;
            scale2=maxw/imagew;
            double scale=scale1>scale2?scale1:scale2;
            PdfImage *pdfi = new PdfImage(m_document);
            pdfi->SetImageChromaKeyMask(0,0,0);
            pdfi->LoadFromFile(image.toLatin1());
            m_painter->DrawImage(100,100,pdfi,scale);
          }

          PdfFont *pfont=m_document->CreateFont(font.family().toLatin1());
          pfont->SetFontSize(font.pointSize());
          pfont->SetUnderlined(font.underline());
          pfont->SetStrikeOut(font.strikeOut());
          m_painter->SetFont(pfont);
          m_painter->SetColor(fontcolor.redF(),fontcolor.greenF(),fontcolor.blueF());
          PdfString stringtitle(title.toLatin1());
          double widthtitle=pfont->GetFontMetrics()->StringWidth(stringtitle);
          double posx=(m_uiconfig->spuPageWidth->getPdfU()-widthtitle)/2;
          double posy=TitlePosition();
         Text(title,posx,posy,m_uiconfig->toolButtonCoverFont);
         if ( ! title.isEmpty())
              m_painter->DrawText(posx,posy,stringtitle);
          pfont->SetFontSize(font.pointSize()*8/10);
          PdfString stringsubtitle(subtitle.toLatin1());
          double widthsubtitle=pfont->GetFontMetrics()->StringWidth(stringsubtitle);
          posx=posx+widthtitle-widthsubtitle;
          if ( ! subtitle.isEmpty())
              m_painter->DrawText(posx,posy-1.5*font.pointSize(),stringsubtitle);
          m_painter->FinishPage();
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
    PdfRect size(mm(left),mm(bottom),mm(width),mm(height));
    return size;
}

void Processor::FollowingLine()
{

}

QString Processor::Category()
{
    return QString("TextBook");
}


double Processor::mm(int value)
{
    return (value*72/25.4);
}



double Processor::TitlePosition()
{
    double factor;
    if ( m_uiconfig->comboBoxTitlePosition->currentIndex()==0) factor=2/3.0;
    else if ( m_uiconfig->comboBoxTitlePosition->currentIndex()==1) factor=1/2.0;
    else factor=1/3.0;
    return m_uiconfig->spuPageHeight->getPdfU()*factor;
}

double Processor::ImagePosition()
{
    double factor;
    if ( m_uiconfig->comboBoxTitlePosition->currentIndex()==0) factor=1/3.0;
    else if ( m_uiconfig->comboBoxTitlePosition->currentIndex()==1) factor=3/4.0;
    else factor=2/3.0;
    return m_uiconfig->spuPageHeight->getPdfU()*factor;
}


void Processor::Text( QString text, double x, double y, FontButton *fb ,Align align)
{
    PdfFont *pfont=m_document->CreateFont(fb->getFont().family().toLatin1());
    PdfString str(text.toLatin1());
    double widthtext=pfont->GetFontMetrics()->StringWidth(str);
    pfont->SetFontSize(fb->getFont().pointSize());
    pfont->SetUnderlined(fb->getFont().underline());
    pfont->SetStrikeOut(fb->getFont().strikeOut());
    m_painter->SetFont(pfont);
    m_painter->SetColor(fb->getTextColor().redF(),fb->getTextColor().greenF(),fb->getTextColor().blueF());
    if (! text.isEmpty())
    {
        if ( align == right )  x-=widthtext;
        else x-=widthtext/2;
        m_painter->DrawText(x,y,str);
    }
}
