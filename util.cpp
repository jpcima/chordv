#include "util.h"
#include <QSettings>

Util::Util()
{

}


void Util::initConfigFile( QString projectName)
{
    QSettings s(projectName,QSettings::IniFormat);
    s.setValue("General/File",QObject::tr("yoursongs.cho3"));
    s.setValue("General/Creator",QObject::tr("Your Name"));
    s.setValue("General/chordlang",QObject::tr("en"));

    s.setValue("ChordBook/Cover","1");
    s.setValue("ChordBook/CoverBackgroundColor","#EDB029");
    s.setValue("ChordBook/CoverTextColor","black");
    s.setValue("ChordBook/CoverImage","template/image.png");
    s.setValue("ChordBook/CoverFont","somefont");
    s.setValue("ChordBook/OpenFullScreen","1");
    s.setValue("ChordBook/TocFont","Courier-Bold");
    s.setValue("ChordBook/NormalFont","Courier-Bold");
    s.setValue("ChordBook/MediaBox","A4");
    s.setValue("ChordBook/TitleFont","Courier-Bold");
    s.setValue("ChordBook/TitleFontSize","40pt");
    s.setValue("ChordBook/TitleColor","white");
    s.setValue("ChordBook/PageNumberFontSize","18pt");
    s.setValue("ChordBook/MarginHorizontal","1cm");
    s.setValue("ChordBook/MarginVertical","1cm");
    s.setValue("ChordBook/UpperCase","1");
    s.setValue("ChordBook/SubtitleFont","Courier");
    s.setValue("ChordBook/SubtitleFontSize","8pt");
    s.setValue("ChordBook/TitleBackgroundColor","#9A5D5D");
    s.setValue("ChordBook/RefrainColor","#346034");
    s.setValue("ChordBook/ChorusColor","#7B5757");
    s.setValue("ChordBook/NormalColor","black");
    s.setValue("ChordBook/TocSizeFont","18pt");
    s.setValue("ChordBook/TocVerticalSpacing","12mm");
    s.setValue("ChordBook/TocCols","2");
    s.setValue("ChordBook/OutFile","ChordsBooklet.pdf");
    s.setValue("chordBook/chordlang","en");

    s.setValue("LyricsBook/Cover","1");
    s.setValue("LyricsBook/ChordDiagramHSize","2cm");
    s.setValue("LyricsBook/CoverBackgroundColor","#EDB029");
    s.setValue("LyricsBook/CoverTextColor","black");
    s.setValue("LyricsBook/CoverImage","template/image.png");
    s.setValue("LyricsBook/CoverFont","Verdana-Bold");
    s.setValue("LyricsBook/TitleFont","Times-Bold");
    s.setValue("LyricsBook/PageNumberFontSize","12pt");
    s.setValue("LyricsBook/TitleFontSize","18pt");
    s.setValue("LyricsBook/TitleColor","white");
    s.setValue("LyricsBook/UpperCase","1");
    s.setValue("LyricsBook/SubtitleFont","Times");
    s.setValue("LyricsBook/SubtitleFontSize","12pt");
    s.setValue("LyricsBook/TitleBackgroundColor","black");
    s.setValue("LyricsBook/TocFont","Times-Italic");
    s.setValue("LyricsBook/TocCols","1");
    s.setValue("LyricsBook/NormalFont","Times");
    s.setValue("LyricsBook/NormalFontSize","12pt");
    s.setValue("LyricsBook/OpenFullScreen","1");
    s.setValue("LyricsBook/OutFile","LyricsBooklet.pdf");
    s.setValue("LyricsBook/MediaBox","A4");
    s.setValue("LyricsBook/MarginHorizontal","1cm");
    s.setValue("LyricsBook/MarginVertical","1cm");
    s.setValue("LyricsBook/ChordFont","Times-Italic");
    s.setValue("LyricsBook/ChordFontSize","9pt");
    s.setValue("LyricsBook/chordlang","fr");
    s.setValue("LyricsBook/ChordDraw","0");

    s.setValue("TextBook/Cover","1");
    s.setValue("TextBook/CoverBackgroundColor","#EDB029");
    s.setValue("TextBook/CoverTextColor","black");
    s.setValue("TextBook/CoverImage","template/image.png");
    s.setValue("TextBook/CoverFont","Verdana-Bold");
    s.setValue("TextBook/TitleFont","Times-Bold");
    s.setValue("TextBook/PageNumberFontSize","12pt");
    s.setValue("TextBook/TitleFontSize","18pt");
    s.setValue("TextBook/TitleColor","white");
    s.setValue("TextBook/UpperCase","1");
    s.setValue("TextBook/SubtitleFont","Times");
    s.setValue("TextBook/SubtitleFontSize","12pt");
    s.setValue("TextBook/TitleBackgroundColor","black");
    s.setValue("TextBook/TocFont","Times-Italic");
    s.setValue("TextBook/TocCols","1");
    s.setValue("TextBook/NormalFont","Times");
    s.setValue("TextBook/NormalFontSize","12pt");
    s.setValue("TextBook/OpenFullScreen","1");
    s.setValue("TextBook/OutFile","TextBooklet.pdf");
    s.setValue("TextBook/MediaBox","A4");
    s.setValue("TextBook/MarginHorizontal","1cm");
    s.setValue("TextBook/MarginVertical","1cm");
}

