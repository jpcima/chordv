#ifndef DIALOGCHORDDEFINITION_H
#define DIALOGCHORDDEFINITION_H

#include <QDialog>
#include <QHash>
#include <QGraphicsScene>
#include <QModelIndex>
#include <QSqlTableModel>
#include <QTableView>
#include <QSqlQueryModel>

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
    void ActiveInsertButton();
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
    void InsertChord(bool);
    void ChordClickedNonApproved(QModelIndex index);
    void Approve();
    void DeleteApproved();
private:
    Ui::DialogChordDefinition *ui;
    QHash <QString, QString> m_chords;
    QString findName(QString chordstring, QString chordmin);
    QSqlTableModel *m_model;
    QSqlQueryModel *m_modelapprove;
    int m_index;
    int m_indexnonapproved;
    void setError(QString message, int linenumber);
    void paintEvent(QPaintEvent *event);
signals:
    void Error(QString message);
    void ChordToInsert(QString chord);
};


#endif // DIALOGCHORDDEFINITION_H
