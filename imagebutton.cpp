#include "imagebutton.h"
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

    QString image=QFileDialog::getOpenFileName(this,tr("Choose an Image file"),s.value("LastOpenedDirectory").toString(),tr("Image(*.jpg *.png)"));
    QRegExp exp(QString("^%1").arg(s.value("DirCurrentProject").toString()));
    m_image=image.replace(exp,"");
    if ( ! image.isEmpty())  emit ImageSelelected(m_image);
}

QString ImageButton::getImage()
{
    QSettings s;
    return s.value("DirCurrentProject").toString()+m_image;
}

void ImageButton::setImage(QString image)
{
   m_image=image;
   emit ImageSelelected(image);
}
