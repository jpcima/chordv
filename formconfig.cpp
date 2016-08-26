#include "formconfig.h"
#include "ui_formconfig.h"

#include <QDebug>
#include <QRegExp>
#include <QLineEdit>
#include <QSettings>
#include "colorbutton.h"
#include "examplelabel.h"
#include "settings.h"

FormConfig::FormConfig(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormConfig)
{
    ui->setupUi(this);
    SetConfigFromInit();
    m_parent=parent;
    connect (ui->checkBoxCover,SIGNAL(stateChanged(int)),this,SLOT(setCover(int)));
    foreach (FontButton *w ,m_parent->findChildren<FontButton*>())
        connect (w,SIGNAL(sendSelectedFont(QFont,QColor,QColor)),this,SLOT(displayFont(QFont,QColor,QColor)));
    connect(ui->comboBoxMediaBox,SIGNAL(currentTextChanged(QString)),this,SLOT(SizeChanged(QString)));
    connect(ui->checkBoxLandscape,SIGNAL(clicked(bool)),this,SLOT(SizeChanged(bool)));
    connect(ui->toolButtonCoverImage,SIGNAL(ImageSelelected(QString)),this,SLOT(displayThumb(QString)));
    connect(ui->spuPageHeight,SIGNAL(valueChanged(double)),this,SLOT(FindSize(double)));
    connect(ui->spuPageWidth,SIGNAL(valueChanged(double)),this,SLOT(FindSize(double)));
    connect(ui->toolButtonSuppressCoverImage,SIGNAL(clicked(bool)),this,SLOT(deleteCoverImage(bool)));
}

void FormConfig::SizeChanged(bool)
{
    Calculate();
}

void FormConfig::SizeChanged(QString)
{
    Calculate();
}

void FormConfig::Calculate()
{
    double height=ui->comboBoxMediaBox->getHeight();
    double width=ui->comboBoxMediaBox->getWidth();
    QString unit=ui->comboBoxMediaBox->getUnit();
     if ( ui->checkBoxLandscape->isChecked() )
     {
         double l=width;
         width=height;
         height=l;
     }
    ui->spuPageHeight->setValue(height,ui->spuPageHeight->string2unit(unit));
    ui->spuPageWidth->setValue(width,ui->spuPageWidth->string2unit(unit));
}

void FormConfig::FindSize(double)
{
    bool landscape;
    QString val=ui->comboBoxMediaBox->findSize(ui->spuPageWidth->getValue(),ui->spuPageHeight->getValue(),landscape);
    ui->comboBoxMediaBox->disconnect();
    ui->checkBoxLandscape->disconnect();
    ui->comboBoxMediaBox->setCurrentTextByValue(val);
    ui->checkBoxLandscape->setChecked(landscape);
    connect(ui->comboBoxMediaBox,SIGNAL(currentTextChanged(QString)),this,SLOT(SizeChanged(QString)));
    connect(ui->checkBoxLandscape,SIGNAL(clicked(bool)),this,SLOT(SizeChanged(bool)));
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
    foreach (SpinBoxUnit *w ,m_parent->findChildren<SpinBoxUnit*>(value))
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
    ui->comboBoxTitlePosition->setEnabled(val);
    ui->toolButtonSuppressCoverImage->setEnabled(val);
}



