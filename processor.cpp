#include "processor.h"
#include "ui_formconfig.h"
#include "const.h"

#include <QRegExp>
#include <QDebug>
#include <QFileInfo>


using namespace PoDoFo;


Processor::Processor(QString text, QString file, Ui::FormConfig *ui)
{
    m_uiconfig=ui;
    m_documentAllocation=false;
    m_pageAllocation=false;
    m_line=m_uiconfig->spuPageHeight->getPdfU()- m_uiconfig->spuVerticalMargin->getPdfU();
    m_column=m_uiconfig->spuHorizontalMargin->getPdfU();
    QFileInfo fi(file);
    m_file=file.replace(QRegExp("."+fi.completeSuffix()+"$"),".pdf");
    if (m_file.isEmpty()) return;
    m_document = new PdfStreamedDocument(m_file.toStdString().c_str());
    m_dimension = new PdfRect(PageSize());
    m_documentAllocation=true;
    m_compress=false;
    m_socmode=false;
    m_refrain=false;
    m_text=text;
    m_nbrealpages=0;
}


void Processor::run()
{

    QRegExp NewSongREX("^ *\\{(new_song|ns) *\\} *$",Qt::CaseInsensitive);
    QRegExp CompressREX("^ *\\{compress\\} * *$",Qt::CaseInsensitive);
    QRegExp ColumnsREX("^ *\\{(?:col|columns): *([^}]*) *\\}",Qt::CaseInsensitive);
    QRegExp ColumnBreakREX("^ *\\{(column_break|colb) *\\}",Qt::CaseInsensitive);
    QRegExp CoverTitleREX("^ *\\{*(?:covertitle|ct): *([^}]+)\\}",Qt::CaseInsensitive);
    QRegExp CoverSubTitleREX("^ *\\{(?:coversubtitle|cs): *([^}]+)\\}",Qt::CaseInsensitive);
    QRegExp SubTitleREX("^ *\\{(?:subtitle|st): *([^}]+)\\}",Qt::CaseInsensitive);
    QRegExp TitleREX("^ *\\{(?:title|t): *([^}]*)\\}",Qt::CaseInsensitive);
    QRegExp SocREX("^ *\\{(?:soc|start_of_chorus)\\}",Qt::CaseInsensitive);
    QRegExp EocREX("^ *\\{(?:eoc|end_of_chorus)\\}",Qt::CaseInsensitive);
    QRegExp RefrainREX("^Refrain *: *$",Qt::CaseInsensitive);
    QRegExp ChordRex("\\[[^]]+\\]",Qt::CaseInsensitive);


    setCoverMade(false);

    foreach ( QString line, m_text.split(QRegExp("\n")) )
    {
        if ( line.contains(NewSongREX) )
        { }
        else if ( line.contains(CompressREX) )
        {
            setCompress(true);
        }
        else if ( line.contains(ColumnsREX) )
        {
            setColNumber(ColumnsREX.cap(1).toInt());
        }
        else if ( line.contains(ColumnBreakREX) )
        {
            setColBreak();
        }
        else if ( line.contains(CoverTitleREX) )
        {
            setCoverTitle(CoverTitleREX.cap(1));
        }
        else if ( line.contains(CoverSubTitleREX) )
        {
            setCoverSubtitle(CoverSubTitleREX.cap(1));
        }
        else if ( line.contains(SubTitleREX) )
        {
            displayPageSubtitle(SubTitleREX.cap(1) ) ;
        }
        else if ( line.contains(TitleREX) )
        {
              QString title=TitleREX.cap(1);

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
                 m_nbrealpages=0;
            }

            displayChordsForSong();
            displayLyrics();
            displayTitle(title);
            m_nbrealpages++;

//            $MaxLine=$lyricsline=($ury-$lly)*190/210;
//            $lyricscol=$llx+Util::convert(${Config}->{LyricsBook}->{MarginHorizontal});
              m_BufLyrics.clear();
//            $CurrentColor=$Config->{ChordBook}->{NormalColor};
//            $vmargin=Util::convert($Config->{"LyricsBook"}->{MarginVertical});
              displayPageTitle();
//            $vmargin=$ury-$ury*192/200;
              setCompress(false);
        }
        else if ( line.contains(SocREX) )
        {
            setSocMode(true);
            includeChorus(QObject::tr("Chorus"));
        }
        else if ( line.contains(EocREX) )
        {
            includeChorus(QObject::tr("Endchorus"));
            setSocMode(false);
        }
        else if ( line.contains(RefrainREX) )
        {
            setRefrain(true);
            m_BufLyrics<<QObject::tr("Refrain");
        }
        else if   ( line.contains(ChordRex) )
        {

             if ( m_socmode ) includeChorus(line);
             else m_BufLyrics<<line;

        }
        else
        {
            if ( m_socmode ) includeChorus(line);
            else m_BufLyrics<<line;
        }
    }

