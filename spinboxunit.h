#ifndef SPINBOXUNIT_H
#define SPINBOXUNIT_H

#include <QWidget>
#include <QHBoxLayout>
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QLabel>

class SpinBoxUnit : public QWidget
{
    Q_OBJECT

public:
    enum unit { mm,cm,in};
    explicit SpinBoxUnit(QWidget *parent = 0);
    void init(QString label,double val, unit u=mm);
    void setValueMM(double val);
    void setValueCM(double val);
    void setValueIN(double val);
    void setValue(QString val);
    void setLabel(QString label);
    void setUnit( unit u);
    void setUnit (int i);
    double getValueCM();
    double getValueMM();
    double getValueIN();
private slots:
    void adjustValue( int value);
    void setValue(double val);
private:
    double m_value;
    QHBoxLayout *m_layout;
    QDoubleSpinBox *m_doublespinbox;
    QComboBox *m_cbunit;
    QLabel *m_label;
    unit m_unit;
    double convert(int value, unit u);
    int unit2int(unit u);
    unit string2unit( QString i);
    unit int2unit (int i);
    void adjustValue();
};

#endif // SPINBOXUNIT_H
