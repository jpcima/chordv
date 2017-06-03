#ifndef DIALOGCHORDDEFINITION_H
#define DIALOGCHORDDEFINITION_H

#include <QDialog>
#include <QHash>
#include <QGraphicsScene>
#include <QModelIndex>
#include <QSqlTableModel>
#include <QTableView>

#include <QPaintEvent>

namespace Ui {
class DialogChordDefinition;
}



class DialogChordDefinition : public QDialog
{
    Q_OBJECT

public:
    explicit DialogChordDefinition(QWidget *parent = 0);
    ~DialogChordDefinition();

protected slots:
    void ShowChords(QStringList chordnames,QString chortdstring);
private slots:
    void ShowChord(QModelIndex index);
    void Import();
    void ChordClicked(QModelIndex);
    void ModifyChord();
    void DeleteChord();
    void AddChord();
    void SortOnFret(bool checked);
    void SortOnIndex(bool checked);
    void SortOnChord(bool checked);
    void SetFilter(QString filter);
private:
    Ui::DialogChordDefinition *ui;
    QHash <QString, QString> m_chords;
    QString findName(QString chordstring, QString chordmin);
    QSqlTableModel *m_model;
    int m_index;
    void setError(QString message, int linenumber);
signals:
    void Error(QString message);
};


#endif // DIALOGCHORDDEFINITION_H
