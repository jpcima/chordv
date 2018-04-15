#ifndef DIALOGSEARCH_H
#define DIALOGSEARCH_H

#include <QDialog>

namespace Ui {
class DialogSearch;
}

class DialogSearch : public QDialog
{
    Q_OBJECT

public:
    explicit DialogSearch(QWidget *parent = 0);
    ~DialogSearch();

private slots:
    void Search();
    void BackwardSearch();
private:
    Ui::DialogSearch *ui;
signals:
    void Search(QString text, bool casesensitive, bool wordonly);
    void SearchBack(QString text, bool casesensitive, bool wordonly);
};

#endif // DIALOGSEARCH_H
