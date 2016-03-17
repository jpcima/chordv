#include "processor.h"


#include <QRegExp>
#include <QDebug>

Processor::Processor(QString text, AbstBook *b)
{
    QRegExp NewSongREX("^ *{(new_song|ns) *} *$");
    QRegExp CompressREX("^ *{compress} *} *$");
    QRegExp ColumnsREX("*{(col|columns): *([^}]*)");
    QRegExp ColumnBreakREX("^ *{(column_break|colb) *");
    QRegExp CoverTitleREX(" *{(covertitle|ct): *([^}]*)");
    QRegExp CoverSubTitleREX("^ *{(coversubtitle|cs): *([^}]*)");
    QRegExp SubTitleREX("^ *{(subtitle|st): *([^}]*)");
    QRegExp TitleREX("^ *{(title|t): *([^}]*)");
    QRegExp SocREX("^ *{(soc|start_of_chorus)}");
    QRegExp EocREX("^ *{(eoc|end_of_chorus)}");
    QRegExp RefrainREX("^Refrain *: *$");
    QRegExp ChordRex("\\[[^]]+\\]");

    QStringList Buf;

    bool first=true;
    b->setCoverMade(false);

    foreach ( QString line, text.split(QRegExp("\n")) )
    {

        if ( line.contains(NewSongREX) )  {}
        else if ( line.contains(CompressREX) )    { b->setCompress(true); }
        else if ( line.contains(ColumnsREX) )     { b->setColNumber(ColumnsREX.cap(2).toInt()); }
        else if ( line.contains(ColumnBreakREX) ) { //b->breakCol($pdflyrics,$pagelyrics,\$lyricsline,\$lyricscol,$vspacing,0,$vmargin,$hmargin);
        }
        else if ( line.contains(CoverTitleREX) ) {  b->setCoverTitle(CoverTitleREX.cap(2)); }
        else if ( line.contains(CoverSubTitleREX) ) {  b->setCoverSubtitle(CoverSubTitleREX.cap(2)); }
        else if ( line.contains(SubTitleREX) )
        {
            QString subtitle=SubTitleREX.cap(2);
            b->setSubTitle(subtitle);
            b->displayPageSubtitle(subtitle) ;
            //my ($llx,$lly,$urx,$ury)=$pagelyrics->get_mediabox();
            //$vmargin=$ury-$ury*(19/20-1/70*$subtitley);
        }
        else if ( line.contains(TitleREX) )
        {
            b->setTitle(TitleREX.cap(2));
//            $subtitley=1;
//            $colnumber=1;
//            $tocpage++;
//            $TocPages[$tocpage]=1;
//            &printChordsForSong();
//            %ChordsForSong = ();

//            if ( $AnnotationAuth!~/^$/ )
//            {
//              my ($llx,$lly,$urx,$ury)=$pagechords->get_mediabox();
//              my $ant=$pagechords->annotation();
//              $ant->rect($llx,$ury*19/20,$urx,$ury);
//              $ant->text($AnnotationAuth);
//              $AnnotationAuth="";
//            }
            if ( ! b->getCoverMade()  )
            {
                 b->Cover(b->getCoverTitle(),b->getCoverSubtitle());
                 b->setCoverMade(true);
//                $TocsChords[0]= $pdfchords->page();
//                $TocsLyrics[0]= $pdflyrics->page();
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
//                &DisplayPageTitle($pdfchords,$TocsChords[0],"ChordBook",__("Table of content")) ;
//                &DisplayPageTitle($pdflyrics,$TocsLyrics[0],"LyricsBook",__("Table of content")) ;
//            }
              if ( first == false ) b->doChords();
//            $pagechords=$pdfchords->page();
//            $pagelyrics=$pdflyrics->page();
//            my ($llx,$lly,$urx,$ury)=$pagelyrics->get_mediabox;
//            $MaxLine=$lyricsline=($ury-$lly)*190/210;
//            $lyricscol=$llx+Util::convert(${Config}->{LyricsBook}->{MarginHorizontal});
              first=false;
              Buf.clear();
//            $CurrentColor=$Config->{ChordBook}->{NormalColor};
//            $vmargin=Util::convert($Config->{"LyricsBook"}->{MarginVertical});
//            &DisplayPageTitle($pdfchords,$pagechords,"ChordBook",$title);
//            &DisplayPageTitle($pdflyrics,$pagelyrics,"LyricsBook",$title);
//            $vmargin=$ury-$ury*192/200;
//            AddToc($TocsChords[scalar(@TocsChords)-1],$pdfchords,$title,"ChordBook",\%InfoChords,\@TocsChords);
//            AddToc($TocsLyrics[scalar(@TocsLyrics)-1],$pdflyrics,$title,"LyricsBook",\%InfoLyrics,\@TocsLyrics);
              b->setCompress(false);

        }
        else if ( line.contains(SocREX) )
        {
            Buf<<QObject::tr("Chorus");
            b->setSocMode(true);
        }
        else if ( line.contains(EocREX) )
        {
            Buf<<QObject::tr("Endchorus");
            b->setSocMode(false);
        }
        else if ( line.contains(RefrainREX) )
        {
            b->setRefrain(true);
            Buf<<QObject::tr("Refrain");
        }
        else if   ( line.contains(ChordRex) )
        {

              b->displayLyrics(line);
              line=b->keepChords(line);

              QStringList s=line.split("|");
              Buf<<s;
        }
        else if ( first  )
        {
           b->displayLyrics(line);
        }
    }

}


b->doChords();
b->printChordsForSong();

//my $out1=$Config->{ChordBook}->{OutFile};
//$pdfchords->saveas($out1);
//$pdfchords=PDF::API2->open($out1);
//$startoc=$pdfchords->openpage(&firstpage("ChordBook"));
//&DisplayFooters($pdfchords,"ChordBook");
//&AddLinksInToc($pdfchords,"ChordBook",\%InfoChords,\@TocsChords);
//&MakePageNumbers($pdfchords,"ChordBook");
//$pdfchords->saveas($out1);


//my $out2=$Config->{LyricsBook}->{OutFile};
//$pdflyrics->saveas($out2);
//$pdflyrics=PDF::API2->open($out2);
//$startoc=$pdflyrics->openpage(&firstpage("LyricsBook"));
//&DisplayFooters($pdflyrics,"LyricsBook");
//&AddLinksInToc($pdflyrics,"LyricsBook",\%InfoLyrics,\@TocsLyrics);
//&MakePageNumbers($pdflyrics,"LyricsBook");
//$pdflyrics->saveas($out2);

}
