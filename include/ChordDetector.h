#ifndef CHORDDETECT_H
#define CHORDDETECT_H


#include <QStringList>
#include <QMap>
class ChordDetector
{
public:
    ChordDetector( QStringList listNotes);
    QStringList detectChord ();
private:

    int note2num(QString note);
    QString num2spellingElement(int inNum);
    int spellingElement2num(QString inSc);
    QStringList orderSpelling(QStringList spelling);
    QString convertToCodeIfPossible(QStringList spelling);
    QMap<int, QMap<int, QString> > getModeArray(QString spelling);
    QList<QStringList> m_list;
    void round(QStringList &list, int i);
    void CalculateAllChords(QStringList list, int first);
    QList<QStringList> getAllChords();
    QList<QStringList> m_listAllChords;
    QStringList m_listNotes;

};

#endif