void FormConfig::setValue(QString var, QVariant value)
{
    QRegExp spu ("^spu(.*)") ;
    if ( var.contains(spu))
    {
        foreach (SpinBoxUnit *w , m_parent->findChildren<SpinBoxUnit*>(var)) w->setValue(value.toString());

    }
    if ( var.endsWith("Font"))
    {
        QFont f;
        f.fromString(value.toString());
        foreach (FontButton *w ,m_parent->findChildren<FontButton*>(QString("toolButton")+var))  w->setFont(f);
    }
    else if ( var.endsWith("FontColor"))
    {
        foreach (FontButton *w ,m_parent->findChildren<FontButton*>(QString("toolButton")+var))  w->setColor(QColor(value.toString()));
    }
    else if ( var.endsWith("FontBackgroundColor"))
    {
        foreach (FontButton *w ,m_parent->findChildren<FontButton*>(QString("toolButton")+var))  w->setBackgroundColor(QColor(value.toString()));
    }
    else if ( var==QString("Cover") )
    {
         ui->checkBoxCover->setChecked(value.toInt()==1);
    }
  else if ( var.startsWith("comboBox") )
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


void FormConfig::InitDefault(Classes c)
{

    QString classe=classe2String(c);
    Settings *s;
    if( m_configFileName.isEmpty()) s = new Settings() ;
    else s= new Settings(m_configFileName);
    ui->checkBoxCover->setChecked(s->value(QString("%1/Cover").arg(classe),true).toBool());
    ui->checkBoxFullScreenMode->setChecked(s->value(QString("%1/FullScreenMode").arg(classe),false).toBool());
    ui->checkBoxTitleInUppercase->setChecked(s->value(QString("%1/TitleInUppercase").arg(classe),false).toBool());
    ui->comboBoxChordInText->setCurrentIndex(s->value(QString("%1/ChordInText").arg(classe),0).toInt());
    ui->comboBoxChordLang->setCurrentText(s->value(QString("%1/ChordLang").arg(classe),"English").toString());
    ui->comboBoxTocColumnNUmber->setCurrentIndex(s->value(QString("%1/TocColumnNumber").arg(classe),0).toInt());
    ui->comboBoxTitlePosition->setCurrentText(s->value(QString("%1/TitlePosition").arg(classe),"1/3").toString());
    ui->lineEditOutFile->setText(s->value(QString("%1/OutFile").arg(classe),"out").toString());
    ui->spuChordHorizontalSize->setValue(s->value(QString("%1/ChordHorizontalSize").arg(classe),"2mm").toString());
    ui->spuHorizontalMargin->setValue(s->value(QString("%1/HorizontalMargin").arg(classe),"2mm").toString());
    ui->spuVerticalMargin->setValue(s->value(QString("%1/VerticalMargin").arg(classe),"5mm").toString());
    ui->spuTocVerticalSpacing->setValue(s->value(QString("%1/VerticalSpacing").arg(classe),"1mm").toInt());
    ui->spuPageHeight->setValue(s->value(QString("%1/PageHeight").arg(classe),"297mm").toString());
    ui->spuPageWidth->setValue(s->value(QString("%1/PageWidth").arg(classe),"210mm").toString());
    QFont f;
    f.fromString(s->value(QString("%1/ChordFont").arg(classe),QFont().toString()).toString());
    ui->toolButtonChordFont->setFont(f);
    f.fromString(s->value(QString("%1/CoverFont").arg(classe),QFont().toString()).toString());
    ui->toolButtonCoverFont->setFont(f);
    f.fromString(s->value(QString("%1/NormalFont").arg(classe),QFont().toString()).toString());
    ui->toolButtonNormalFont->setFont(f);
    f.fromString(s->value(QString("%1/SubtitleFont").arg(classe),QFont().toString()).toString());
    ui->toolButtonSubtitleFont->setFont(f);
    f.fromString(s->value(QString("%1/TitleFont").arg(classe),QFont().toString()).toString());
    ui->toolButtonTitleFont->setFont(f);
    f.fromString(s->value(QString("%1/TocFont").arg(classe),QFont().toString()).toString());
    ui->toolButtonTocFont->setFont(f);
    f.fromString(s->value(QString("%1/PageNumberFont").arg(classe),QFont().toString()).toString());
    ui->toolButtonPageNumberFont->setFont(f);
    ui->toolButtonChordFont->setColor(QColor(s->value(QString("%1/ChordFontColor").arg(classe),"black").toString()));
    ui->toolButtonCoverFont->setColor(QColor(s->value(QString("%1/CoverFontColor").arg(classe),"black").toString()));
    ui->toolButtonNormalFont->setColor(QColor(s->value(QString("%1/NormalFontColor").arg(classe),"black").toString()));
    ui->toolButtonSubtitleFont->setColor(QColor(s->value(QString("%1/SubtitleFontColor").arg(classe),"black").toString()));
    ui->toolButtonTitleFont->setColor(QColor(s->value(QString("%1/TitleFontColor").arg(classe),"black").toString()));
    ui->toolButtonPageNumberFont->setColor(QColor(s->value(QString("%1/PageNumberFontColor").arg(classe),"black").toString()));
    ui->toolButtonTocFont->setBackgroundColor(QColor(s->value(QString("%1/TocFontColor").arg(classe),"black").toString()));
    ui->toolButtonChordFont->setBackgroundColor(QColor(s->value(QString("%1/ChordFontBackgoundColor").arg(classe),"white").toString()));
    ui->toolButtonCoverFont->setBackgroundColor(QColor(s->value(QString("%1/CoverFontBackgroundColor").arg(classe),"white").toString()));
    ui->toolButtonNormalFont->setBackgroundColor(QColor(s->value(QString("%1/NormalFontBackgoundColor").arg(classe),"white").toString()));
    ui->toolButtonSubtitleFont->setBackgroundColor(QColor(s->value(QString("%1/SubtitleFontBackgoundColor").arg(classe),"white").toString()));
    ui->toolButtonTitleFont->setBackgroundColor(QColor(s->value(QString("%1/TitleFontBackgoundColor").arg(classe),"white").toString()));
    ui->toolButtonTocFont->setBackgroundColor(QColor(s->value(QString("%1/TocFontBackgoundColor").arg(classe),"white").toString()));
    ui->toolButtonPageNumberFont->setBackgroundColor(QColor(s->value(QString("%1/PageNumberFontBackgoundColor").arg(classe),"white").toString()));
    ui->toolButtonCoverImage->setImage(s->value(QString("%1/CoverImage").arg(classe),"").toString());
    delete s;
}

void FormConfig::SetConfigFromFile(QString FileName)
{
    m_configFileName=FileName;
}

void FormConfig::SetConfigFromInit()
{
    m_configFileName="";
}


void FormConfig::Save(QString filename, Classes classe)
{
    QString section=classe2String(classe);
    QSettings sf(filename,QSettings::IniFormat);

    foreach (FontButton *w ,m_parent->findChildren<FontButton*>())
    {
        if ( ! w->isEnabled() ) continue;
        QRegExp tb("^toolButton");
        QRegExp f("Font$");
        QString name=w->objectName().replace(tb,"").replace(f,"");
        sf.setValue(QString("%1/%2Font").arg(section).arg(name),w->getFont().toString());
        sf.setValue(QString("%1/%2FontBackgroundColor").arg(section).arg(name),w->getTextColor().name());
        sf.setValue(QString("%1/%2FontColor").arg(section).arg(name),w->getBackgroundColor().name());
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
        sf.setValue(QString("%1/%2Image").arg(section).arg(name),w->getImage());
    }
    foreach (QCheckBox *w ,m_parent->findChildren<QCheckBox*>())
    {
         if ( ! w->isEnabled() ) continue;
         QRegExp tb("^checkBox");
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
    foreach (SpinBoxUnit *w ,m_parent->findChildren<SpinBoxUnit*>())
    {
         if ( ! w->isEnabled() ) continue;
         QRegExp tb("^spu");
         QString name=w->objectName().replace(tb,"");
         sf.setValue(QString("%1/%2").arg(section).arg(name),w->valueunit());
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
{    QString name=sender()->objectName().replace("toolButton","");
    name=QString("label%1Example").arg(name);
    foreach (ExampleLabel *w ,m_parent->findChildren<ExampleLabel*>(name))
    w->setColor(font,text,background);

}


void FormConfig::displayThumb(QString image)
{

    QSettings *s;
    if ( m_configFileName.isEmpty() ) s= new QSettings;
    else s= new QSettings(m_configFileName);
    if (image.isEmpty()){ ui->labelCoverViewImage->setPixmap(QPixmap());return;}
    QPixmap pix(QString("%1/%2").arg(s->value("DirCurrentProject").toString()).arg(image));
    QPixmap p=pix.scaledToWidth(150);
    ui->labelCoverViewImage->setPixmap(p);
    delete s;
}


void FormConfig::deleteCoverImage(bool)
{
    ui->labelCoverViewImage->setPixmap(QPixmap());
    ui->toolButtonCoverImage->setImage("");
}

QString FormConfig::classe2String(Classes name)
{
    if ( name == Memory ) return "Memory";
    if ( name == Text ) return "Text";
    if ( name == Lyrics) return "Lyrics";
    else  return "Chord";
}
