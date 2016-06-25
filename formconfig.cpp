#include "formconfig.h"
#include "ui_formconfig.h"

#include <QDebug>
#include <QRegExp>
#include <QLineEdit>
#include <QSettings>
#include "colorbutton.h"
#include "examplelabel.h"


FormConfig::FormConfig(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormConfig)
{
    ui->setupUi(this);
    m_parent=parent;
    connect (ui->checkBoxCover,SIGNAL(stateChanged(int)),this,SLOT(setCover(int)));
    foreach (FontButton *w ,m_parent->findChildren<FontButton*>())
        connect (w,SIGNAL(sendSelectedFont(QFont,QColor,QColor)),this,SLOT(displayFont(QFont,QColor,QColor)));
    connect(ui->comboBoxMediaBox,SIGNAL(currentTextChanged(QString)),this,SLOT(SizeChanged(QString)));
    connect(ui->toolButtonCoverImage,SIGNAL(ImageSelelected(QString)),this,SLOT(displayThumb(QString)));
    Init();
}

FormConfig::~FormConfig()
{
    delete ui;
}

void FormConfig::SizeChanged(QString value)
{
    ui->doubleSpinBoxPageHeight->setValue(ui->comboBoxMediaBox->getHeight());
    ui->doubleSpinBoxPageWidth->setValue(ui->comboBoxMediaBox->getWidth()) ;
    ui->comboBoxPageHeithUnit->setCurrentText(ui->comboBoxMediaBox->getUnit());
    ui->comboBoxPageWidthUnit->setCurrentText(ui->comboBoxMediaBox->getUnit());
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
    QRegExp spu ("^spu(.*)") ;
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
    else if ( var.endsWith("Unit") && var.startsWith("comboBox") )
    {
            foreach (QComboBox *w , m_parent->findChildren<QComboBox*>(var)) w->setCurrentText(value.toString());
    }
    else if ( var.startsWith("spinBox"))
    {
           foreach (QSpinBox *w ,m_parent->findChildren<QSpinBox*>(var)) w->setValue(value.toInt());

    }
    else if ( var.startsWith("doubleSpinBox") )
    {
           foreach (QDoubleSpinBox *w ,m_parent->findChildren<QDoubleSpinBox*>(var)) w->setValue(value.toDouble());

    }
    else if ( var.endsWith("Image"))
    {

        foreach (ImageButton *w ,m_parent->findChildren<ImageButton*>(QString("toolButton")+var))
            w->setImage(value.toString());

    }
    else if ( var.endsWith("MediaBox"))
    {
        foreach (PageSize *w ,m_parent->findChildren<PageSize*>(QString("comboBoxMediaBox")))
        {
            w->setCurrentText(value.toString());
        }

    }

   // else emit sendLog(QString ("Notice: (à finir) %1 => %2").arg(var).arg(value.toString()));

}

void FormConfig::Init()
{
    ui->checkBoxCover->setChecked(false);
    ui->checkBoxFullScreenMode->setChecked(false);
    ui->checkBoxTitleInUppercase->setChecked(false);
    ui->comboBoxChordDiagramHSizeUnit->setCurrentText("cm");
    ui->comboBoxChordInText->setCurrentIndex(0);
    ui->comboBoxChordLang->setCurrentIndex(0);
    ui->comboBoxMarginHorizontalUnit->setCurrentText("cm");
    ui->comboBoxMarginVerticalUnit->setCurrentText("cm");
    ui->comboBoxMediaBox->setCurrentText("A4");
    ui->comboBoxTocColumnNUmber->setCurrentIndex(0);
    ui->comboBoxTocVerticalSpacingUnit->setCurrentText("cm");
    ui->lineEditOutFile->clear();
    ui->doubleSpinBoxChordDiagramHSize->setValue(2);
    ui->doubleSpinBoxMarginHorizontal->setValue(5);
    ui->doubleSpinBoxMarginVertical->setValue(5);
    ui->doubleSpinBoxTocVerticalSpacing->setValue(1);
    ui->toolButtonChordFont->setFont(QFont());
    ui->toolButtonCoverFont->setFont(QFont());
    ui->toolButtonNormalFont->setFont(QFont());
    ui->toolButtonSubtitleFont->setFont(QFont());
    ui->toolButtonTitleFont->setFont(QFont());
    ui->toolButtonTocFont->setFont(QFont());
    ui->toolButtonPageNumberFont->setFont(QFont());
    ui->toolButtonChordFont->setColor(QColor("black"));
    ui->toolButtonCoverFont->setColor(QColor("black"));
    ui->toolButtonNormalFont->setColor(QColor("black"));
    ui->toolButtonSubtitleFont->setColor(QColor("black"));
    ui->toolButtonTitleFont->setColor(QColor("black"));
    ui->toolButtonPageNumberFont->setColor(QColor("black"));
    ui->toolButtonTocFont->setBackgroundColor(QColor("white"));
    ui->toolButtonChordFont->setBackgroundColor(QColor("white"));
    ui->toolButtonCoverFont->setBackgroundColor(QColor("white"));
    ui->toolButtonNormalFont->setBackgroundColor(QColor("white"));
    ui->toolButtonSubtitleFont->setBackgroundColor(QColor("white"));
    ui->toolButtonTitleFont->setBackgroundColor(QColor("white"));
    ui->toolButtonTocFont->setBackgroundColor(QColor("white"));
    ui->toolButtonPageNumberFont->setBackgroundColor(QColor("white"));
    ui->toolButtonCoverImage->setImage("");




}