doChords();
displayChordsForSong();
displayLyrics();
addToc();
save();
openExistingFile();
addFooter();
makePageNumber();
savemem();
emit PDFMade(tr("Conversion done for %1").arg(m_file));
}

Processor::~Processor()
{
    if ( m_documentAllocation )
    {
      delete m_document;
      delete m_dimension;
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


void Processor::includeChorus( QString )
{

}

void Processor::displayTitle(QString title)
{
    newPage();
    m_NormalPages<<m_page->GetContents();
    m_title=title.replace(QRegExp("^ +"),"");
    m_tocpages[m_title]=1;
    m_colnumber=1;
    m_line=m_uiconfig->spuPageHeight->getPdfU()- m_uiconfig->spuVerticalMargin->getPdfU();
    Text(m_document,title,m_uiconfig->spuPageWidth->getPdfU()/2,
               m_line,
               m_uiconfig->toolButtonTitleFont,center);
    m_firstline=true;
}


void Processor::displayPageSubtitle(QString subtitle)
{
  m_subtitle=subtitle;
  m_line-=m_uiconfig->toolButtonSubtitleFont->getFont().pointSizeF()*1.2;
  Text(m_document,subtitle,m_uiconfig->spuPageWidth->getPdfU()/2,
             m_line,
             m_uiconfig->toolButtonSubtitleFont,center);
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
    if ( m_pageAllocation)
    {
        m_painter.FinishPage();
    }
    m_page = m_document->CreatePage(*m_dimension);
    m_painter.SetPage(m_page);
    m_line=m_uiconfig->spuPageHeight->getPdfU()-m_uiconfig->spuVerticalMargin->getPdfU();
    m_column=m_uiconfig->spuHorizontalMargin->getPdfU();
 }


void Processor::displayLyrics()
{
    if ( m_firstline )
    {
        m_firstline=false;
        m_line-=m_uiconfig->toolButtonNormalFont->getFont().pointSizeF()*3;
        m_initialhposition=m_line;
    }
    foreach (QString text,m_BufLyrics)
    {
        if ( ! text.isEmpty() )
        {
            text.replace(QRegExp("\\[[^]]+\\]"),"") ;
            Text(m_document,text,m_column,m_line,m_uiconfig->toolButtonNormalFont);
        }
        NextLine();
    }
}

void Processor::NextLine()
{
    if ( m_line - m_uiconfig->toolButtonNormalFont->getFont().pointSizeF()*1.2 > m_uiconfig->spuVerticalMargin->getPdfU())
        m_line-=m_uiconfig->toolButtonNormalFont->getFont().pointSizeF()*1.2;
    else if ( currentColumn() < m_colnumber )
      {
        m_column = nextColumn( currentColumn() ) ;
        m_line=m_initialhposition;
      }
    else
    {
        if (m_tocpages.count() != 0)
            m_tocpages[m_tocpages.keys().last()]++;
        newPage();
    }
}


int Processor::currentColumn()
{
  int c=1;
  while (c * m_uiconfig->spuPageWidth->getPdfU()/m_colnumber < m_column ) c++;
  return c-1;
}

int Processor::nextColumn( int colnumber)
{
    return ( m_uiconfig->spuPageWidth->getPdfU()*(colnumber+1)/m_colnumber +m_uiconfig->spuHorizontalMargin->getPdfU());
}

void Processor::Cover(QString title, QString subtitle)

{

        m_pageAllocation=true;
        QString image=m_uiconfig->toolButtonCoverImage->getImage();
        QColor backgroundcolor=QColor(m_uiconfig->toolButtonCoverFont->getBackgroundColor());
        m_page= m_document->CreatePage(*m_dimension);
        m_painter.SetPage(m_page);
        m_painter.SetColor(backgroundcolor.redF(),backgroundcolor.greenF(),backgroundcolor.blueF());
        m_painter.Rectangle(0,0,m_uiconfig->spuPageWidth->getPdfU(),m_uiconfig->spuPageHeight->getPdfU());
        m_painter.Fill(true);
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
            m_painter.DrawImage(100,100,pdfi,scale);
          }

          double posx=m_uiconfig->spuPageWidth->getPdfU()/2;
          double posy=TitlePosition();
          double x2=Text(m_document,title,posx,posy,m_uiconfig->toolButtonCoverFont,center);
          PdfFont *pfont=m_document->CreateFont(m_uiconfig->toolButtonCoverFont->getFont().family().toLatin1());
          PdfString str(subtitle.toLatin1());
          pfont->SetFontSize(m_uiconfig->toolButtonCoverFont->getFont().pointSize()*0.5);
          pfont->SetUnderlined(m_uiconfig->toolButtonCoverFont->getFont().underline());
          pfont->SetStrikeOut(m_uiconfig->toolButtonCoverFont->getFont().strikeOut());
          double widthtext=pfont->GetFontMetrics()->StringWidth(subtitle.toLatin1());
          Text(m_document,subtitle,x2-widthtext/2,posy-m_uiconfig->toolButtonCoverFont->getFont().pointSize()*0.5,m_uiconfig->toolButtonCoverFont,right,0.5);
          m_painter.FinishPage();
}

void Processor::doChords()
{

}

void Processor::displayChordsForSong()
{

}

void Processor::displayPageTitle()
{

}


void Processor::setColBreak()
{

}

void Processor::save()
{
    if ( m_pageAllocation)
    {
        m_painter.FinishPage();
    }
    if ( m_documentAllocation)
    {
       m_document->Close();
    }
}

void Processor::savemem()
{
       int i= m_mdocument->GetPageCount();
       qDebug()<<m_file;
       QFile  file(m_file);
       file.remove();
       m_mdocument->Write(m_file.toStdString().c_str());

        //delete m_mdocument;
}

void Processor::openExistingFile()
{
    m_mdocument = new PdfMemDocument(m_file.toStdString().c_str());
    int i=m_mdocument->GetPageCount();
}

void Processor::addFooter()
{

}

int Processor::TocColSize()
{
    if ( m_uiconfig->comboBoxTocColumnNumber->currentIndex() == 0 ) return m_uiconfig->spuPageWidth->getPdfU()-2*m_uiconfig->spuHorizontalMargin->getPdfU()  ;
    else if ( m_uiconfig->comboBoxTocColumnNumber->currentIndex() == 1 )  return m_uiconfig->spuPageWidth->getPdfU()/2-2*m_uiconfig->spuHorizontalMargin->getPdfU() ;
    else return m_uiconfig->spuPageWidth->getPdfU()/3-2*m_uiconfig->spuHorizontalMargin->getPdfU() ;
}

void Processor::addLinkInToc()
{

}


int Processor::NbPagesInToc(int nbpages)
{
    double heightneed=nbpages*(m_uiconfig->comboBoxTocVerticalSpacing->currentText().toDouble()+1)
            *m_uiconfig->toolButtonTocFont->getFont().pointSizeF()/m_uiconfig->comboBoxTocColumnNumber->currentText().toInt();
    double nbpagesneed=heightneed/(m_uiconfig->spuPageHeight->getPdfU() - m_uiconfig->toolButtonTitleFont->getFont().pointSizeF()*2.4
                        - 2*m_uiconfig->spuVerticalMargin->getPdfU() );
    int nb=nbpagesneed+1;
    return nb;
}

void Processor::addToc()
{
    if ( m_uiconfig->comboBoxTocPosition->currentIndex()==0) return;
    int pagenumber=0;
    PdfPage *toc;
    int position;
    m_line=m_uiconfig->spuPageHeight->getPdfU()- m_uiconfig->spuVerticalMargin->getPdfU();
    if ( m_uiconfig->comboBoxTocPosition->currentIndex()==1 )
    {
         position= m_covermade ?1:0;
         toc=m_document->InsertPage(*m_dimension,position);
    }
    else
    {
        toc=m_document->CreatePage(*m_dimension);
    }
    m_TocPages<<toc->GetContents();
    pagenumber++;
    m_painter.SetPage(toc);
    bool ok;
    double verticalspacing=m_uiconfig->comboBoxTocVerticalSpacing->currentText().toDouble(&ok);
    if ( !ok ) verticalspacing=1;
    verticalspacing*=1.2;

    Text(m_document,QObject::tr("Table of content"),m_uiconfig->spuPageWidth->getPdfU()/2,m_line,m_uiconfig->toolButtonTitleFont,center);
    m_line-=m_uiconfig->toolButtonTitleFont->getFont().pointSizeF()*2.4 ;
    int lineinit=m_line;
    int colinit=m_uiconfig->spuHorizontalMargin->getPdfU();
    int currentcol=0;
    int titlenumber=0;
    foreach ( QString title, m_tocpages.keys())
        {
         int nbpagesintoc=NbPagesInToc(m_nbrealpages);
         PdfRect rect=LineToc(title,TocColSize(),colinit,m_line,m_uiconfig->toolButtonTocFont,pagenumber+nbpagesintoc);
         PdfAnnotation *a=toc->CreateAnnotation(ePdfAnnotation_Link,rect);
         a->SetContents(tr("Go to page %1").arg(pagenumber+nbpagesintoc).toStdString().c_str());
         PdfDestination dest(m_document->GetPage(pagenumber));
         a->SetDestination(dest);
         a->SetFlags( ePdfAnnotationFlags_Hidden);
         pagenumber+=m_tocpages[title];
         if ( m_line - m_uiconfig->toolButtonTocFont->getFont().pointSizeF()*verticalspacing > m_uiconfig->spuVerticalMargin->getPdfU())
             m_line-=m_uiconfig->toolButtonTocFont->getFont().pointSizeF()*verticalspacing;
         else if ( m_uiconfig->comboBoxTocColumnNumber->currentIndex() > currentcol  )
         {
             currentcol=1;
             m_line=lineinit;
             colinit=colinit+TocColSize();
         }
         else
         {
             m_line=lineinit;
             colinit=m_uiconfig->spuHorizontalMargin->getPdfU();
             m_tocpages[m_tocpages.keys().last()]++;
             if ( m_pageAllocation)  m_painter.FinishPage();
             if ( m_uiconfig->comboBoxTocPosition->currentIndex()==1 )
             {
                  position++;
                  toc=m_document->InsertPage(*m_dimension,position);
             }
             else
             {
                 toc=m_document->CreatePage(*m_dimension);
             }
             m_painter.SetPage(toc);
             m_line=m_uiconfig->spuPageHeight->getPdfU()-m_uiconfig->spuVerticalMargin->getPdfU();
             m_column=m_uiconfig->spuHorizontalMargin->getPdfU();
             m_TocPages<<toc->GetContents();
         }
         titlenumber++;
    }
    m_painter.FinishPage();
}

void Processor::makePageNumber()
{
    Const::PageNumber pagetype= Const::getPageNumber(m_uiconfig->comboBoxPageNumber->currentIndex());
    if (pagetype == Const::No )  return ;
    int firstpage=getCoverMade() ? 2:1;
    int totalpage=m_mdocument->GetPageCount()-firstpage+1;
    int nbpage=1;
    for ( int p=firstpage-1; p<=totalpage ; p++)
    {
        PdfPage *pdfp = m_mdocument->GetPage(p);
        m_painter.SetPage(pdfp);
        QString pattern;
        if ( m_uiconfig->comboBoxPageNumberStyle->currentIndex()==0)
            pattern="%1";
        else if ( m_uiconfig->comboBoxPageNumberStyle->currentIndex()==1)
            pattern="- %1 -";
        else pattern=QString("%%1/%1").arg(totalpage);
        QString page=QString(pattern).arg(nbpage);

        nbpage++;
        int x;
        int y;
        if (  m_uiconfig->spuHorizontalMargin->getPdfU() < m_uiconfig->toolButtonPageNumberFont->getFont().pointSizeF()*3 )
            y= m_uiconfig->toolButtonPageNumberFont->getFont().pointSizeF()*3;
        else y =  m_uiconfig->spuHorizontalMargin->getPdfU()-m_uiconfig->toolButtonPageNumberFont->getFont().pointSizeF()*3 ;
        if ( pagetype == Const::Center)
            x = m_uiconfig->spuPageWidth->getPdfU()/2;
        else
            x =m_uiconfig->spuPageWidth->getPdfU()-m_uiconfig->spuHorizontalMargin->getPdfU();
        if  ( pagetype == Const::Center ) Text(m_mdocument,page,x,y,m_uiconfig->toolButtonPageNumberFont,center);
        else Text(m_mdocument,page,x,y, m_uiconfig->toolButtonPageNumberFont,left);
        double  widthtext=m_uiconfig->toolButtonPageNumberFont->getFont().pointSizeF()*page.length();
        PdfRect rect(x,y,widthtext,m_uiconfig->toolButtonPageNumberFont->getFont().pointSizeF());
        PdfAnnotation *a=pdfp->CreateAnnotation(ePdfAnnotation_Link,rect);
        a->SetContents(tr("Go to table of content").toStdString().c_str());
        PdfDestination dest(m_document->GetPage(1));
        a->SetDestination(dest);
        a->SetFlags( ePdfAnnotationFlags_Hidden);

        m_painter.FinishPage();
    }
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


double  Processor::Text( PdfDocument *doc, QString text, double x, double y, FontButton *fb ,Align align, double scale)
{
    double end=0;
    PdfFont *pfont=doc->CreateFont(fb->getFont().family().toLatin1());
    PdfString str(text.toLatin1());
    pfont->SetFontSize(fb->getFont().pointSize()*scale);
    pfont->SetUnderlined(fb->getFont().underline());
    pfont->SetStrikeOut(fb->getFont().strikeOut());
    m_painter.SetFont(pfont);
    double widthtext=pfont->GetFontMetrics()->StringWidth(str);
    m_painter.SetColor(fb->getTextColor().redF(),fb->getTextColor().greenF(),fb->getTextColor().blueF());
    m_painter.Fill(true);
    if (! text.isEmpty())
    {
        if ( align == right )  x-=widthtext*scale;
        else if ( align == center ) x-=widthtext*scale/2;
        else if (align == left ) ;
        end=x+widthtext;
        m_painter.DrawText(x,y,str);
    }
    return end;
}

PdfRect Processor::LineToc(QString text, double width, double x, double y, FontButton *fb, int pagenumber)
{
    QRegExp space("^ +");
    text.replace(space,"").append(" ");
    PdfFont *pfont=m_document->CreateFont(fb->getFont().family().toLatin1());
    pfont->SetFontSize(fb->getFont().pointSize());
    pfont->SetUnderlined(fb->getFont().underline());
    pfont->SetStrikeOut(fb->getFont().strikeOut());
    m_painter.SetFont(pfont);
    QString point(" ");
    bool odd=true;
    while ( pfont->GetFontMetrics()->StringWidth(QString("%1%2    ").arg(text,point).toLatin1())> width)
    {
        text.chop(1);
    }
    //text=QString("%1%2%3").arg(text,point).arg(page);
    while ( pfont->GetFontMetrics()->StringWidth(QString("%1%2    ").arg(text,point).toLatin1())<= width)
    {
        odd=odd?false:true;
        QString c;
        if ( m_uiconfig->comboBoxTocSpaceCharacter->currentIndex()==0 ) c=".";
        else if ( m_uiconfig->comboBoxTocSpaceCharacter->currentIndex()==1 ) c="-";
        else c=" ";
        if ( odd ) point+=c;
        else point+=" ";
    }
    text=QString("%1%2    ").arg(text,point);
    m_painter.SetColor(fb->getTextColor().redF(),fb->getTextColor().greenF(),fb->getTextColor().blueF());
    m_painter.Fill(true);
    m_painter.DrawText(x,y,PdfString(text.toLatin1()));
    PdfRect rect(x,y,x+width+fb->getFont().pointSizeF(),fb->getFont().pointSizeF());
    Text(m_document,QString("%1").arg(pagenumber),x+width+fb->getFont().pointSize(),y,fb,right);
    return rect;
}
