#include "imagebutton.h"
#include <QFileDialog>
#include <QSettings>


ImageButton::ImageButton(QWidget *parent):QToolButton(parent)
{
 connect (this,SIGNAL(clicked(bool)),this,SLOT(setImage(bool)));
}

void ImageButton::setImage(bool)
{
    QSettings s;
    m_image=QFileDialog::getOpenFileName(this,tr("Choose an Image file"),s.value("LastOpenedDirectory").toString(),tr("Image(*.jpg *.png)"));
    if ( ! m_image.isEmpty())  emit ImageSelelected(m_image);
}
