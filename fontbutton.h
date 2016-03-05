#ifndef FONTBUTTON_H
#define FONTBUTTON_H

#include <QToolButton>

class FontButton : public QToolButton
{
    Q_OBJECT
public:
    FontButton(QWidget *parent);
private:
    QColor m_textcolor;
    QColor m_backgroundcolor;
    QFont m_font;
private slots:
    void setFont(bool );
    void SelectedFont(QFont font, QColor text, QColor background);
};

#endif // FONTBUTTON_H
