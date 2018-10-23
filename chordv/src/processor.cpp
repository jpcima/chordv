#include "processor.h"
#include "ui_formconfig.h"
#include "ui_mainwindow.h"
#include "const.h"
#include "chord.h"
#include "chordutil.h"

#include <QRegExp>
#include <QDebug>
#include <QFileInfo>
#include <QtMath>
#include <QDir>
#include <QStringList>
#include <QSqlQuery>
#include <QMessageBox>

using namespace PoDoFo;



Processor::Processor(Ui::MainWindow *ui1, Ui::FormConfig *ui2)
{
    m_uiconfig=ui2;
    m_fatalerror=true;
    m_uimainwindow=ui1;
    m_projectpath=ui1->labelNameDirProject->text();
    m_documentAllocation=false;
    m_file=QString("%1/%2_%3.pdf")
            .arg(m_uimainwindow->labelNameDirProject->text())
            .arg(m_uimainwindow->labelNameProjectName->text())
            .arg(m_uiconfig->lineEditOutFile->text());

    m_pageAllocation=false;
    m_line=m_uiconfig->spuPageHeight->getPdfU()- m_uiconfig->spuVerticalMargin->getPdfU();
    m_column=m_uiconfig->spuHorizontalMargin->getPdfU();
    if (m_file.isEmpty()) return;

    QFile file(m_file);
    file.open(QIODevice::ReadWrite);
    file.close();
    QFileInfo fi(m_file);
    if ( !fi.isWritable() )  return;
    m_document = new PdfStreamedDocument(m_file.toStdString().c_str());
    m_dimension = new PdfRect(PageSize(0,0,m_uiconfig->spuPageWidth->getPdfU(),m_uiconfig->spuPageHeight->getPdfU()));
    m_documentAllocation=true;
    m_compress=false;
    m_chorus=false;
    m_refrain=false;
    m_text=m_uimainwindow->textEditCho3File->document()->toPlainText();
    m_nbrealpages=0;
    m_mode="generic";
    m_covertitleexist=false;
    m_covertsubtitleexist=false;
    m_time="4/4";
    m_tempo=120;
    m_subtitle.clear();
    m_fatalerror=false;
}


