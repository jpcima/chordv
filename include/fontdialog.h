#ifndef FONTDIALOG_H
#define FONTDIALOG_H

#include <QFontDialog>


class FontDialog : public QFontDialog
{
    Q_OBJECT

public:
    explicit FontDialog(QWidget *parent = 0);
    ~FontDialog();
};

#endif // FONTDIALOG_H
