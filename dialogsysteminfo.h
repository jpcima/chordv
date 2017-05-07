#ifndef DIALOGSYSTEMINFO_H
#define DIALOGSYSTEMINFO_H

#include <QDialog>

namespace Ui {
class DialogSystemInfo;
}

class DialogSystemInfo : public QDialog
{
    Q_OBJECT

public:
    explicit DialogSystemInfo(QWidget *parent = 0);
    ~DialogSystemInfo();

private:
    Ui::DialogSystemInfo *ui;
};

#endif // DIALOGSYSTEMINFO_H
