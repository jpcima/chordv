#include "forminputoutputchord.h"
#include "ui_forminputoutputchord.h"
#include "language.h"

FormInputOutputChord::FormInputOutputChord(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormInputOutputChord)
{
    ui->setupUi(this);
    Language::setLanguageComboBox(ui->comboBoxInputChordLanguage);
    Language::setLanguageComboBox(ui->comboBoxOutputChordLanguage);
    ui->comboBoxMinorInput->addItems(Language::ListMinor(ui->comboBoxInputChordLanguage));
    ui->comboBoxMinorOutput->addItems(Language::ListMinor(ui->comboBoxOutputChordLanguage));
    SetInvisibleIfOnlyOnceChoice(ui->comboBoxMinorInput,ui->labelMinorInput);
    SetInvisibleIfOnlyOnceChoice(ui->comboBoxMinorOutput,ui->labelMinorOutput);
    connect (ui->comboBoxInputChordLanguage,SIGNAL(currentIndexChanged(QString)),this,SLOT(LanguageInputChanged(QString)));
    connect (ui->comboBoxOutputChordLanguage,SIGNAL(currentIndexChanged(QString)),this,SLOT(LanguageOutputChanged(QString)));

}

QString FormInputOutputChord::getInputLang()
{
    return ui->comboBoxInputChordLanguage->currentText();
}

QString FormInputOutputChord::getInputCodeLang()
{
    return ui->comboBoxInputChordLanguage->currentData().toString();
}

QString FormInputOutputChord::getOutputCodeLang()
{
    return ui->comboBoxOutputChordLanguage->currentData().toString();
}

QString FormInputOutputChord::getOutputLang()
{
    return ui->comboBoxOutputChordLanguage->currentText();
}

QString FormInputOutputChord::getInputMinor()
{
    return ui->comboBoxMinorInput->currentText();
}

QString FormInputOutputChord::getOutputMinor()
{
    return ui->comboBoxMinorOutput->currentText();
}



FormInputOutputChord::~FormInputOutputChord()
{
    delete ui;
}


void FormInputOutputChord::SetInvisibleIfOnlyOnceChoice( QComboBox *ptr , QLabel *ptrl)
{
    ptr->setVisible(ptr->count()>1);
    ptrl->setVisible(ptr->count()>1);

}

void FormInputOutputChord::LanguageOutputChanged(QString )
{
    ui->comboBoxMinorOutput->clear();
    ui->comboBoxMinorOutput->addItems(Language::ListMinor(ui->comboBoxOutputChordLanguage));
    SetInvisibleIfOnlyOnceChoice(ui->comboBoxMinorOutput,ui->labelMinorOutput);
}

void FormInputOutputChord::LanguageInputChanged(QString     )
{
    ui->comboBoxMinorInput->clear();
    ui->comboBoxMinorInput->addItems(Language::ListMinor(ui->comboBoxInputChordLanguage));
    SetInvisibleIfOnlyOnceChoice(ui->comboBoxMinorInput,ui->labelMinorInput);
}

