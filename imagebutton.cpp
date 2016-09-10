#include "imagebutton.h"
#include "util.h"
#include <QFileDialog>
#include <QSettings>

#include <QDebug>

ImageButton::ImageButton(QWidget *parent):QToolButton(parent)
{
    connect (this,SIGNAL(clicked(bool)),this,SLOT(SetImage(bool)));
}

void ImageButton::SetImage(bool)
{
    QSettings s;
    m_image=QFileDialog::getOpenFileName(this,tr("Choose an Image file"),Util::getLastDirectory(),tr("Image(*.jpg *.png)"));
    if ( ! m_image.isEmpty())  emit ImageSelelected(m_image);
}

QString ImageButton::getImage()
{
    QSettings s;
    if ( m_image.isEmpty()) return "";
    else return m_image;
}

void ImageButton::setImage(QString image)
{
   m_image=image;
   qDebug()<<image;
   emit ImageSelelected(image);
}
