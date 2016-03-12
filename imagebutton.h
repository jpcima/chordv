#ifndef IMAGEBUTTON_H
#define IMAGEBUTTON_H

#include <QToolButton>
#include <QLabel>
class ImageButton : public QToolButton
{

   Q_OBJECT
public:
    ImageButton(QWidget *parent);
    QString getImage() ;
    void setImage(QString image) ;
private:
    QString m_image;
private slots:
    void SetImage(bool);
signals:
    void ImageSelelected( QString Image);
};

#endif // IMAGEBUTTON_H