void FormConfig::Save(QString filename, QString section)
{
    QSettings sf(filename,QSettings::IniFormat);
    foreach (FontButton *w ,m_parent->findChildren<FontButton*>())
    {
        if ( ! w->isEnabled() ) continue;
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
    foreach (ColorButton *w ,m_parent->findChildren<ColorButton*>() )
    {
        if ( ! w->isEnabled() ) continue;
        QRegExp tb("^toolButton");
        QRegExp c("Color$");
        QString name=w->objectName().replace(tb,"").replace(c,"");
        sf.setValue(QString("%1/%2Color").arg(section).arg(name),w->getColor().name());
    }
    foreach (ImageButton *w ,m_parent->findChildren<ImageButton*>())
    {
        if ( ! w->isEnabled() ) continue;
        QRegExp tb("^toolButton");
        QRegExp i("Image$");
        QString name=w->objectName().replace(tb,"").replace(i,"");
        sf.setValue(QString("%1/%2Color").arg(section).arg(name),w->getImage());
    }
    foreach (QCheckBox *w ,m_parent->findChildren<QCheckBox*>())
    {
         if ( ! w->isEnabled() ) continue;
         QRegExp tb("^toolButton");
         QString name=w->objectName().replace(tb,"");
         sf.setValue(QString("%1/%2").arg(section).arg(name),w->isChecked()?"1":"0");
    }
    foreach (QComboBox *w ,m_parent->findChildren<QComboBox*>())
    {
         if ( ! w->isEnabled() ) continue;
         QRegExp tb("^comboBox");
         QString name=w->objectName().replace(tb,"");
         sf.setValue(QString("%1/%2").arg(section).arg(name),w->currentText());
    }
    foreach (QLineEdit *w ,m_parent->findChildren<QLineEdit*>())
    {
         if ( ! w->isEnabled() ) continue;
         QRegExp tb("^lineEdit");
         QString name=w->objectName().replace(tb,"");
         sf.setValue(QString("%1/%2").arg(section).arg(name),w->text());
    }
    foreach (QSpinBox *w ,m_parent->findChildren<QSpinBox*>())
    {
         if ( ! w->isEnabled() ) continue;
         QRegExp tb("^spinBox");
         QString name=w->objectName().replace(tb,"");
         sf.setValue(QString("%1/%2").arg(section).arg(name),w->value());
    }
    foreach (QDoubleSpinBox *w ,m_parent->findChildren<QDoubleSpinBox*>())
    {
         if ( ! w->isEnabled() ) continue;
         QRegExp tb("^doubleSpinBox");
         QString name=w->objectName().replace(tb,"");
         sf.setValue(QString("%1/%2").arg(section).arg(name),w->value());
    }

    sf.sync();
}



void FormConfig::displayFont ( QFont font, QColor text, QColor background)
{
    QString name=sender()->objectName().replace("toolButton","");
    name=QString("label%1Example").arg(name);
    foreach (ExampleLabel *w ,m_parent->findChildren<ExampleLabel*>(name))
    w->setColor(font,text,background);

}


void FormConfig::displayThumb(QString image)
{
    QSettings s;
    if (image.isEmpty()){ ui->labelCoverViewImage->setPixmap(QPixmap());return;}
    QPixmap pix(QString("%1/%2").arg(s.value("DirCurrentProject").toString()).arg(image));
    QPixmap p=pix.scaledToWidth(150);
    ui->labelCoverViewImage->setPixmap(p);
}
