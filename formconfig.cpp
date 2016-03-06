#include "formconfig.h"
#include "ui_formconfig.h"

#include <QDebug>
#include <QRegExp>
#include <QLineEdit>
#include <QSettings>

FormConfig::FormConfig(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormConfig)
{
    ui->setupUi(this);
    m_parent=parent;
    //connect(ui->toolButtonCoverBackgroundColor,SIGNAL(ColorChanged(QColor),)
    connect (ui->checkBoxCover,SIGNAL(stateChanged(int)),this,SLOT(setCover(int)));
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


void FormConfig::setCover(int val)
{

    ui->labelCoverImage->setEnabled(val);
    ui->toolButtonCoverImage->setEnabled(val);
}

void FormConfig::setValue(QString var, QVariant value)
{
    if ( var.endsWith("Font"))
    {
        QString toolButton=var;
        if ( var.contains("Family")) { toolButton.replace("Family","");
            foreach (FontButton *w ,m_parent->findChildren<FontButton*>(QString("toolButton")+toolButton))  w->setFamily(value.toString()); }
         else if ( var.contains("Background"))  { toolButton.replace("Background","");
            foreach (FontButton *w ,m_parent->findChildren<FontButton*>(QString("toolButton")+toolButton))  w->setBackgroundColor(QColor(value.toString()));   }
        else if ( var.contains("Color")) { toolButton.replace("Color","");
            foreach (FontButton *w ,m_parent->findChildren<FontButton*>(QString("toolButton")+toolButton))  w->setColor(QColor(value.toString()));}
        else if ( var.contains("Size")) { toolButton.replace("Size","");
             foreach (FontButton *w ,m_parent->findChildren<FontButton*>(QString("toolButton")+toolButton))w->setPointsize(value.toInt());}
        else if ( var.contains("Weight")) {toolButton.replace("Weight","");
             foreach (FontButton *w ,m_parent->findChildren<FontButton*>(QString("toolButton")+toolButton)) w->setWeight(value.toInt());}
        else if ( var.contains("Italic")) {toolButton.replace("Italic","");
           foreach (FontButton *w ,m_parent->findChildren<FontButton*>(QString("toolButton")+toolButton))w->setItalic(value.toBool());}
    }
    else if ( var==QString("Cover") )
    {
         ui->checkBoxCover->setChecked(value.toInt()==1);
    }
    else if ( var.endsWith("Size") || var.startsWith("Margin") || var.endsWith("Spacing"))
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
   else emit sendLog(QString ("Notice: (à finir) %1 => %2").arg(var).arg(value.toString()));

}

void FormConfig::Save(QString filename, QString section)
{
    QSettings sf(filename,QSettings::IniFormat,this);
    foreach (FontButton *w ,m_parent->findChildren<FontButton*>())
    {
        if ( ! w->isVisible() ) continue;
        QRegExp tb("^toolButton");
        QRegExp f("Font$");
        QString name=w->objectName().replace(tb,"").replace(f,"");
        sf.setValue(QString("%1/%2FamilyFont").arg(section).arg(name),w->getFont().family());
        sf.setValue(QString("%1/%2SizeFont").arg(section).arg(name),w->getFont().pointSize());
        sf.setValue(QString("%1/%2WeightFont").arg(section).arg(name),w->getFont().weight());
        sf.setValue(QString("%1/%2ItalicFont").arg(section).arg(name),w->getFont().italic());
        sf.setValue(QString("%1/%2BackgroundFont").arg(section).arg(name),w->getBackgroundColor().name());
        sf.setValue(QString("%1/%2ColorFont").arg(section).arg(name),w->getBackgroundColor().name());
    }
    foreach (QCheckBox *w ,m_parent->findChildren<QCheckBox*>())
    {
         if ( ! w->isVisible() ) continue;
         QRegExp tb("^toolButton");
         QString name=w->objectName().replace(tb,"");
         sf.setValue(QString("%1/%2").arg(section).arg(name),w->isChecked()?"1":"0");
    }
    foreach (QComboBox *w ,m_parent->findChildren<QComboBox*>())
    {
         if ( ! w->isVisible() ) continue;
         QRegExp tb("^comboBox");
         QString name=w->objectName().replace(tb,"");
         sf.setValue(QString("%1/%2").arg(section).arg(name),w->currentText());
    }
    foreach (QLineEdit *w ,m_parent->findChildren<QLineEdit*>())
    {
         if ( ! w->isVisible() ) continue;
         QRegExp tb("^lineEdit");
         QString name=w->objectName().replace(tb,"");
         sf.setValue(QString("%1/%2").arg(section).arg(name),w->text());
    }

}

