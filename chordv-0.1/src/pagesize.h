#ifndef PAGESIZE_H
#define PAGESIZE_H

#include <QComboBox>
#include <QMultiMap>


class PageSize : public QComboBox
{
public:
    PageSize( QWidget *parent);
    QString getUnit();
    double getWidth();
    double getHeight();
    void setCurrentText( const QString &text);
    QString findSize(double w, double h, bool &landscape);
    void setCurrentTextByValue(QString value);
private:
    QMap <QString, QString> m_sizes;
    void getVals(double &w,double &h,QString &u);
    void getVals(QString text,double &w,double &h,QString &u);
};

#endif // PAGESIZE_H
