#ifndef DIALOGBAR_H
#define DIALOGBAR_H

#include <QDialog>

namespace Ui {
class DialogBar;
}

class DialogBar : public QDialog
{
    Q_OBJECT

public:
    explicit DialogBar(QWidget *parent = 0);
    ~DialogBar();
    bool canceled();
    QString value();
private slots:
    void Save();
private:
    Ui::DialogBar *ui;
    bool m_cancel;
    QString m_bar;
};

#endif // DIALOGBAR_H
