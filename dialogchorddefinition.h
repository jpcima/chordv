#ifndef DIALOGCHORDDEFINITION_H
#define DIALOGCHORDDEFINITION_H

#include <QDialog>
#include <QHash>
#include <QGraphicsScene>
#include <QModelIndex>

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
    void ShowChords(QStringList chordnames);
private slots:
    void ShowChord(QModelIndex index);
private:
    Ui::DialogChordDefinition *ui;
    QHash <QString, QString> m_chords;
    void InitialSetup();
};

#endif // DIALOGCHORDDEFINITION_H
