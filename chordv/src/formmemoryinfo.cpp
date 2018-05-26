#include "formmemoryinfo.h"
#include "ui_formmemoryinfo.h"

#include <QSettings>

FormMemoryInfo::FormMemoryInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormMemoryInfo)
{
    ui->setupUi(this);
    Init();
    SetUnsetPosition();
    connect (ui->toolButtonFontMemory,SIGNAL(sendSelectedFont(QFont,QColor,QColor)), this,SLOT(ShowSelectedFont(QFont,QColor,QColor)));
    connect (ui->checkBoxFullScreenMemory,SIGNAL(clicked(bool)),this,SLOT(SetUnsetPosition()));

}

void FormMemoryInfo::Init()
{
    QSettings s;
    ui->checkBoxFullScreenMemory->setChecked(s.value("Memory/FullScreenBox",false).toBool());
    ui->checkBoxShowRythmTextMemory->setChecked(s.value("Memory/ShowRythm",false).toBool());
    ui->checkBoxTwoLines->setChecked(s.value("Memory/ShowTwoLines",false).toBool());
    ui->comboBoxPositionMemory->setCurrentIndex(s.value("Memory/Position",0).toInt());
    ui->toolButtonFontMemory->setColor(QColor(s.value("Memory/FontColor","black").toString()));
    ui->toolButtonFontMemory->setBackgroundColor(QColor(s.value("Memory/BackgroundColor","white").toString()));
    QFont f;
    f.fromString(s.value("Memory/Font").toString());
    ui->toolButtonFontMemory->setFont(f);

    ShowSelectedFont(ui->toolButtonFontMemory->getFont(),ui->toolButtonFontMemory->getTextColor(),ui->toolButtonFontMemory->getBackgroundColor());
}

void FormMemoryInfo::Save()
{
    QSettings s;
    s.setValue("Memory/FullScreenBox", ui->checkBoxFullScreenMemory->isChecked());
    s.setValue("Memory/ShowRythm", ui->checkBoxShowRythmTextMemory->isChecked());
    s.setValue("Memory/Position",ui->comboBoxPositionMemory->currentIndex());
    s.setValue("Memory/ShowTwoLines",ui->checkBoxTwoLines->isChecked());
    s.setValue("Memory/Font",ui->toolButtonFontMemory->getFont().toString());
    s.setValue("Memory/FontColor",ui->toolButtonFontMemory->getTextColor().name());
    s.setValue("Memory/BackgroundColor",ui->toolButtonFontMemory->getBackgroundColor().name());

}

QFont FormMemoryInfo::getFont()
{
    return ui->toolButtonFontMemory->getFont();
}

QColor FormMemoryInfo::getBackgroundColor()
{
    return ui->toolButtonFontMemory->getBackgroundColor();
}

QColor FormMemoryInfo::getTextColor()
{
    return ui->toolButtonFontMemory->getTextColor();
}

bool FormMemoryInfo::getShowRythm()
{
    return ui->checkBoxShowRythmTextMemory->isChecked();
}

bool FormMemoryInfo::getFullscreenMode()
{
    return ui->checkBoxFullScreenMemory->isChecked();
}

int FormMemoryInfo::getPosition()
{
    return ui->comboBoxPositionMemory->currentIndex();
}

bool FormMemoryInfo::getShowTwoLines()
{
     return ui->checkBoxTwoLines->isChecked();
}

FormMemoryInfo::~FormMemoryInfo()
{
    delete ui;
}

void FormMemoryInfo::ShowSelectedFont(QFont font,QColor textcolor,QColor backgroundcolor)
{
    ui->labelExample->setFont(font);
    ui->labelExample->setStyleSheet(QString("QLabel { background-color: %1; color: %2;}").arg(backgroundcolor.name()).arg(textcolor.name()));
}


void FormMemoryInfo::SetUnsetPosition()
{
  ui ->comboBoxPositionMemory->setDisabled(ui->checkBoxFullScreenMemory->isChecked());
}
