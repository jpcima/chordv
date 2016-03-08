#ifndef IMAGEBUTTON_H
#define IMAGEBUTTON_H

#include <QToolButton>

class ImageButton : public QToolButton
{

   Q_OBJECT
public:
    ImageButton(QWidget *parent);
    QString getImage() { return m_image;}
private:
    QString m_image;
private slots:
    void setImage(bool);
signals:
    void ImageSelelected( QString Image);
};

#endif // IMAGEBUTTON_H