void Processor::run()
{

    if (m_fatalerror)
       {
        emit Error(tr("File %1 is not writable. Save as origin file in a writable place before to make a pdf").arg(m_file));
        return;
       }
    QRegExp NewSongREX("^ *\\{(new_song|ns) *\\} *$",Qt::CaseInsensitive);
    QRegExp CompressREX("^ *\\{compress\\} * *$",Qt::CaseInsensitive);
    QRegExp ColumnsREX("^ *\\{(?:col|columns): *([^}]*) *\\}",Qt::CaseInsensitive);
    QRegExp ColumnBreakREX("^ *\\{(column_break|colb)(:(text|lyrics))? *\\}",Qt::CaseInsensitive);
    QRegExp CoverTitleREX("^ *\\{*(?:cover_title|ct): *([^}]+)\\}",Qt::CaseInsensitive);
    QRegExp CoverSubTitleREX("^ *\\{(?:cover_subtitle|cs): *([^}]+)\\}",Qt::CaseInsensitive);
    QRegExp SubTitleREX("^ *\\{(?:subtitle|st): *([^}]+)\\}",Qt::CaseInsensitive);
    QRegExp TitleREX("^ *\\{(?:title|t): *([^}]*)\\}",Qt::CaseInsensitive);
    QRegExp SocREX("^ *\\{(?:soc|start_of_chorus)\\}",Qt::CaseInsensitive);
    QRegExp EocREX("^ *\\{(?:eoc|end_of_chorus)\\}",Qt::CaseInsensitive);
    QRegExp SorREX("^ *\\{(?:sor|start_of_refrain)\\}",Qt::CaseInsensitive);
    QRegExp EorREX("^ *\\{(?:eor|end_of_refrain)\\}",Qt::CaseInsensitive);
    QRegExp DefineRex("^\\{define: *([^ ]+) +base-fret +(\\d+) +frets +(\\d+|x) +(\\d+|x) +(\\d+|x) +(\\d+|x) +(\\d+|x) +(\\d+|x)([^}]*)\\}",Qt::CaseInsensitive);
    QRegExp ChordREX("\\[[^]]+\\]",Qt::CaseInsensitive);
    QRegExp TempoREX("^ *\\{(?:tempo): *([^}]*) *\\}",Qt::CaseInsensitive);
    QRegExp TimeREX("^ *\\{(?:time): *([^}]*) *\\}",Qt::CaseInsensitive);
    QRegExp ComposerRex("^ *\\{(?:composer): *([^}]*) *\\}",Qt::CaseInsensitive);
    QRegExp LyricistRex("^ *\\{(?:lyricist): *([^}]*) *\\}",Qt::CaseInsensitive);
    QRegExp ArrangerRex("^ *\\{(?:arranger): *([^}]*) *\\}",Qt::CaseInsensitive);
    QRegExp ArtistRex("^ *\\{(?:artist): *([^}]*) *\\}",Qt::CaseInsensitive);
    QRegExp AlbumRex("^ *\\{(?:album): *([^}]*) *\\}",Qt::CaseInsensitive);
    QRegExp CopyrightRex("^ *\\{(?:copyright): *([^}]*) *\\}",Qt::CaseInsensitive);
    QRegExp YearRex("^ *\\{(?:year): *([^}]*) *\\}",Qt::CaseInsensitive);
    QRegExp KeyRex("^ *\\{(?:key): *([^}]*) *\\}",Qt::CaseInsensitive);
    QRegExp DurationRex("^ *\\{(?:key): *([^}]*) *\\}",Qt::CaseInsensitive);
    QRegExp VersionRex("^ *\\{(?:version|v): *([^}]*) *\\}",Qt::CaseInsensitive);
    setCoverMade(false);
    m_lineindex=0;
    foreach ( QString line, m_text.split(QRegExp("\n")) )
    {
        m_lineindex++;
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
        else if ( line.contains(TempoREX))
        {
            setBpm(TempoREX.cap(1).toDouble());
        }
        else if ( line.contains(TimeREX))
        {
            setRytm(TimeREX.cap(1));
        }
        else if ( line.contains(ComposerRex))
        {
            setComposer(ComposerRex.cap(1));
        }
        else if ( line.contains(LyricistRex))
        {
            setLyricist(LyricistRex.cap(1));
        }
        else if ( line.contains(ArrangerRex))
        {
            setArranger(ArtistRex.cap(1));
        }
        else if ( line.contains(ArtistRex))
        {
            setArtist(ArtistRex.cap(1));
        }
        else if ( line.contains(AlbumRex))
        {
            setAlbum(AlbumRex.cap(1));
        }
        else if ( line.contains(CopyrightRex))
        {
            setCopyright(CopyrightRex.cap(1));
        }
        else if ( line.contains(YearRex))
        {
            setYear(YearRex.cap(1).toInt());
        }
        else if ( line.contains(KeyRex))
        {
            setKey(KeyRex.cap(1));
        }
        else if ( line.contains(DurationRex))
        {
            setDuration(DurationRex.cap(1));
        }
        else if ( line.contains(ColumnBreakREX) )
        {

            setColBreak(line);
        }
        else if ( line.contains(CoverTitleREX) )
        {
            setCoverTitle(CoverTitleREX.cap(1));
        }
        else if (line.contains(VersionRex) )
        {
            setVersion(VersionRex.cap(1));
        }
        else if ( line.contains(CoverSubTitleREX) )
        {
            setCoverSubtitle(CoverSubTitleREX.cap(1));
        }
        else if ( line.contains(SubTitleREX) )
        {
            m_subtitle<<SubTitleREX.cap(1);
        }
        else if (line.contains(DefineRex))
        {
            QString chordname=DefineRex.cap(1);
            QString basefret=DefineRex.cap(2);
            QString fret=QString("%1 %2 %3 %4 %5 %6").arg(DefineRex.cap(3))
                    .arg(DefineRex.cap(4)).arg(DefineRex.cap(5)).arg(DefineRex.cap(6))
                    .arg(DefineRex.cap(7)).arg(DefineRex.cap(8));
            QSqlQuery select (QString("SELECT * FROM chords WHERE Name='%1' AND Approved=1 ").arg(chordname));
            if (select.next())
            {
                if ( basefret != "0" )
                {
                     QString newchordname=QString("%1(%2)").arg(chordname).arg(ChordUtil::toRomain(basefret.toInt()));
                     QSqlQuery select (QString("SELECT * FROM chords WHERE Name='%1'").arg(newchordname));
                     if ( ! select.next())
                     {
                         QSqlQuery query(QString("INSERT INTO chords (Name, Value, Approved) VALUES ('%1','%2 %3',0)").arg(newchordname).arg(basefret).arg(fret));

                     }
                }
            }
            else
            {
                QSqlQuery select (QString("SELECT * FROM chords WHERE Name='%1' AND Approved=0 ").arg(chordname));
                if (  ! select.next() )
                QSqlQuery query(QString("INSERT INTO chords (Name, Value, Approved) VALUES ('%1','%2 %3',0)").arg(chordname).arg(basefret).arg(fret));
            }


        }
        else if ( line.contains(TitleREX) )
        {

//            if ( $AnnotationAuth!~/^$/ )
//            {
//              my ($llx,$lly,$urx,$ury)=$pagechords->get_mediabox();
//              my $ant=$pagechords->annotation();
//              $ant->rect($llx,$ury*19À tire d'elles/20,$urx,$ury);
//              $ant->text($AnnotationAuth);
//              $AnnotationAuth="";
//            }

            if ( m_covertitleexist && ! getCoverMade()  && m_uiconfig->checkBoxCover->isChecked())
            {
                 Cover(getCoverTitle(),getCoverSubtitle(),getVersion());
                 setCoverMade(true);
                 m_nbrealpages=0;
            }
            else
            {
                foreach ( QString title,m_subtitle) displayPageSubtitle(title) ;
                displayRytm();
                displayBpm();
            }
            displayChordsForSong();
            displayLyrics();
            m_nbrealpages++;
            displayPageTitle(TitleREX.cap(1));



//            $MaxLine=$lyricsline=($ury-$lly)*190/210;
//            $lyricscol=$llx+Util::convert(${Config}->{LyricsBook}->{MarginHorizontal});
              m_BufLyrics.clear();
              m_BufChords.clear();
              m_subtitle.clear();
//            $CurrentColor=$Config->{ChordBook}->{NormalColor};
//            $vmargin=Util::convert($Config->{"LyricsBook"}->{MarginVertical});
//            $vmargin=$ury-$ury*192/200;
              setCompress(false);
              m_tempo=120;
              m_time=QString("4/4");
        }
        else if ( line.contains(SocREX) )
        {
            setSocMode(true);
            includeSoc();
        }
        else if ( line.contains(EocREX) )
        {
            setSocMode(false);
            includeEoc();
        }
        else if ( line.contains(SorREX) )
        {
            setRefrain(true);
            includeSor();
        }
        else if ( line.contains(EorREX) )
        {
            setRefrain(false);
            includeEor();
        }
        else if ( line.contains(ChordREX) )
        {
             if ( m_chorus ) includeChorus(line);
             else m_BufLyrics<<line;
             memorizeChords(line);
        }
        else
        {
            m_BufLyrics<<line;
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
emit PDFMade(m_file);
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

void Processor::setBpm(double bpm)
{
    m_tempo=bpm;
}

void Processor::setRytm( QString rythm)
{
    m_time=rythm;
}

void Processor::setCoverTitle(QString covertitle)
{
    m_covertitle=covertitle;
    m_covertitleexist=true;
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
    m_covertsubtitleexist=true;
    m_coversubtitle=coversubtitle;
}

QString Processor::getVersion(){return m_version ;}

void Processor::setVersion(QString version)
{
    m_version=version;
}

void Processor::includeRefrain(QString line)
{
  m_BufLyrics<<line;
}


void Processor::includeSoc()
{
    m_BufLyrics<<tr("Chorus :");
}

void Processor::includeEoc()
{
    m_BufLyrics<<tr("End of chorus");
}


void Processor::includeSor()
{
     m_BufLyrics<<tr("Refrain :");
}

void Processor::includeEor()
{
  m_BufLyrics<<tr("End of refrain");
}

void Processor::includeChorus( QString line)
{
  m_BufLyrics<<line;
}

void Processor::displayPageTitle( QString title)
{
    newPage();
    m_NormalPages<<m_page->GetContents();
    m_title=title.replace(QRegExp("^ +"),"");
    m_tocpages[m_title]=1;
    m_toc<<m_title;
    m_colnumber=1;
    if ( m_uiconfig->toolButtonTitleFont->getBackgroundColor() != m_uiconfig->colorButtonPaperColor->getColor())
    {
      m_painter.SetColor(m_uiconfig->toolButtonTitleFont->getBackgroundColor().redF(),m_uiconfig->toolButtonTitleFont->getBackgroundColor().greenF(),m_uiconfig->toolButtonTitleFont->getBackgroundColor().blueF());
      m_painter.Rectangle(m_uiconfig->spuHorizontalMargin->getPdfU(),
                        m_uiconfig->spuPageHeight->getPdfU()-m_uiconfig->spuVerticalMargin->getPdfU()-m_uiconfig->toolButtonTitleFont->getFont().pointSize(),
                        m_uiconfig->spuPageWidth->getPdfU()-2*m_uiconfig->spuHorizontalMargin->getPdfU(),
                        m_uiconfig->toolButtonTitleFont->getFont().pointSize());
      m_painter.Fill();
    }
    if ( m_uiconfig->checkBoxTitleInUppercase->isChecked()) title=title.toUpper();
    m_line=m_uiconfig->spuPageHeight->getPdfU()- m_uiconfig->spuVerticalMargin->getPdfU()-m_uiconfig->toolButtonTitleFont->getFont().pointSize()/1.4;//*0.8;
    Text(m_document,title,m_uiconfig->spuPageWidth->getPdfU()/2,
               m_line,
               m_uiconfig->toolButtonTitleFont,center);
    m_firstline=true;
    m_line-=m_uiconfig->toolButtonSubtitleFont->getFont().pointSize()/1.8;
}

void Processor::displayPageSubtitle(QString subtitle)
{
    int subtitlenumber=m_subtitle.count();
    if ( !m_pageAllocation)
    {
       m_page = m_document->CreatePage(*m_dimension);
       m_painter.SetPage(m_page);
       m_pageAllocation=true;
    }
  if ( m_uiconfig->toolButtonSubtitleFont->getBackgroundColor() != m_uiconfig->colorButtonPaperColor->getColor())
  {
    m_painter.SetColor(m_uiconfig->toolButtonSubtitleFont->getBackgroundColor().redF(),m_uiconfig->toolButtonSubtitleFont->getBackgroundColor().greenF(),m_uiconfig->toolButtonSubtitleFont->getBackgroundColor().blueF());
    m_painter.Rectangle(m_uiconfig->spuHorizontalMargin->getPdfU(),
                        m_uiconfig->spuPageHeight->getPdfU()-m_uiconfig->spuVerticalMargin->getPdfU()-m_uiconfig->toolButtonTitleFont->getFont().pointSize()-subtitlenumber*m_uiconfig->toolButtonSubtitleFont->getFont().pointSize(),//*1.4-1,
                        m_uiconfig->spuPageWidth->getPdfU()-2*m_uiconfig->spuHorizontalMargin->getPdfU(),
                        m_uiconfig->toolButtonSubtitleFont->getFont().pointSize());
    m_painter.Fill();
  }
  m_line-=m_uiconfig->toolButtonSubtitleFont->getFont().pointSize();
  Text(m_document,subtitle,m_uiconfig->spuPageWidth->getPdfU()/2,
       m_line,
       m_uiconfig->toolButtonSubtitleFont,center);
  m_line-=m_uiconfig->toolButtonSubtitleFont->font().pointSize()*2;
}

void Processor::setSocMode(bool socmode)
{
    m_chorus=socmode;
}

void Processor::setRefrain(bool refrain)
{
    m_refrain=refrain;
}



void Processor::newPage()
{
    if ( m_pageAllocation)
    {
        FinishPage(&m_painter);
    }
    m_page = m_document->CreatePage(*m_dimension);
    m_painter.SetPage(m_page);
    m_line=m_uiconfig->spuPageHeight->getPdfU()-m_uiconfig->spuVerticalMargin->getPdfU();
    if ( m_mode == "lyrics" && m_uiconfig->comboBoxChordInText->currentIndex()==FormConfig::DiagramInText)
    {
        m_line-=m_uiconfig->spuChordHorizontalSize->getPdfU();
    }
    m_column=m_uiconfig->spuHorizontalMargin->getPdfU();
    m_pageAllocation=true;
 }

void Processor::doColumnBreak(QString line)
{
    QRegExp ColumnBreakREX("^ *\\{(column_break|colb) *\\}",Qt::CaseInsensitive);
    if ( line.contains(ColumnBreakREX))
    {
        if ( m_colnumber > 1 && currentColumn() < m_colnumber  )
              {
                m_column = nextColumn( currentColumn() ) ;
                m_line=m_initialhposition;
              }
            else
            {
                if (m_tocpages.count() != 0)
                    m_tocpages[m_title]++;
                newPage();
            }
    }
}

void Processor::displayLyrics()
{
    QRegExp CommentRex("^ *\\{(?:comment|c): *([^}]*) *\\}",Qt::CaseInsensitive);
    QRegExp CommentItalicRex("^ *\\{(?:comment-italic|ci): *([^}]*) *\\}",Qt::CaseInsensitive);
    QRegExp CommentBoxRex("^ *\\{(?:comment-box|cb): *([^}]*) *\\}",Qt::CaseInsensitive);

    BufLyricsNormailisation();
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
            if ( isColBreak(text))
                doColumnBreak(text);
            else if ( text.contains(CommentRex))
            {
                 Text(m_document,CommentRex.cap(1),m_column,m_line,m_uiconfig->toolButtonCommentFont);
                 NextLine();
            }
            else if ( text.contains(CommentItalicRex))
            {
                Text(m_document,CommentItalicRex.cap(1),m_column,m_line,m_uiconfig->toolButtonCommentItalicFont);
                 NextLine();
            }
            else if ( text.contains(CommentBoxRex))
            {
                TextInBox(m_document,CommentRex.cap(1),m_column,m_line,m_uiconfig->toolButtonCommentBoxFont);
                 NextLine();
            }
            else
            {
                Text(m_document,text,m_column,m_line,m_uiconfig->toolButtonNormalFont);
                NextLine();
            }
        }
        else
        NextLine();
    }
}


bool Processor::isChorus(QString text)
{
    QString emptyifchorus=text;
    emptyifchorus.replace(QRegExp("\\[[^]]+\\]"),"").replace(" ","") ;
    return emptyifchorus.isEmpty();
}

bool Processor::isColBreak(QString line)
{
    return ( line.contains(QRegExp("^ *\\{(column_break|colb)",Qt::CaseInsensitive)));
}

void Processor::NextLine(int num )
{
    double vs=m_uiconfig->comboBoxVerticalSpacing->currentData().toDouble();
    if (  m_line - 2*m_uiconfig->toolButtonNormalFont->getFont().pointSizeF()*vs  - 2 * num >
          m_uiconfig->spuVerticalMargin->getPdfU())
    {
        m_line-=m_uiconfig->toolButtonNormalFont->getFont().pointSizeF()*vs+num;
    }
    else if ( m_colnumber > 1 && currentColumn() < m_colnumber  )
   {
        m_column = nextColumn(currentColumn()) ;
        m_line=m_initialhposition;
        m_line-=m_uiconfig->toolButtonNormalFont->getFont().pointSizeF()*vs;
    }
    else
    {
        if (m_tocpages.count() != 0)
        {
            m_tocpages[m_title]++;
        }
        newPage();
    }
}


int Processor::currentColumn()
{
  int c=1;
  while (c * m_uiconfig->spuPageWidth->getPdfU()/m_colnumber < m_column ) c++;
  return c;
}

int Processor::nextColumn( int colnumber)
{
    return ( m_uiconfig->spuPageWidth->getPdfU()*(colnumber)/m_colnumber +m_uiconfig->spuHorizontalMargin->getPdfU());
}

void Processor::Cover(QString title, QString subtitle, QString version)

{
        AllocatePage();
        QString image=m_projectpath+"/"+m_uiconfig->toolButtonCoverImage->getImage();
        QColor backgroundcolor=QColor(m_uiconfig->toolButtonCoverFont->getBackgroundColor());
        m_painter.SetColor(backgroundcolor.redF(),backgroundcolor.greenF(),backgroundcolor.blueF());
        m_painter.Rectangle(0,0,m_uiconfig->spuPageWidth->getPdfU(),m_uiconfig->spuPageHeight->getPdfU());
        m_painter.Fill(true);
        if (! image.isEmpty())
          {
            QPixmap pix(image);
            if (! pix.isNull())
            {
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
          }

          double posx=m_uiconfig->spuPageWidth->getPdfU()/2;
          double posy=TitlePosition();
          double x2=Text(m_document,title,posx,posy,m_uiconfig->toolButtonCoverFont,center);
          PdfFont *pfont=m_document->CreateFont(m_uiconfig->toolButtonCoverFont->getFont().family().toLatin1());
          pfont->SetFontSize(m_uiconfig->toolButtonCoverFont->getFont().pointSize()*0.5);
          pfont->SetUnderlined(m_uiconfig->toolButtonCoverFont->getFont().underline());
          pfont->SetStrikeOut(m_uiconfig->toolButtonCoverFont->getFont().strikeOut());
          double widthtext=pfont->GetFontMetrics()->StringWidth(subtitle.toLatin1());
          Text(m_document,subtitle,x2-widthtext/2,posy-m_uiconfig->toolButtonCoverFont->getFont().pointSize()*0.5,m_uiconfig->toolButtonCoverFont,right,0.5);
          Text(m_document,version,x2-widthtext/2,posy-m_uiconfig->toolButtonCoverFont->getFont().pointSize()*3,m_uiconfig->toolButtonCoverFont,center,0.2);
}


void Processor::AllocatePage()
{
    m_pageAllocation=true;
    m_page= m_document->CreatePage(*m_dimension);
    m_painter.SetPage(m_page);
}

void Processor::doChords()
{

}

void Processor::displayChordsForSong()
{
}



void Processor::setColBreak(QString line)
{
       m_BufLyrics<<line;
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
       //int i= m_mdocument->GetPageCount();
       QFile  file(m_file);
       file.remove();
       m_mdocument->Write(m_file.toStdString().c_str());
}

void Processor::openExistingFile()
{
    m_mdocument = new PdfMemDocument(m_file.toStdString().c_str());
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
    bool ok ;
    double verticalspacing=m_uiconfig->comboBoxTocVerticalSpacing->currentData().toDouble(&ok);
    if ( !ok ) verticalspacing=1.2;
    double heightneed=nbpages*(verticalspacing+1)
            *m_uiconfig->toolButtonTocFont->getFont().pointSizeF()/m_uiconfig->comboBoxTocColumnNumber->currentText().toInt();
    double nbpagesneed=heightneed/(m_uiconfig->spuPageHeight->getPdfU() - m_uiconfig->toolButtonTitleFont->getFont().pointSizeF()*2.4
                        - 2*m_uiconfig->spuVerticalMargin->getPdfU() );
    int nb=nbpagesneed+1;
    return nb;
}

int Processor::FirstPageNumber()
{
    return m_covermade?2:1;
}


int Processor::NbPageCover()
{
    return m_covermade?1:0;
}

void Processor::memorizeChords(QString line)
{
    QRegExp chordEx("\\[([^]]*)\\]");
    while ( line.indexOf(chordEx)!=-1)
    {
        m_BufChords<<chordEx.cap(1);
        line.replace(QString("[%1]").arg(chordEx.cap(1)),"");
    }
}

void Processor::addTocAtBegining()
{
    if ( !m_pageAllocation)
    {
       m_page = m_document->CreatePage(*m_dimension);
       m_painter.SetPage(m_page);
       m_pageAllocation=true;
    }
    PdfPage *toc;
    int pagenumber=0;
    int position =FirstPageNumber();
    m_positiontoc=position-1;
    m_line=m_uiconfig->spuPageHeight->getPdfU()- m_uiconfig->spuVerticalMargin->getPdfU();
    toc=m_document->InsertPage(*m_dimension,position-1);

    pagenumber++;
    m_TocPages<<toc->GetContents();
    m_painter.SetPage(toc);
    bool ok;
    double verticalspacing=m_uiconfig->comboBoxTocVerticalSpacing->currentData().toDouble(&ok);
    if ( !ok ) verticalspacing=1.2;
    Text(m_document,QObject::tr("Table of content"),m_uiconfig->spuPageWidth->getPdfU()/2,m_line,m_uiconfig->toolButtonTitleFont,center);
    m_line-=m_uiconfig->toolButtonTitleFont->getFont().pointSizeF()*2.4 ;
    int lineinit=m_line;
    int colinit=m_uiconfig->spuTocHorizontalMargin->getPdfU();
    int currentcol=0;
    int titlenumber=0;
    int nbpagesintoc=1;
    nbpagesintoc=NbPagesInToc(m_nbrealpages);
    foreach ( QString title, m_toc)
        {
         // rect is the zone clickable
         int page=pagenumber+nbpagesintoc-1;
         PdfRect rect=LineToc(title,TocColSize(),colinit,m_line,m_uiconfig->toolButtonTocFont,page);
         PdfAnnotation *a=toc->CreateAnnotation(ePdfAnnotation_Link,rect);
         //a->SetContents(tr("Go to page %1").arg(pagenumber+nbpagesintoc-2).toStdString().c_str());
         PdfDestination dest(m_document->GetPage(page-nbpagesintoc+position - (m_covermade?0:1)));
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
             colinit=m_uiconfig->spuTocHorizontalMargin->getPdfU();
             m_tocpages[m_title]++;
             if ( m_pageAllocation)  FinishPage(&m_painter);
             toc=m_document->InsertPage(*m_dimension,position);
             position++;
             m_painter.SetPage(toc);
             m_line=m_uiconfig->spuPageHeight->getPdfU()-m_uiconfig->spuVerticalMargin->getPdfU();
             m_column=m_uiconfig->spuTocHorizontalMargin->getPdfU();
             m_TocPages<<toc->GetContents();
         }
         titlenumber++;
    }
    FinishPage(&m_painter);
}

void Processor::addTocAtEnd()
{

    if ( !m_pageAllocation)
    {
       m_page = m_document->CreatePage(*m_dimension);
       m_painter.SetPage(m_page);
       m_pageAllocation=true;
    }
    PdfPage *toc;
    int pagenumber=0;
    m_positiontoc=m_document->GetPageCount();
    m_line=m_uiconfig->spuPageHeight->getPdfU()- m_uiconfig->spuVerticalMargin->getPdfU();
    toc=m_document->CreatePage(*m_dimension);
    pagenumber++;
    m_TocPages<<toc->GetContents();
    m_painter.SetPage(toc);
    bool ok;
    double verticalspacing=m_uiconfig->comboBoxTocVerticalSpacing->currentData().toDouble(&ok);
    if ( !ok ) verticalspacing=1.2;
    Text(m_document,QObject::tr("Table of content"),m_uiconfig->spuPageWidth->getPdfU()/2,m_line,m_uiconfig->toolButtonTitleFont,center);
    m_line-=m_uiconfig->toolButtonTitleFont->getFont().pointSizeF()*2.4 ;
    int lineinit=m_line;
    int colinit=m_uiconfig->spuTocHorizontalMargin->getPdfU();
    int currentcol=0;
    int titlenumber=0;
//    int nbpagesintoc=1;
//    nbpagesintoc=NbPagesInToc(m_nbrealpages);
    foreach ( QString title, m_toc)
        {
         // rect is the zone clickable
         PdfRect rect=LineToc(title,TocColSize(),colinit,m_line,m_uiconfig->toolButtonTocFont,pagenumber);
         PdfAnnotation *a=toc->CreateAnnotation(ePdfAnnotation_Link,rect);
     //    a->SetContents(tr("Go to page %1").arg(pagenumber+FirstPageNumber()).toStdString().c_str());
         a->SetContents(QString("Go to page 11").toStdString().c_str());

         PdfDestination dest(m_document->GetPage(pagenumber-1+NbPageCover()));
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
             colinit=m_uiconfig->spuTocHorizontalMargin->getPdfU();
             m_tocpages[m_title]++;
             if ( m_pageAllocation)  FinishPage(&m_painter);
             toc=m_document->CreatePage(*m_dimension);
             m_painter.SetPage(toc);
             m_line=m_uiconfig->spuPageHeight->getPdfU()-m_uiconfig->spuVerticalMargin->getPdfU();
             m_column=m_uiconfig->spuTocHorizontalMargin->getPdfU();
             m_TocPages<<toc->GetContents();
         }
         titlenumber++;
    }
    FinishPage(&m_painter);

}

