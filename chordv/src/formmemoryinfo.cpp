#include "formmemoryinfo.h"
#include "ui_formmemoryinfo.h"

#include <QSettings>

FormMemoryInfo::FormMemoryInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormMemoryInfo)
{
    ui->setupUi(this);
    Init();
    connect (ui->toolButtonFontMemory,SIGNAL(sendSelectedFont(QFont,QColor,QColor)), this,SLOT(ShowSelectedFont(QFont,QColor,QColor)));

}

void FormMemoryInfo::Init()
{
    QSettings s;
    ui->checkBoxFullScreenMemory->setChecked(s.value("Memory/FullScreenBoxMemory",false).toBool());
    ui->checkBoxScrollingTextMemory->setChecked(s.value("Memory/ScrollingTextMemory",false).toBool());
    ui->comboBoxPositionMemory->setCurrentIndex(s.value("Memory/PositionMemory",0).toInt());
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
    s.setValue("Memory/FullScreenBoxMemory", ui->checkBoxFullScreenMemory->isChecked());
    s.setValue("Memory/ScrollingTextMemory", ui->checkBoxScrollingTextMemory->isChecked());
    s.setValue("Memory/PositionMemory",ui->comboBoxPositionMemory->currentIndex());
    s.setValue("Memory/Font",ui->toolButtonFontMemory->getFont().toString());
    s.setValue("Memory/FontColor",ui->toolButtonFontMemory->getTextColor().name());
    s.setValue("Memory/BackgroundColor",ui->toolButtonFontMemory->getBackgroundColor().name());

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
