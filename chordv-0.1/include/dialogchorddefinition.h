#ifndef DIALOGCHORDDEFINITION_H
#define DIALOGCHORDDEFINITION_H

#include <QDialog>
#include <QHash>
#include <QGraphicsScene>
#include <QModelIndex>
#include <QSqlTableModel>
#include <QTableView>
#include <QSqlQueryModel>
#include <QLabel>

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
    void SetChordLanguage(QString lang, QString minor);
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
    void currentRowChanged(QModelIndex index1, QModelIndex index2);
private:
    Ui::DialogChordDefinition *ui;
    QHash <QString, QString> m_chords;
    QString findName(QString chordstring, QString chordmin);
    QSqlTableModel *m_model;
    QSqlQueryModel *m_modelapprove;
    int m_index;
    int m_indexnonapproved;
    QString m_codelang;
    QString m_language;
    QString m_minor;

    void setError(QString message, int linenumber);
    void paintEvent(QPaintEvent *event);
    void setIcon(QLabel *label, bool status);
signals:
    void Error(QString message);
    void ChordToInsert(QString chord);
};


#endif // DIALOGCHORDDEFINITION_H
