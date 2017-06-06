#ifndef DIALOGTWOLINESTOCHORDPRO_H
#define DIALOGTWOLINESTOCHORDPRO_H

#include <QDialog>
#include <QMap>

namespace Ui {
class DialogTwoLinesToChordPro;
}

class DialogTwoLinesToChordPro : public QDialog
{
    Q_OBJECT

public:
    explicit DialogTwoLinesToChordPro(QWidget *parent = 0);
    ~DialogTwoLinesToChordPro();

private slots:
    void Convert();
private:
    Ui::DialogTwoLinesToChordPro *ui;
    bool isChords(QString line);
    QMap <int,QString> m_chords;
    bool MapIsEmpty();
    QString mixLineAndMap(QString line);
    void ConvertToMap(QString line);
    void ClearMap();
};

#endif // DIALOGTWOLINESTOCHORDPRO_H