void Processor::addToc()
{
    if ( m_uiconfig->comboBoxTocPosition->currentIndex()==0)  FinishPage(&m_painter);
    else if ( m_uiconfig->comboBoxTocPosition->currentIndex()==1) addTocAtBegining();
    else addTocAtEnd();

}

void Processor::makePageNumber()
{
    bool arrow = false;
    Const::PageNumber pagetype= Const::getPageNumber(m_uiconfig->comboBoxPageNumber->currentIndex());
    if (pagetype == Const::No )  return ;

    int firstpage=getCoverMade() ? 2:1;
    int totalpage=m_mdocument->GetPageCount()-firstpage+1;
    if (totalpage<=0) return;
    int nbpage=1;
    for ( int p=firstpage-1; p<=totalpage ; p++)
    {
        if ( nbpage > totalpage ) break;
        PdfPage *pdfp = m_mdocument->GetPage(p);
        m_painter.SetPage(pdfp);
        QString pattern;
        if ( m_uiconfig->comboBoxPageNumberStyle->currentIndex()==Const::Number)
            pattern="%1";
        else if ( m_uiconfig->comboBoxPageNumberStyle->currentIndex()==Const::NumberAndTiret )
            pattern="- %1 -";
        else if ( m_uiconfig->comboBoxPageNumberStyle->currentIndex()==Const::NumberDivideByPageNUmber )
            pattern=QString("%%1/%1").arg(totalpage);
        else if ( m_uiconfig->comboBoxPageNumberStyle->currentIndex()==Const::NumberAndArrows )
        {
            pattern=QString("%1");
            arrow=true;
        }
        else pattern=QString("%1");
        QString page=QString(pattern).arg(nbpage);

        double  widthtext=m_uiconfig->toolButtonPageNumberFont->getFont().pointSizeF()*page.length();
        int x=0;
        int y=0;
        if (  m_uiconfig->spuHorizontalMargin->getPdfU() < m_uiconfig->toolButtonPageNumberFont->getFont().pointSizeF() )
            y= m_uiconfig->toolButtonPageNumberFont->getFont().pointSizeF()*3;
        else
          y =  m_uiconfig->spuHorizontalMargin->getPdfU()-m_uiconfig->toolButtonPageNumberFont->getFont().pointSizeF() ;
        if ( pagetype == Const::Center)
            x = m_uiconfig->spuPageWidth->getPdfU()/2;
        else if ( m_uiconfig->comboBoxPageNumberStyle->currentIndex()==Const::Outside )
        {  if ( m_uiconfig->comboBoxDuplex->currentIndex() ==Const::Simplex)
              x =m_uiconfig->spuPageWidth->getPdfU()-m_uiconfig->spuHorizontalMargin->getPdfU();
           else if ( nbpage %2 == 0 )
               x =m_uiconfig->spuPageWidth->getPdfU()-m_uiconfig->spuHorizontalMargin->getPdfU();
           else
               x = m_uiconfig->spuHorizontalMargin->getPdfU();
        }
        if ( m_uiconfig->toolButtonPageNumberFont->getBackgroundColor() != m_uiconfig->colorButtonPaperColor->getColor() )
        {
            m_painter.SetColor(m_uiconfig->toolButtonPageNumberFont->getBackgroundColor().redF(),m_uiconfig->toolButtonPageNumberFont->getBackgroundColor().greenF(),m_uiconfig->toolButtonPageNumberFont->getBackgroundColor().blueF());
            m_painter.Rectangle(m_uiconfig->spuHorizontalMargin->getPdfU(),
                              y-m_uiconfig->toolButtonTocFont->getFont().pointSize()/3.0,
                              m_uiconfig->spuPageWidth->getPdfU()-2*m_uiconfig->spuHorizontalMargin->getPdfU(),
                              m_uiconfig->toolButtonTocFont->getFont().pointSize()*1.3);
            m_painter.Fill();
        }
        if  ( pagetype == Const::Center )
        {

            if ( arrow )
            {
              Text(m_mdocument,page,x,y,m_uiconfig->toolButtonPageNumberFont,left);
              if (nbpage > 1)
              {
                m_painter.SetColor(m_uiconfig->toolButtonPageNumberFont->getTextColor().redF(),m_uiconfig->toolButtonPageNumberFont->getTextColor().greenF(),m_uiconfig->toolButtonPageNumberFont->getTextColor().blueF());
                m_painter.MoveTo(x-m_uiconfig->toolButtonTocFont->getFont().pointSize(),y+0.4*m_uiconfig->toolButtonTocFont->getFont().pointSize());
                m_painter.LineTo(x-m_uiconfig->toolButtonTocFont->getFont().pointSize()/2,y+0.8*m_uiconfig->toolButtonTocFont->getFont().pointSize());
                m_painter.LineTo(x-m_uiconfig->toolButtonTocFont->getFont().pointSize()/2,y);
                m_painter.ClosePath();
                m_painter.Fill();
                PdfRect rect1(x-1.5*m_uiconfig->toolButtonTocFont->getFont().pointSize(),y,m_uiconfig->toolButtonTocFont->getFont().pointSize(),m_uiconfig->toolButtonPageNumberFont->getFont().pointSizeF());
                PdfAnnotation *a1=pdfp->CreateAnnotation(ePdfAnnotation_Link,rect1);
                a1->SetContents(tr("Go to last page").toStdString().c_str());
                PdfDestination dest1(m_document->GetPage(nbpage-1));
                a1->SetDestination(dest1);
                a1->SetFlags( ePdfAnnotationFlags_Hidden);
              }
              if (nbpage < totalpage)
              {
                m_painter.SetColor(m_uiconfig->toolButtonPageNumberFont->getTextColor().redF(),m_uiconfig->toolButtonPageNumberFont->getTextColor().greenF(),m_uiconfig->toolButtonPageNumberFont->getTextColor().blueF());
                m_painter.MoveTo(x+widthtext+m_uiconfig->toolButtonTocFont->getFont().pointSize()/2,y+0.4*m_uiconfig->toolButtonTocFont->getFont().pointSize());
                m_painter.LineTo(x+widthtext,y+0.8*m_uiconfig->toolButtonTocFont->getFont().pointSize());
                m_painter.LineTo(x+widthtext,y);
                m_painter.ClosePath();
                m_painter.Fill();
                PdfRect rect2(x+widthtext,y,m_uiconfig->toolButtonTocFont->getFont().pointSize(),m_uiconfig->toolButtonPageNumberFont->getFont().pointSizeF());
                PdfAnnotation *a2=pdfp->CreateAnnotation(ePdfAnnotation_Link,rect2);
                a2->SetContents(tr("Go to next page").toStdString().c_str());
                PdfDestination dest2(m_document->GetPage(nbpage+1));
                a2->SetDestination(dest2);
                a2->SetFlags( ePdfAnnotationFlags_Hidden);
              }
            }
            else
                Text(m_mdocument,page,x,y,m_uiconfig->toolButtonPageNumberFont,center);
        }
        else
            Text(m_mdocument,page,x,y, m_uiconfig->toolButtonPageNumberFont,left);
        nbpage++;
    if (m_uiconfig->comboBoxTocPosition->currentIndex() != Const::No)
    {
            PdfRect rect(x-m_uiconfig->toolButtonPageNumberFont->getFont().pointSizeF()/2,y,1.5*widthtext,m_uiconfig->toolButtonPageNumberFont->getFont().pointSizeF());
            PdfAnnotation *a=pdfp->CreateAnnotation(ePdfAnnotation_Link,rect);
            a->SetContents(tr("Go to table of content").toStdString().c_str());
            PdfDestination dest(m_document->GetPage(m_positiontoc));
            a->SetDestination(dest);
            a->SetFlags( ePdfAnnotationFlags_Hidden);
     }
        FinishPage(&m_painter);
    }
}

