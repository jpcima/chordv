#include "langnotes.h"

LangNotes::LangNotes()
{
    QStringList listfrench;
    listfrench<<"Do"<<"Ré"<<"Mi"<<"Fa"<<"Sol"<<"La"<<"Si";
    m_lang["fr"]=listfrench;
    QStringList listgerman;
    listgerman<<"C"<<"D"<<"E"<<"F"<<"G"<<"A"<<"H";
    m_lang["de"]=listgerman;
    QStringList listenglish;
    listenglish<<"C"<<"D"<<"E"<<"F"<<"G"<<"A"<<"B";
    m_lang["en"]=listenglish;
    QStringList listhindi;
    listhindi<<"स "<< "रे"<<"ग" <<" म"<<"प"<<"ध" <<"नि";
    m_lang["hi"]<<listenglish;
    QStringList listjapaneese;
    listjapaneese<<"ハ"<<"ニ"<<"ホ"<<"ヘ"<<"ト"<<"イ"<<"ロ";
    m_lang["jp"]=listjapaneese;
    QStringList listrussian;
    listrussian <<"До"<<"Pe"<<"Mи"<<"фа"<<"Cоль"<<"ля"<<"Cи";
    m_lang["ru"]=listrussian;
    m_lang["it"]=listfrench;
    m_lang["es"]=listfrench;
    m_englishnote["C"]=0;
    m_englishnote["D"]=1;
    m_englishnote["E"]=2;
    m_englishnote["F"]=3;
    m_englishnote["G"]=4;
    m_englishnote["A"]=5;
    m_englishnote["B"]=6;

}

QString LangNotes::note(QString lang, QString englishnote)
{
    return m_lang[lang].at(m_englishnote[englishnote]);
}


