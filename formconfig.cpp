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
