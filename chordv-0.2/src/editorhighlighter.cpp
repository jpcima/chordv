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
    QTextCharFormat format3;
    format3.setFontWeight(QFont::Bold);
    format3.setForeground(Qt::darkGreen);
    QTextCharFormat format4;
    format3.setFontWeight(QFont::Medium);
    format3.setForeground(Qt::darkGreen);


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
    QRegExp expression3("\\{(comment|c):[^}]+\\}");
    int index3 = text.indexOf(expression3);
    while ( index3>=0 ) {
        int length = expression3.matchedLength();
        setFormat(index3, length, format3);
        index3=text.indexOf(expression3,index3+length);
    }
    QRegExp expression4("\\{(comment_italic|ci):[^}]+\\}");
    int index4 = text.indexOf(expression4);
    while ( index4>=0 ) {
        int length = expression4.matchedLength();
        setFormat(index4, length, format4);
        index4=text.indexOf(expression4,index4+length);
    }

}

