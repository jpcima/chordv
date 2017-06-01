#include "editorhighlighter.h"

#include <QDebug>

EditorHighlighter::EditorHighlighter(QTextDocument *parent):QSyntaxHighlighter(parent)
{
}

void EditorHighlighter::highlightBlock(const QString &text)
{
    QTextCharFormat format1;
    format1.setFontWeight(QFont::Bold);
    format1.setForeground(Qt::darkMagenta);
    QTextCharFormat format2;
    format2.setFontWeight(QFont::Bold);
    format2.setForeground(Qt::darkBlue);

    QString pattern1 = "\\{[^}]+\\}";
    QRegExp expression1(pattern1) ;
    int index1 = text.indexOf(expression1);
    while ( index1>=0 ) {
        int length = expression1.matchedLength();
        setFormat(index1, length, format1);
        index1=text.indexOf(expression1,index1+length);
    }
    QString pattern2 = "\\[[^]]+\\]";
    QRegExp expression2(pattern2) ;
    int index2 = text.indexOf(expression2);
    while ( index2>=0 ) {
        int length = expression2.matchedLength();
        setFormat(index2, length, format2);
        index2=text.indexOf(expression2,index2+length);
    }

}

