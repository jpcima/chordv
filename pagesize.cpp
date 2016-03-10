#include "pagesize.h"

#include <QRegExp>
#include <QDebug>

PageSize::PageSize(QWidget *parent) : QComboBox(parent)
{
    m_sizes.insert("A4","210x290 mm");
    m_sizes.insert("US Letter","8.5x11 in");
    m_sizes.insert("US Legal","8.5x14 in");
    m_sizes.insert("US Executive","7.2x10.5 in");
    m_sizes.insert("A0","841x1189 mm");
    m_sizes.insert("A1","594x841 mm");
    m_sizes.insert("A2","420x594 mm");
    m_sizes.insert("A3","297x420 mm");
    m_sizes.insert("A5","148x210 mm");
    m_sizes.insert("A6","105x148 mm");
    m_sizes.insert("A7","74x105 mm");
    m_sizes.insert("A8","52x74 mm");
    m_sizes.insert("A9","37x52 mm");
    m_sizes.insert("A10","26x37 mm");
    m_sizes.insert("B0","1414x1000 mm");
    m_sizes.insert("B1","1000x707 mm");
    m_sizes.insert("B2","707x500 mm");
    m_sizes.insert("B3","500x353 mm");
    m_sizes.insert("B4","353x250 mm");
    m_sizes.insert("B5","250x176 mm");
    m_sizes.insert("B6","176x125 mm");
    m_sizes.insert("B7","125x88 mm");
    m_sizes.insert("B8","88x62 mm");
    m_sizes.insert("B9","62x44 mm");
    m_sizes.insert("B10","44x31 mm");
    m_sizes.insert("Other","");
    this->insertItems(0,m_sizes.keys());
}

QString PageSize::getUnit()
{
    QString u;
    double w,h;
    getVals(w, h, u);
    return u;
}

double PageSize::getWidth()
{
    QString u;
    double w,h;
    getVals( w,  h,  u);
    return w;
}

double PageSize::getHeight()
{
    QString u;
    double w,h;
    getVals( w,  h,  u);
    return h;
}

void PageSize::setCurrentText(const QString &text)
{
    int val=this->findText(text);
    if ( val  != -1)
            QComboBox::setCurrentText(text);
    else
       {
        QComboBox::setCurrentText(tr("Other"));
        double w,h;
        QString u;
        getVals(text,w,h,u);
       }


}

void PageSize::getVals(double &w, double &h, QString &u)
{
    getVals(m_sizes[currentText()],w,h,u);
}

void PageSize::getVals(QString text,double &w, double &h, QString &u)
{
    QRegExp exp("(\\d{1,4})((\\.\\d){0,1})x(\\d{1,4})((\\.\\d){0,1}) ([a-z]{2})");
    if ( text.contains(exp))
    {
        QString weight=exp.cap(1);
        if (!exp.cap(3).isEmpty())
            weight+=exp.cap(3);
        QString height=exp.cap(4);
        if (!exp.cap(6).isEmpty())
            height+=exp.cap(6);
        u=exp.cap(7);
        w=weight.toDouble();
        h=height.toDouble();
    }
    else
    {
        u=QString("");
        h=w=0;
    }
}
