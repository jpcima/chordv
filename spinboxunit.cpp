#include "spinboxunit.h"
#include <QDebug>

SpinBoxUnit::SpinBoxUnit(QWidget *parent) : QWidget(parent)
{
   m_layout=new QHBoxLayout(parent);
   m_doublespinbox = new QDoubleSpinBox();
   m_cbunit=new QComboBox();
   m_label=new QLabel();
   m_cbunit->addItem(tr("mm"));
   m_cbunit->addItem(tr("cm"));
   m_cbunit->addItem(tr("in"));
   m_layout->addWidget(m_label);
   m_layout->addWidget(m_doublespinbox);
   m_layout->addWidget(m_cbunit);
   m_cbunit->setMaximumWidth(60);
   m_doublespinbox->setMaximumWidth(120);
   m_doublespinbox->setMaximum(600);
   m_value=0;
   m_unit=mm;
   connect (m_doublespinbox,SIGNAL(valueChanged(double)),this,SLOT(setValue(double)));

}

void SpinBoxUnit::init(QString label, double val, SpinBoxUnit::unit u)
{
    m_unit=u;
    m_value=val;
    m_label->setText(label);
    adjustValue();
}

void SpinBoxUnit::setValue( QString val)
{
    QRegExp exp("^(.\d+)([a-z]*)$");
    QString unit;
    double value;
    if ( val.contains(exp))
    {
        value=exp.cap(1).toDouble();
        unit=exp.cap(2);
    }
    else
    {
        value=0;
        unit="mm" ;
    }

}

void SpinBoxUnit::setValue(double val)
{
    if ( m_unit == mm ) setValueMM(val);
    else if ( m_unit == cm ) setValueCM(val);
    else if ( m_unit == in ) setValueIN(val);
}

void SpinBoxUnit::setValueMM(double val)
{
    m_value=val;
    adjustValue();

}

void SpinBoxUnit::setValueCM(double val)
{
    m_value=val*10.0;
    adjustValue();
}

void SpinBoxUnit::setValueIN(double val)
{
    m_value=val*10.0*2.54;
    adjustValue();
}

void SpinBoxUnit::setLabel(QString label)
{
    m_label->setText(label);
}

double SpinBoxUnit::getValueCM()
{
    return getValueMM()/10.0;
}

double SpinBoxUnit::getValueIN()
{
    return getValueCM()/2.54;
}

double SpinBoxUnit::getValueMM()
{
    return m_value;
}


int SpinBoxUnit::unit2int( unit u)
{
    if ( u == mm ) return 0;
    else if ( u == cm  ) return 1;
    else return 2;
}

SpinBoxUnit::unit SpinBoxUnit::int2unit(int i)
{
    if (i==0) return mm;
    else if ( i == 1 ) return cm;
    else return in;

}

SpinBoxUnit::unit SpinBoxUnit::string2unit(QString i)
{
    if (i=="in") return in;
    else if ( i == "cm" ) return cm;
    else return mm;

}


void SpinBoxUnit::adjustValue()
{
    m_doublespinbox->disconnect();
    m_doublespinbox->setValue(convert(m_value,m_unit));
    connect (m_doublespinbox,SIGNAL(valueChanged(double)),this,SLOT(setValue(double)));
}

void SpinBoxUnit::setUnit(unit u)
{
    m_cbunit->disconnect();
    m_cbunit->setCurrentIndex(unit2int(u));
    m_doublespinbox->setValue(convert(m_value,u));
    connect(m_cbunit,SIGNAL(currentIndexChanged(int)),this,SLOT(adjustValue(int)));
}

void SpinBoxUnit::setUnit(int u)
{
    if ( u == 0 ) setUnit(mm);
    else if ( u == 1 ) setUnit(cm);
    else setUnit(in);
}

void SpinBoxUnit::adjustValue(int unit)
{
    m_doublespinbox->disconnect();
    if (unit == 0 ) m_unit=mm;
    else if ( unit == 1  ) m_unit=cm;
    else m_unit=in;
    m_doublespinbox->setValue(convert(m_value,m_unit));
    connect (m_doublespinbox,SIGNAL(valueChanged(double)),this,SLOT(setValue(double)));
}


double SpinBoxUnit::convert(int value, unit u)
{
    if ( u == mm ) return value;
    else if  ( u == cm ) return value/10.0;
    else  return value/10.0*2.54;
}