PdfRect Processor::PageSize( double left, double bottom, double width, double height )
{
    PdfRect size(left,bottom,width,height);
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

double Processor::TextInBox(PdfDocument *doc, QString text, double x, double y, FontButton *fb ,Align align, double scale)
{
    if ( !m_pageAllocation)
    {
       m_page = m_document->CreatePage(*m_dimension);
       m_painter.SetPage(m_page);
       m_pageAllocation=true;
    }
    PdfFont *pfont=doc->CreateFont(fb->getFont().family().toLatin1());
    PdfString str(text.toLatin1());
    double fontsize=fb->getFont().pointSize()*scale;
    pfont->SetFontSize(fontsize);
    pfont->SetUnderlined(fb->getFont().underline());
    pfont->SetStrikeOut(fb->getFont().strikeOut());
    double widthtext=pfont->GetFontMetrics()->StringWidth(text.toLatin1())*scale;
    double heighttext=pfont->GetFontSize()*1.1;
    m_painter.SetColor(fb->getBackgroundColor().redF(),fb->getBackgroundColor().greenF(),fb->getBackgroundColor().blueF());
    double vs=m_uiconfig->comboBoxVerticalSpacing->currentData().toDouble();
    m_painter.Rectangle(x-widthtext*0.1,y-heighttext*0.2,widthtext*vs,heighttext*vs);
    m_painter.Fill();
    return Text(doc,text,x,y,fb,align,scale);


}

double  Processor::Text( PdfDocument *doc, QString text, double x, double y, FontButton *fb ,Align align, double scale)
{
    qDebug()<<"text"<<text;
    if (text.length()==0 ) return 0;
    if ( !m_pageAllocation)
    {
       m_page = m_document->CreatePage(*m_dimension);
       m_painter.SetPage(m_page);
       m_pageAllocation=true;
    }
    double end=0;
    PdfFont *pfont=doc->CreateFont(fb->getFont().family().toLatin1());
    PdfString str(text.toLatin1());
    double fontsize=fb->getFont().pointSize()*scale;
    pfont->SetFontSize(fontsize);
    pfont->SetUnderlined(fb->getFont().underline());
    pfont->SetStrikeOut(fb->getFont().strikeOut());
    double widthtext=pfont->GetFontMetrics()->StringWidth(str);
    while ( widthtext >m_uiconfig->spuPageWidth->getPdfU() )
    {
        fontsize=fontsize*0.9;
        pfont->SetFontSize(fontsize);
        widthtext=pfont->GetFontMetrics()->StringWidth(str);
    }
    m_painter.SetFont(pfont);
    m_painter.SetColor(fb->getTextColor().redF(),fb->getTextColor().greenF(),fb->getTextColor().blueF());
    m_painter.Fill(true);
    if (! text.isEmpty())
    {
        if ( align == right )  x-=widthtext*scale;
        else if ( align == center ) x-=widthtext*scale/2;
        else if (align == left ) {};
        end=x+widthtext;
        m_painter.DrawText(x,y,str);
    }
    return end;
}


PdfRect Processor::LineToc(QString text, double width, double x, double y, FontButton *fb, int pagenumber)
{
    if ( !m_pageAllocation)
    {
       m_page = m_document->CreatePage(*m_dimension);
       m_painter.SetPage(m_page);
       m_pageAllocation=true;
    }
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
    while ( pfont->GetFontMetrics()->StringWidth(QString("%1%2    ").arg(text,point).toLatin1())<= width-m_uiconfig->spuTocHorizontalMargin->getPdfU()*2)
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
    Text(m_document,QString("%1").arg(pagenumber),x+width+fb->getFont().pointSize()-2*m_uiconfig->spuTocHorizontalMargin->getPdfU(),y,fb,right);
    return rect;
}


void Processor::FinishPage(PdfPainter *painter)
{
    QString watermark=m_uimainwindow->lineEditWatermark->text();
    watermark=QString("          %1          ").arg(watermark);
    if ( ! watermark.isEmpty() )
    {
        painter->Save();

        PdfFont *pfont=m_document->CreateFont(m_uiconfig->toolButtonTitleFont->getFont().family().toLatin1());

        PdfExtGState state(m_document);
        state.SetFillOpacity(0.4);
        painter->SetExtGState(&state);
        PdfString str(watermark.toLatin1());
        double lenght=sqrt(qPow(m_uiconfig->spuPageHeight->getPdfU(),2)+qPow(m_uiconfig->spuPageWidth->getPdfU(),2));
        while (pfont->GetFontMetrics()->StringWidth(str) < lenght )
        {
            pfont->SetFontSize(pfont->GetFontSize()+1);
        }
        painter->SetFont(pfont);
        painter->SetColor(0.90,0.90,0.90);
        painter->Fill(true);
        double angle=qAtan(m_uiconfig->spuPageHeight->getPdfU()/m_uiconfig->spuPageWidth->getPdfU());
        double sinA=sin(angle);
        double cosA=cos(angle);
        painter->SetTransformationMatrix(cosA,sinA,-sinA,cosA,0,0);
        painter->DrawText(0,0,PdfString(watermark.toLatin1().toStdString()));
        painter->Restore();
    }
    painter->FinishPage();
}



void Processor::displayChord(QString ch,int &line, int &column,int size, QString lang)
{
    Chord chord(ch,lang);
    int steph=size/8;
    int stepv=size/10 ;

//   1 2 3 4 5 6 7 8
//1        0
//2      ===========
//3       o
//4      -----------
//5
//6      -----------
//7
//8      -----------
//9
//10     -----------



    int sizecircle=steph/3;
    int sizenonote=steph/4;
    int sizefont=steph;

    if ( !m_pageAllocation)
    {
       m_page = m_document->CreatePage(*m_dimension);
       m_painter.SetPage(m_page);
       m_pageAllocation=true;
    }
    PdfFont *pfont=m_document->CreateFont(m_uiconfig->toolButtonChordFont->getFont().family().toLatin1());
    pfont->SetFontSize(sizefont);
    pfont->SetUnderlined(m_uiconfig->toolButtonChordFont->getFont().underline());
    pfont->SetStrikeOut(m_uiconfig->toolButtonChordFont->getFont().strikeOut());
    m_painter.SetFont(pfont);
    QString fret=chord.fret();
    // print fret number
    if (  fret!= "0") m_painter.DrawText(column+steph,line-stepv*3,PdfString(chord.fret().toLatin1()));
    // print chord name
    m_painter.DrawTextAligned(column+size/2,line-stepv,chord.nameLocale().length(),PdfString(chord.nameLocale().toLatin1()), EPdfAlignment::ePdfAlignment_Center);
    // print first fret
    m_painter.SetStrokeWidth(2);
    m_painter.SetLineCapStyle(ePdfLineCapStyle_Round);
    m_painter.DrawLine(column+2*steph,line-2*stepv+1,column+7*steph,line-2*stepv+1);
    m_painter.SetStrokeWidth(0.5);
    // print 4 fret
    for ( int i=0; i<=3;i++) m_painter.DrawLine(column+2*steph,line-(3+i)*stepv,column+7*steph,line-(3+i)*stepv);
    for (int i=1;i<7;i++)   m_painter.DrawLine(column+(1+i)*steph,line-2*stepv,column+(1+i)*steph,line-7*stepv);

    int string=1;
    foreach ( QString s, chord.toStrings())
    {
        if ( s == "x")
        {
            m_painter.DrawLine(column+(1+string)*steph-sizenonote,line-(stepv+s.toInt()*stepv)-stepv/2+2+sizenonote,column+(1+string)*steph+sizenonote,line-(stepv+s.toInt()*stepv)-stepv/2+2-sizenonote);
            m_painter.DrawLine(column+(1+string)*steph-sizenonote,line-(stepv+s.toInt()*stepv)-stepv/2+2-sizenonote,column+(1+string)*steph+sizenonote,line-(stepv+s.toInt()*stepv)-stepv/2+2+sizenonote);

        }
        else if ( s == "0")
        {
            m_painter.Circle(column+(1+string)*steph,line-(stepv+s.toInt()*stepv)-stepv/2+2,sizecircle*0.6);
            m_painter.SetStrokeWidth(0.5);
            m_painter.Stroke();
        }
        else
        {
            m_painter.Circle(column+(1+string)*steph,line-(stepv+s.toInt()*stepv)-stepv/2,sizecircle);
            m_painter.Fill(true);
        }
        string++;
    }
    column+=size;
    // PB NOT COL COMPLIENT
    if ( column +size > m_uiconfig->spuPageWidth->getPdfU() - m_uiconfig->spuHorizontalMargin->getPdfU())
    {
        column = m_uiconfig->spuHorizontalMargin->getPdfU();
        // TEST IF ENOUGH PLACE
        line=line-size;
    }
}


void Processor::displayRytm()
{

}

void Processor::displayBpm()
{

}


void Processor::BufLyricsNormailisation()
{
    int i=0;
    int max=m_BufLyrics.count();
    QStringList out;
    foreach ( QString text , m_BufLyrics)
    {

        //if ( text.contains(QRegExp("^ +$"))) text.replace(QRegExp(" +"),"");
        if ( text.isEmpty() && i!=max-1 && m_BufLyrics.at(i+1).isEmpty())
         ;
        else
            out<<text;
        i++;
    }
    m_BufLyrics=out;
    if (!m_BufLyrics.isEmpty())
    while ( m_BufLyrics.last().isEmpty() && m_BufLyrics.count()!=1) m_BufLyrics.takeLast();
}


void Processor::addCol(int &col, int num)
{
  if ( m_colnumber == 1  && col + num < m_uiconfig->spuPageWidth->getPdfU()-m_uiconfig->spuHorizontalMargin->getPdfU())
  {
      col+=num;
  }
  else if ( m_colnumber == 1 )
  {
     NextLine(num);
     col=m_column;
  }
  else if ( m_colnumber > 1 &&  col+num < nextColumn(currentColumn()) )
  {
      col+=num;
  }
  else
  {
     NextLine(num);
     col=m_column;
  }
}


void Processor::setComposer( QString composer)
{
    m_composer=composer;
}

void Processor::setLyricist(QString lyricist)
{
    m_lyricist=lyricist;
}

void Processor::setArranger(QString arranger)
{
    m_arranger=arranger;
}

void Processor::setArtist(QString artist)
{
    m_artist=artist;
}
void Processor::setAlbum( QString album)
{
    m_album=album;
}
void Processor::setCopyright(QString copyright)
{
    m_copyright=copyright;
}

void Processor::setYear(int year)
{
    m_year=year;
}

void Processor::setKey(QString key)
{
    m_key=key;
}

void Processor::setDuration( QString duration)
{
    m_duration=duration;
}
