#ifndef SPINBOXUNIT_H
#define SPINBOXUNIT_H

#include <QWidget>
#include <QHBoxLayout>
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QSpacerItem>

class SpinBoxUnit : public QWidget
{
    Q_OBJECT

public:
    enum unit { mm,cm,in};
    explicit SpinBoxUnit(QWidget *parent = 0);
    double getValue() ;
    double getValueInUnit();
    QString getUnit();
    SpinBoxUnit::unit string2unit(QString i);
    void setValue(QString valunit);
public slots:
     void setValue(double val, unit u=mm);
private slots:
    void changeUnit( int value);

private:
    double toMM(double value, unit u);
    double fromMM(double value);
    void Disconnect();
    void Connect();
    int unit2int(unit u);
     unit int2unit (int i);

    double m_value; // always in millimeters
    unit m_unit;
    QHBoxLayout *m_layout;
    QDoubleSpinBox *m_doublespinbox;
    QComboBox *m_cbunit;
    QSpacerItem *m_spacer;
    double convert(int value, unit u);





};

#endif // SPINBOXUNIT_H
