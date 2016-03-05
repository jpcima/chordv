#include "formconfig.h"
#include "ui_formconfig.h"

#include <QDebug>
#include <QRegExp>
#include <QLineEdit>

FormConfig::FormConfig(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormConfig)
{
    ui->setupUi(this);
    m_parent=parent;
    //connect(ui->toolButtonCoverBackgroundColor,SIGNAL(ColorChanged(QColor),)
}

FormConfig::~FormConfig()
{
    delete ui;
}

void FormConfig::disableWidgets(QRegExp value)
{
    foreach (QLineEdit *w ,m_parent->findChildren<QLineEdit*>(value))
        w->setVisible(false);
    foreach (QLabel *w ,m_parent->findChildren<QLabel*>(value))
        w->setVisible(false);
    foreach (QToolButton *w ,m_parent->findChildren<QToolButton*>(value))
        w->setVisible(false);
    foreach (QSpinBox *w ,m_parent->findChildren<QSpinBox*>(value))
        w->setVisible(false);
    foreach (QCheckBox *w ,m_parent->findChildren<QCheckBox*>(value))
        w->setVisible(false);
    foreach (QComboBox *w ,m_parent->findChildren<QComboBox*>(value))
        w->setVisible(false);
}

void FormConfig::setValue(QString var, QVariant value)
{
    if ( var.contains("Font"))
    {

    }
    else if ( var.endsWith("Size") || var.startsWith("Margin"))
    {
        QRegExp exp("^([0-9]+)([a-zA-Z]+)");
        if ( value.toString().contains(exp))
        {
           int val=exp.cap(1).toInt();
           QString unit=exp.cap(2);

           foreach (QSpinBox *w ,m_parent->findChildren<QSpinBox*>(QString("spinBox")+var))
           {
               w->setValue(val);
           }
           foreach (QComboBox *w ,m_parent->findChildren<QComboBox*>(QString("comboBox")+var))
           {
               w->setCurrentText(unit);
           }

        }
        else  qDebug()<<"ERROR "<<var<<value;
    }
   else
    qDebug()<<var<<value;
}
