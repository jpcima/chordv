/********************************************************************************
** Form generated from reading UI file 'formconfig.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMCONFIG_H
#define UI_FORMCONFIG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <verticalspacing.h>
#include "examplelabel.h"
#include "fontbutton.h"
#include "imagebutton.h"
#include "pagesize.h"
#include "spinboxunit.h"

QT_BEGIN_NAMESPACE

class Ui_FormConfig
{
public:
    QVBoxLayout *verticalLayout_6;
    QTabWidget *tabWidget;
    QWidget *tab;
    QHBoxLayout *horizontalLayout_29;
    QVBoxLayout *verticalLayout_10;
    QHBoxLayout *horizontalLayout_13;
    QGroupBox *groupBoxPageSize;
    QHBoxLayout *horizontalLayout_20;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_18;
    QLabel *labelPageWidth;
    SpinBoxUnit *spuPageWidth;
    QHBoxLayout *horizontalLayout_19;
    QLabel *labelPageHeight;
    SpinBoxUnit *spuPageHeight;
    QHBoxLayout *horizontalLayout_21;
    QLabel *labelPageDimension;
    PageSize *comboBoxMediaBox;
    QCheckBox *checkBoxLandscape;
    QGroupBox *groupBoxMiscellaneous;
    QHBoxLayout *horizontalLayout_33;
    QVBoxLayout *verticalLayout_18;
    QHBoxLayout *horizontalLayout_6;
    QLabel *labelNormalFont;
    ExampleLabel *labelNormalFontExample;
    FontButton *toolButtonNormalFont;
    QHBoxLayout *horizontalLayout_3;
    QLabel *labelTitleFont;
    ExampleLabel *labelTitleFontExample;
    FontButton *toolButtonTitleFont;
    QHBoxLayout *horizontalLayout_4;
    QLabel *labelSubtitleFont;
    ExampleLabel *labelSubtitleFontExample;
    FontButton *toolButtonSubtitleFont;
    QHBoxLayout *horizontalLayout_27;
    QLabel *labelDuplex;
    QComboBox *comboBoxDuplex;
    QHBoxLayout *horizontalLayout_28;
    QGroupBox *groupBoxPageNumber;
    QHBoxLayout *horizontalLayout_7;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_26;
    QLabel *labelPageNumber;
    QComboBox *comboBoxPageNumber;
    QHBoxLayout *horizontalLayout_5;
    QLabel *labelPageNumberStyle;
    QComboBox *comboBoxPageNumberStyle;
    QHBoxLayout *horizontalLayout_14;
    QLabel *labelPageNumberFont;
    ExampleLabel *labelPageNumberFontExample;
    FontButton *toolButtonPageNumberFont;
    QGroupBox *groupBoxMargin;
    QHBoxLayout *horizontalLayout_25;
    QVBoxLayout *verticalLayout_9;
    QHBoxLayout *horizontalLayout_16;
    QLabel *labelMarginHorizontal;
    SpinBoxUnit *spuHorizontalMargin;
    QHBoxLayout *horizontalLayout_17;
    QLabel *labelMarginVertical;
    SpinBoxUnit *spuVerticalMargin;
    QWidget *tab_3;
    QVBoxLayout *verticalLayout_13;
    QGridLayout *gridLayout_2;
    QGroupBox *groupBoxCover;
    QVBoxLayout *verticalLayout_11;
    QVBoxLayout *verticalLayout;
    QCheckBox *checkBoxCover;
    QHBoxLayout *horizontalLayout_10;
    QLabel *labelCoverFont;
    ExampleLabel *labelCoverFontExample;
    FontButton *toolButtonCoverFont;
    QHBoxLayout *horizontalLayout_11;
    QLabel *labelTitlePosition;
    QComboBox *comboBoxTitlePosition;
    QHBoxLayout *horizontalLayout;
    QLabel *labelCoverImage;
    QLabel *labelCoverViewImage;
    QToolButton *toolButtonSuppressCoverImage;
    ImageButton *toolButtonCoverImage;
    QGroupBox *groupBoxChord;
    QVBoxLayout *verticalLayout_14;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_15;
    QLabel *labelChordDiagramHSize;
    SpinBoxUnit *spuChordHorizontalSize;
    QVBoxLayout *verticalLayout_12;
    QHBoxLayout *horizontalLayout_8;
    QLabel *labelChordFont;
    ExampleLabel *labelChordFontExample;
    FontButton *toolButtonChordFont;
    QHBoxLayout *horizontalLayout_22;
    QLabel *labelChordLang;
    QComboBox *comboBoxChordLang;
    QHBoxLayout *horizontalLayout_23;
    QLabel *labelChordLangInText;
    QComboBox *comboBoxChordInText;
    QGroupBox *groupBoxToc;
    QVBoxLayout *verticalLayout_7;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_24;
    QLabel *labelTocVerticalSpacing;
    VerticalSpacing *comboBoxTocVerticalSpacing;
    QHBoxLayout *horizontalLayout_31;
    QLabel *labelTocColumn;
    QComboBox *comboBoxTocColumnNumber;
    QHBoxLayout *horizontalLayout_36;
    QLabel *labelTocFont;
    ExampleLabel *labelTocFontExample;
    FontButton *toolButtonTocFont;
    QHBoxLayout *horizontalLayout_32;
    QLabel *labelTocSpaceCharacter;
    QComboBox *comboBoxTocSpaceCharacter;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label;
    QComboBox *comboBoxTocPosition;
    QGroupBox *groupBoxMiscellaneousContent;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_8;
    QHBoxLayout *horizontalLayout_9;
    QLabel *labelOutputFileName;
    QLineEdit *lineEditOutFile;
    QHBoxLayout *horizontalLayout_30;
    QLabel *labelVerticalSpacing;
    VerticalSpacing *comboBoxVerticalSpacing;
    QCheckBox *checkBoxFullScreenMode;
    QCheckBox *checkBoxTitleInUppercase;

    void setupUi(QWidget *FormConfig)
    {
        if (FormConfig->objectName().isEmpty())
            FormConfig->setObjectName(QStringLiteral("FormConfig"));
        FormConfig->resize(635, 472);
        verticalLayout_6 = new QVBoxLayout(FormConfig);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        tabWidget = new QTabWidget(FormConfig);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setTabPosition(QTabWidget::North);
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        horizontalLayout_29 = new QHBoxLayout(tab);
        horizontalLayout_29->setObjectName(QStringLiteral("horizontalLayout_29"));
        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setObjectName(QStringLiteral("verticalLayout_10"));
        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName(QStringLiteral("horizontalLayout_13"));
        groupBoxPageSize = new QGroupBox(tab);
        groupBoxPageSize->setObjectName(QStringLiteral("groupBoxPageSize"));
        horizontalLayout_20 = new QHBoxLayout(groupBoxPageSize);
        horizontalLayout_20->setObjectName(QStringLiteral("horizontalLayout_20"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        horizontalLayout_18 = new QHBoxLayout();
        horizontalLayout_18->setObjectName(QStringLiteral("horizontalLayout_18"));
        labelPageWidth = new QLabel(groupBoxPageSize);
        labelPageWidth->setObjectName(QStringLiteral("labelPageWidth"));

        horizontalLayout_18->addWidget(labelPageWidth);

        spuPageWidth = new SpinBoxUnit(groupBoxPageSize);
        spuPageWidth->setObjectName(QStringLiteral("spuPageWidth"));

        horizontalLayout_18->addWidget(spuPageWidth);


        verticalLayout_4->addLayout(horizontalLayout_18);

        horizontalLayout_19 = new QHBoxLayout();
        horizontalLayout_19->setObjectName(QStringLiteral("horizontalLayout_19"));
        labelPageHeight = new QLabel(groupBoxPageSize);
        labelPageHeight->setObjectName(QStringLiteral("labelPageHeight"));

        horizontalLayout_19->addWidget(labelPageHeight);

        spuPageHeight = new SpinBoxUnit(groupBoxPageSize);
        spuPageHeight->setObjectName(QStringLiteral("spuPageHeight"));

        horizontalLayout_19->addWidget(spuPageHeight);


        verticalLayout_4->addLayout(horizontalLayout_19);

        horizontalLayout_21 = new QHBoxLayout();
        horizontalLayout_21->setObjectName(QStringLiteral("horizontalLayout_21"));
        labelPageDimension = new QLabel(groupBoxPageSize);
        labelPageDimension->setObjectName(QStringLiteral("labelPageDimension"));

        horizontalLayout_21->addWidget(labelPageDimension);

        comboBoxMediaBox = new PageSize(groupBoxPageSize);
        comboBoxMediaBox->setObjectName(QStringLiteral("comboBoxMediaBox"));

        horizontalLayout_21->addWidget(comboBoxMediaBox);

        checkBoxLandscape = new QCheckBox(groupBoxPageSize);
        checkBoxLandscape->setObjectName(QStringLiteral("checkBoxLandscape"));

        horizontalLayout_21->addWidget(checkBoxLandscape);


        verticalLayout_4->addLayout(horizontalLayout_21);


        horizontalLayout_20->addLayout(verticalLayout_4);


        horizontalLayout_13->addWidget(groupBoxPageSize);

        groupBoxMiscellaneous = new QGroupBox(tab);
        groupBoxMiscellaneous->setObjectName(QStringLiteral("groupBoxMiscellaneous"));
        horizontalLayout_33 = new QHBoxLayout(groupBoxMiscellaneous);
        horizontalLayout_33->setObjectName(QStringLiteral("horizontalLayout_33"));
        verticalLayout_18 = new QVBoxLayout();
        verticalLayout_18->setObjectName(QStringLiteral("verticalLayout_18"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        labelNormalFont = new QLabel(groupBoxMiscellaneous);
        labelNormalFont->setObjectName(QStringLiteral("labelNormalFont"));

        horizontalLayout_6->addWidget(labelNormalFont);

        labelNormalFontExample = new ExampleLabel(groupBoxMiscellaneous);
        labelNormalFontExample->setObjectName(QStringLiteral("labelNormalFontExample"));

        horizontalLayout_6->addWidget(labelNormalFontExample);

        toolButtonNormalFont = new FontButton(groupBoxMiscellaneous);
        toolButtonNormalFont->setObjectName(QStringLiteral("toolButtonNormalFont"));

        horizontalLayout_6->addWidget(toolButtonNormalFont);


        verticalLayout_18->addLayout(horizontalLayout_6);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        labelTitleFont = new QLabel(groupBoxMiscellaneous);
        labelTitleFont->setObjectName(QStringLiteral("labelTitleFont"));

        horizontalLayout_3->addWidget(labelTitleFont);

        labelTitleFontExample = new ExampleLabel(groupBoxMiscellaneous);
        labelTitleFontExample->setObjectName(QStringLiteral("labelTitleFontExample"));

        horizontalLayout_3->addWidget(labelTitleFontExample);

        toolButtonTitleFont = new FontButton(groupBoxMiscellaneous);
        toolButtonTitleFont->setObjectName(QStringLiteral("toolButtonTitleFont"));

        horizontalLayout_3->addWidget(toolButtonTitleFont);


        verticalLayout_18->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        labelSubtitleFont = new QLabel(groupBoxMiscellaneous);
        labelSubtitleFont->setObjectName(QStringLiteral("labelSubtitleFont"));

        horizontalLayout_4->addWidget(labelSubtitleFont);

        labelSubtitleFontExample = new ExampleLabel(groupBoxMiscellaneous);
        labelSubtitleFontExample->setObjectName(QStringLiteral("labelSubtitleFontExample"));

        horizontalLayout_4->addWidget(labelSubtitleFontExample);

        toolButtonSubtitleFont = new FontButton(groupBoxMiscellaneous);
        toolButtonSubtitleFont->setObjectName(QStringLiteral("toolButtonSubtitleFont"));

        horizontalLayout_4->addWidget(toolButtonSubtitleFont);


        verticalLayout_18->addLayout(horizontalLayout_4);

        horizontalLayout_27 = new QHBoxLayout();
        horizontalLayout_27->setObjectName(QStringLiteral("horizontalLayout_27"));
        labelDuplex = new QLabel(groupBoxMiscellaneous);
        labelDuplex->setObjectName(QStringLiteral("labelDuplex"));

        horizontalLayout_27->addWidget(labelDuplex);

        comboBoxDuplex = new QComboBox(groupBoxMiscellaneous);
        comboBoxDuplex->setObjectName(QStringLiteral("comboBoxDuplex"));

        horizontalLayout_27->addWidget(comboBoxDuplex);


        verticalLayout_18->addLayout(horizontalLayout_27);


        horizontalLayout_33->addLayout(verticalLayout_18);


        horizontalLayout_13->addWidget(groupBoxMiscellaneous);


        verticalLayout_10->addLayout(horizontalLayout_13);

        horizontalLayout_28 = new QHBoxLayout();
        horizontalLayout_28->setObjectName(QStringLiteral("horizontalLayout_28"));
        groupBoxPageNumber = new QGroupBox(tab);
        groupBoxPageNumber->setObjectName(QStringLiteral("groupBoxPageNumber"));
        horizontalLayout_7 = new QHBoxLayout(groupBoxPageNumber);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_26 = new QHBoxLayout();
        horizontalLayout_26->setObjectName(QStringLiteral("horizontalLayout_26"));
        labelPageNumber = new QLabel(groupBoxPageNumber);
        labelPageNumber->setObjectName(QStringLiteral("labelPageNumber"));

        horizontalLayout_26->addWidget(labelPageNumber);

        comboBoxPageNumber = new QComboBox(groupBoxPageNumber);
        comboBoxPageNumber->setObjectName(QStringLiteral("comboBoxPageNumber"));

        horizontalLayout_26->addWidget(comboBoxPageNumber);


        verticalLayout_2->addLayout(horizontalLayout_26);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        labelPageNumberStyle = new QLabel(groupBoxPageNumber);
        labelPageNumberStyle->setObjectName(QStringLiteral("labelPageNumberStyle"));

        horizontalLayout_5->addWidget(labelPageNumberStyle);

        comboBoxPageNumberStyle = new QComboBox(groupBoxPageNumber);
        comboBoxPageNumberStyle->setObjectName(QStringLiteral("comboBoxPageNumberStyle"));

        horizontalLayout_5->addWidget(comboBoxPageNumberStyle);


        verticalLayout_2->addLayout(horizontalLayout_5);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setObjectName(QStringLiteral("horizontalLayout_14"));
        labelPageNumberFont = new QLabel(groupBoxPageNumber);
        labelPageNumberFont->setObjectName(QStringLiteral("labelPageNumberFont"));

        horizontalLayout_14->addWidget(labelPageNumberFont);

        labelPageNumberFontExample = new ExampleLabel(groupBoxPageNumber);
        labelPageNumberFontExample->setObjectName(QStringLiteral("labelPageNumberFontExample"));

        horizontalLayout_14->addWidget(labelPageNumberFontExample);

        toolButtonPageNumberFont = new FontButton(groupBoxPageNumber);
        toolButtonPageNumberFont->setObjectName(QStringLiteral("toolButtonPageNumberFont"));

        horizontalLayout_14->addWidget(toolButtonPageNumberFont);


        verticalLayout_2->addLayout(horizontalLayout_14);


        horizontalLayout_7->addLayout(verticalLayout_2);


        horizontalLayout_28->addWidget(groupBoxPageNumber);

        groupBoxMargin = new QGroupBox(tab);
        groupBoxMargin->setObjectName(QStringLiteral("groupBoxMargin"));
        horizontalLayout_25 = new QHBoxLayout(groupBoxMargin);
        horizontalLayout_25->setObjectName(QStringLiteral("horizontalLayout_25"));
        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setObjectName(QStringLiteral("verticalLayout_9"));
        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setObjectName(QStringLiteral("horizontalLayout_16"));
        labelMarginHorizontal = new QLabel(groupBoxMargin);
        labelMarginHorizontal->setObjectName(QStringLiteral("labelMarginHorizontal"));

        horizontalLayout_16->addWidget(labelMarginHorizontal);

        spuHorizontalMargin = new SpinBoxUnit(groupBoxMargin);
        spuHorizontalMargin->setObjectName(QStringLiteral("spuHorizontalMargin"));

        horizontalLayout_16->addWidget(spuHorizontalMargin);


        verticalLayout_9->addLayout(horizontalLayout_16);

        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setObjectName(QStringLiteral("horizontalLayout_17"));
        labelMarginVertical = new QLabel(groupBoxMargin);
        labelMarginVertical->setObjectName(QStringLiteral("labelMarginVertical"));

        horizontalLayout_17->addWidget(labelMarginVertical);

        spuVerticalMargin = new SpinBoxUnit(groupBoxMargin);
        spuVerticalMargin->setObjectName(QStringLiteral("spuVerticalMargin"));

        horizontalLayout_17->addWidget(spuVerticalMargin);


        verticalLayout_9->addLayout(horizontalLayout_17);


        horizontalLayout_25->addLayout(verticalLayout_9);


        horizontalLayout_28->addWidget(groupBoxMargin);


        verticalLayout_10->addLayout(horizontalLayout_28);


        horizontalLayout_29->addLayout(verticalLayout_10);

        tabWidget->addTab(tab, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        verticalLayout_13 = new QVBoxLayout(tab_3);
        verticalLayout_13->setObjectName(QStringLiteral("verticalLayout_13"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        groupBoxCover = new QGroupBox(tab_3);
        groupBoxCover->setObjectName(QStringLiteral("groupBoxCover"));
        verticalLayout_11 = new QVBoxLayout(groupBoxCover);
        verticalLayout_11->setObjectName(QStringLiteral("verticalLayout_11"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        checkBoxCover = new QCheckBox(groupBoxCover);
        checkBoxCover->setObjectName(QStringLiteral("checkBoxCover"));

        verticalLayout->addWidget(checkBoxCover);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        labelCoverFont = new QLabel(groupBoxCover);
        labelCoverFont->setObjectName(QStringLiteral("labelCoverFont"));

        horizontalLayout_10->addWidget(labelCoverFont);

        labelCoverFontExample = new ExampleLabel(groupBoxCover);
        labelCoverFontExample->setObjectName(QStringLiteral("labelCoverFontExample"));

        horizontalLayout_10->addWidget(labelCoverFontExample);

        toolButtonCoverFont = new FontButton(groupBoxCover);
        toolButtonCoverFont->setObjectName(QStringLiteral("toolButtonCoverFont"));

        horizontalLayout_10->addWidget(toolButtonCoverFont);


        verticalLayout->addLayout(horizontalLayout_10);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        labelTitlePosition = new QLabel(groupBoxCover);
        labelTitlePosition->setObjectName(QStringLiteral("labelTitlePosition"));

        horizontalLayout_11->addWidget(labelTitlePosition);

        comboBoxTitlePosition = new QComboBox(groupBoxCover);
        comboBoxTitlePosition->setObjectName(QStringLiteral("comboBoxTitlePosition"));

        horizontalLayout_11->addWidget(comboBoxTitlePosition);


        verticalLayout->addLayout(horizontalLayout_11);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        labelCoverImage = new QLabel(groupBoxCover);
        labelCoverImage->setObjectName(QStringLiteral("labelCoverImage"));

        horizontalLayout->addWidget(labelCoverImage);

        labelCoverViewImage = new QLabel(groupBoxCover);
        labelCoverViewImage->setObjectName(QStringLiteral("labelCoverViewImage"));

        horizontalLayout->addWidget(labelCoverViewImage);

        toolButtonSuppressCoverImage = new QToolButton(groupBoxCover);
        toolButtonSuppressCoverImage->setObjectName(QStringLiteral("toolButtonSuppressCoverImage"));

        horizontalLayout->addWidget(toolButtonSuppressCoverImage);

        toolButtonCoverImage = new ImageButton(groupBoxCover);
        toolButtonCoverImage->setObjectName(QStringLiteral("toolButtonCoverImage"));

        horizontalLayout->addWidget(toolButtonCoverImage);


        verticalLayout->addLayout(horizontalLayout);


        verticalLayout_11->addLayout(verticalLayout);


        gridLayout_2->addWidget(groupBoxCover, 0, 0, 1, 1);

        groupBoxChord = new QGroupBox(tab_3);
        groupBoxChord->setObjectName(QStringLiteral("groupBoxChord"));
        verticalLayout_14 = new QVBoxLayout(groupBoxChord);
        verticalLayout_14->setObjectName(QStringLiteral("verticalLayout_14"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setObjectName(QStringLiteral("horizontalLayout_15"));
        labelChordDiagramHSize = new QLabel(groupBoxChord);
        labelChordDiagramHSize->setObjectName(QStringLiteral("labelChordDiagramHSize"));

        horizontalLayout_15->addWidget(labelChordDiagramHSize);

        spuChordHorizontalSize = new SpinBoxUnit(groupBoxChord);
        spuChordHorizontalSize->setObjectName(QStringLiteral("spuChordHorizontalSize"));

        horizontalLayout_15->addWidget(spuChordHorizontalSize);


        verticalLayout_3->addLayout(horizontalLayout_15);

        verticalLayout_12 = new QVBoxLayout();
        verticalLayout_12->setObjectName(QStringLiteral("verticalLayout_12"));
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        labelChordFont = new QLabel(groupBoxChord);
        labelChordFont->setObjectName(QStringLiteral("labelChordFont"));

        horizontalLayout_8->addWidget(labelChordFont);

        labelChordFontExample = new ExampleLabel(groupBoxChord);
        labelChordFontExample->setObjectName(QStringLiteral("labelChordFontExample"));

        horizontalLayout_8->addWidget(labelChordFontExample);

        toolButtonChordFont = new FontButton(groupBoxChord);
        toolButtonChordFont->setObjectName(QStringLiteral("toolButtonChordFont"));

        horizontalLayout_8->addWidget(toolButtonChordFont);


        verticalLayout_12->addLayout(horizontalLayout_8);


        verticalLayout_3->addLayout(verticalLayout_12);

        horizontalLayout_22 = new QHBoxLayout();
        horizontalLayout_22->setObjectName(QStringLiteral("horizontalLayout_22"));
        labelChordLang = new QLabel(groupBoxChord);
        labelChordLang->setObjectName(QStringLiteral("labelChordLang"));

        horizontalLayout_22->addWidget(labelChordLang);

        comboBoxChordLang = new QComboBox(groupBoxChord);
        QIcon icon;
        icon.addFile(QStringLiteral(":/Image/Images/en.png"), QSize(), QIcon::Normal, QIcon::Off);
        comboBoxChordLang->addItem(icon, QString());
        comboBoxChordLang->setObjectName(QStringLiteral("comboBoxChordLang"));

        horizontalLayout_22->addWidget(comboBoxChordLang);


        verticalLayout_3->addLayout(horizontalLayout_22);

        horizontalLayout_23 = new QHBoxLayout();
        horizontalLayout_23->setObjectName(QStringLiteral("horizontalLayout_23"));
        labelChordLangInText = new QLabel(groupBoxChord);
        labelChordLangInText->setObjectName(QStringLiteral("labelChordLangInText"));

        horizontalLayout_23->addWidget(labelChordLangInText);

        comboBoxChordInText = new QComboBox(groupBoxChord);
        comboBoxChordInText->setObjectName(QStringLiteral("comboBoxChordInText"));

        horizontalLayout_23->addWidget(comboBoxChordInText);


        verticalLayout_3->addLayout(horizontalLayout_23);


        verticalLayout_14->addLayout(verticalLayout_3);


        gridLayout_2->addWidget(groupBoxChord, 0, 1, 2, 1);

        groupBoxToc = new QGroupBox(tab_3);
        groupBoxToc->setObjectName(QStringLiteral("groupBoxToc"));
        verticalLayout_7 = new QVBoxLayout(groupBoxToc);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        horizontalLayout_24 = new QHBoxLayout();
        horizontalLayout_24->setObjectName(QStringLiteral("horizontalLayout_24"));
        labelTocVerticalSpacing = new QLabel(groupBoxToc);
        labelTocVerticalSpacing->setObjectName(QStringLiteral("labelTocVerticalSpacing"));

        horizontalLayout_24->addWidget(labelTocVerticalSpacing);

        comboBoxTocVerticalSpacing = new VerticalSpacing(groupBoxToc);
        comboBoxTocVerticalSpacing->setObjectName(QStringLiteral("comboBoxTocVerticalSpacing"));

        horizontalLayout_24->addWidget(comboBoxTocVerticalSpacing);


        verticalLayout_5->addLayout(horizontalLayout_24);

        horizontalLayout_31 = new QHBoxLayout();
        horizontalLayout_31->setObjectName(QStringLiteral("horizontalLayout_31"));
        labelTocColumn = new QLabel(groupBoxToc);
        labelTocColumn->setObjectName(QStringLiteral("labelTocColumn"));

        horizontalLayout_31->addWidget(labelTocColumn);

        comboBoxTocColumnNumber = new QComboBox(groupBoxToc);
        comboBoxTocColumnNumber->setObjectName(QStringLiteral("comboBoxTocColumnNumber"));

        horizontalLayout_31->addWidget(comboBoxTocColumnNumber);


        verticalLayout_5->addLayout(horizontalLayout_31);

        horizontalLayout_36 = new QHBoxLayout();
        horizontalLayout_36->setObjectName(QStringLiteral("horizontalLayout_36"));
        labelTocFont = new QLabel(groupBoxToc);
        labelTocFont->setObjectName(QStringLiteral("labelTocFont"));

        horizontalLayout_36->addWidget(labelTocFont);

        labelTocFontExample = new ExampleLabel(groupBoxToc);
        labelTocFontExample->setObjectName(QStringLiteral("labelTocFontExample"));

        horizontalLayout_36->addWidget(labelTocFontExample);

        toolButtonTocFont = new FontButton(groupBoxToc);
        toolButtonTocFont->setObjectName(QStringLiteral("toolButtonTocFont"));

        horizontalLayout_36->addWidget(toolButtonTocFont);


        verticalLayout_5->addLayout(horizontalLayout_36);

        horizontalLayout_32 = new QHBoxLayout();
        horizontalLayout_32->setObjectName(QStringLiteral("horizontalLayout_32"));
        labelTocSpaceCharacter = new QLabel(groupBoxToc);
        labelTocSpaceCharacter->setObjectName(QStringLiteral("labelTocSpaceCharacter"));

        horizontalLayout_32->addWidget(labelTocSpaceCharacter);

        comboBoxTocSpaceCharacter = new QComboBox(groupBoxToc);
        comboBoxTocSpaceCharacter->setObjectName(QStringLiteral("comboBoxTocSpaceCharacter"));

        horizontalLayout_32->addWidget(comboBoxTocSpaceCharacter);


        verticalLayout_5->addLayout(horizontalLayout_32);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        label = new QLabel(groupBoxToc);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_12->addWidget(label);

        comboBoxTocPosition = new QComboBox(groupBoxToc);
        comboBoxTocPosition->setObjectName(QStringLiteral("comboBoxTocPosition"));

        horizontalLayout_12->addWidget(comboBoxTocPosition);


        verticalLayout_5->addLayout(horizontalLayout_12);


        verticalLayout_7->addLayout(verticalLayout_5);


        gridLayout_2->addWidget(groupBoxToc, 1, 0, 2, 1);

        groupBoxMiscellaneousContent = new QGroupBox(tab_3);
        groupBoxMiscellaneousContent->setObjectName(QStringLiteral("groupBoxMiscellaneousContent"));
        horizontalLayout_2 = new QHBoxLayout(groupBoxMiscellaneousContent);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        labelOutputFileName = new QLabel(groupBoxMiscellaneousContent);
        labelOutputFileName->setObjectName(QStringLiteral("labelOutputFileName"));

        horizontalLayout_9->addWidget(labelOutputFileName);

        lineEditOutFile = new QLineEdit(groupBoxMiscellaneousContent);
        lineEditOutFile->setObjectName(QStringLiteral("lineEditOutFile"));

        horizontalLayout_9->addWidget(lineEditOutFile);


        verticalLayout_8->addLayout(horizontalLayout_9);

        horizontalLayout_30 = new QHBoxLayout();
        horizontalLayout_30->setObjectName(QStringLiteral("horizontalLayout_30"));
        labelVerticalSpacing = new QLabel(groupBoxMiscellaneousContent);
        labelVerticalSpacing->setObjectName(QStringLiteral("labelVerticalSpacing"));

        horizontalLayout_30->addWidget(labelVerticalSpacing);

        comboBoxVerticalSpacing = new VerticalSpacing(groupBoxMiscellaneousContent);
        comboBoxVerticalSpacing->setObjectName(QStringLiteral("comboBoxVerticalSpacing"));

        horizontalLayout_30->addWidget(comboBoxVerticalSpacing);


        verticalLayout_8->addLayout(horizontalLayout_30);

        checkBoxFullScreenMode = new QCheckBox(groupBoxMiscellaneousContent);
        checkBoxFullScreenMode->setObjectName(QStringLiteral("checkBoxFullScreenMode"));

        verticalLayout_8->addWidget(checkBoxFullScreenMode);

        checkBoxTitleInUppercase = new QCheckBox(groupBoxMiscellaneousContent);
        checkBoxTitleInUppercase->setObjectName(QStringLiteral("checkBoxTitleInUppercase"));

        verticalLayout_8->addWidget(checkBoxTitleInUppercase);


        horizontalLayout_2->addLayout(verticalLayout_8);


        gridLayout_2->addWidget(groupBoxMiscellaneousContent, 2, 1, 1, 1);


        verticalLayout_13->addLayout(gridLayout_2);

        tabWidget->addTab(tab_3, QString());

        verticalLayout_6->addWidget(tabWidget);


        retranslateUi(FormConfig);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(FormConfig);
    } // setupUi

    void retranslateUi(QWidget *FormConfig)
    {
        FormConfig->setWindowTitle(QApplication::translate("FormConfig", "Form", Q_NULLPTR));
        groupBoxPageSize->setTitle(QApplication::translate("FormConfig", "PageSize", Q_NULLPTR));
        labelPageWidth->setText(QApplication::translate("FormConfig", "Page width", Q_NULLPTR));
        labelPageHeight->setText(QApplication::translate("FormConfig", "Page height", Q_NULLPTR));
        labelPageDimension->setText(QApplication::translate("FormConfig", "Page", Q_NULLPTR));
        checkBoxLandscape->setText(QApplication::translate("FormConfig", "Landscape", Q_NULLPTR));
        groupBoxMiscellaneous->setTitle(QApplication::translate("FormConfig", "Miscellaneous", Q_NULLPTR));
        labelNormalFont->setText(QApplication::translate("FormConfig", "Default Font", Q_NULLPTR));
        labelNormalFontExample->setText(QApplication::translate("FormConfig", "Example", Q_NULLPTR));
        toolButtonNormalFont->setText(QApplication::translate("FormConfig", "...", Q_NULLPTR));
        labelTitleFont->setText(QApplication::translate("FormConfig", "Title Font", Q_NULLPTR));
        labelTitleFontExample->setText(QApplication::translate("FormConfig", "Example", Q_NULLPTR));
        toolButtonTitleFont->setText(QApplication::translate("FormConfig", "...", Q_NULLPTR));
        labelSubtitleFont->setText(QApplication::translate("FormConfig", "Subtitle Font", Q_NULLPTR));
        labelSubtitleFontExample->setText(QApplication::translate("FormConfig", "Example", Q_NULLPTR));
        toolButtonSubtitleFont->setText(QApplication::translate("FormConfig", "...", Q_NULLPTR));
        labelDuplex->setText(QApplication::translate("FormConfig", "Duplex", Q_NULLPTR));
        comboBoxDuplex->clear();
        comboBoxDuplex->insertItems(0, QStringList()
         << QApplication::translate("FormConfig", "Simplex", Q_NULLPTR)
         << QApplication::translate("FormConfig", "Duplex", Q_NULLPTR)
        );
        groupBoxPageNumber->setTitle(QApplication::translate("FormConfig", "Page number", Q_NULLPTR));
        labelPageNumber->setText(QApplication::translate("FormConfig", "Page number", Q_NULLPTR));
        comboBoxPageNumber->clear();
        comboBoxPageNumber->insertItems(0, QStringList()
         << QApplication::translate("FormConfig", "No", Q_NULLPTR)
         << QApplication::translate("FormConfig", "Center", Q_NULLPTR)
         << QApplication::translate("FormConfig", "Outside", Q_NULLPTR)
        );
        labelPageNumberStyle->setText(QApplication::translate("FormConfig", "Page style", Q_NULLPTR));
        comboBoxPageNumberStyle->clear();
        comboBoxPageNumberStyle->insertItems(0, QStringList()
         << QApplication::translate("FormConfig", "1", Q_NULLPTR)
         << QApplication::translate("FormConfig", "- 1 - ", Q_NULLPTR)
         << QApplication::translate("FormConfig", "1/50", Q_NULLPTR)
        );
        labelPageNumberFont->setText(QApplication::translate("FormConfig", "Page Number  Font", Q_NULLPTR));
        labelPageNumberFontExample->setText(QApplication::translate("FormConfig", "Example", Q_NULLPTR));
        toolButtonPageNumberFont->setText(QApplication::translate("FormConfig", "...", Q_NULLPTR));
        groupBoxMargin->setTitle(QApplication::translate("FormConfig", "Margin", Q_NULLPTR));
        labelMarginHorizontal->setText(QApplication::translate("FormConfig", "Horizontal ", Q_NULLPTR));
        labelMarginVertical->setText(QApplication::translate("FormConfig", "Vertical", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("FormConfig", "Document", Q_NULLPTR));
        groupBoxCover->setTitle(QApplication::translate("FormConfig", "Cover", Q_NULLPTR));
        checkBoxCover->setText(QApplication::translate("FormConfig", "Cover", Q_NULLPTR));
        labelCoverFont->setText(QApplication::translate("FormConfig", "Cover Font", Q_NULLPTR));
        labelCoverFontExample->setText(QApplication::translate("FormConfig", "Example", Q_NULLPTR));
        toolButtonCoverFont->setText(QApplication::translate("FormConfig", "...", Q_NULLPTR));
        labelTitlePosition->setText(QApplication::translate("FormConfig", "Title position from top", Q_NULLPTR));
        comboBoxTitlePosition->clear();
        comboBoxTitlePosition->insertItems(0, QStringList()
         << QApplication::translate("FormConfig", "1/3", Q_NULLPTR)
         << QApplication::translate("FormConfig", "1/2", Q_NULLPTR)
         << QApplication::translate("FormConfig", "2/3", Q_NULLPTR)
        );
        labelCoverImage->setText(QApplication::translate("FormConfig", " Image", Q_NULLPTR));
        labelCoverViewImage->setText(QString());
        toolButtonSuppressCoverImage->setText(QApplication::translate("FormConfig", " - ", Q_NULLPTR));
        toolButtonCoverImage->setText(QApplication::translate("FormConfig", "...", Q_NULLPTR));
        groupBoxChord->setTitle(QApplication::translate("FormConfig", "Chord", Q_NULLPTR));
        labelChordDiagramHSize->setText(QApplication::translate("FormConfig", "Chord diagram horizontal size", Q_NULLPTR));
        labelChordFont->setText(QApplication::translate("FormConfig", "Chord Font", Q_NULLPTR));
        labelChordFontExample->setText(QApplication::translate("FormConfig", "Example", Q_NULLPTR));
        toolButtonChordFont->setText(QApplication::translate("FormConfig", "...", Q_NULLPTR));
        labelChordLang->setText(QApplication::translate("FormConfig", "Chord Lang", Q_NULLPTR));
        comboBoxChordLang->setItemText(0, QApplication::translate("FormConfig", "English", Q_NULLPTR));

        labelChordLangInText->setText(QApplication::translate("FormConfig", "Chord in text", Q_NULLPTR));
        comboBoxChordInText->clear();
        comboBoxChordInText->insertItems(0, QStringList()
         << QApplication::translate("FormConfig", "with name", Q_NULLPTR)
         << QApplication::translate("FormConfig", "with diagram", Q_NULLPTR)
        );
        groupBoxToc->setTitle(QApplication::translate("FormConfig", "Toc", Q_NULLPTR));
        labelTocVerticalSpacing->setText(QApplication::translate("FormConfig", "Toc vertical spacing", Q_NULLPTR));
        labelTocColumn->setText(QApplication::translate("FormConfig", "Toc column number", Q_NULLPTR));
        comboBoxTocColumnNumber->clear();
        comboBoxTocColumnNumber->insertItems(0, QStringList()
         << QApplication::translate("FormConfig", "1", Q_NULLPTR)
         << QApplication::translate("FormConfig", "2", Q_NULLPTR)
         << QApplication::translate("FormConfig", "3", Q_NULLPTR)
        );
        labelTocFont->setText(QApplication::translate("FormConfig", "Toc Font", Q_NULLPTR));
        labelTocFontExample->setText(QApplication::translate("FormConfig", "Example", Q_NULLPTR));
        toolButtonTocFont->setText(QApplication::translate("FormConfig", "...", Q_NULLPTR));
        labelTocSpaceCharacter->setText(QApplication::translate("FormConfig", "Space character", Q_NULLPTR));
        comboBoxTocSpaceCharacter->clear();
        comboBoxTocSpaceCharacter->insertItems(0, QStringList()
         << QApplication::translate("FormConfig", ". . . .", Q_NULLPTR)
         << QApplication::translate("FormConfig", "- - - -", Q_NULLPTR)
         << QString()
        );
        label->setText(QApplication::translate("FormConfig", "Position ", Q_NULLPTR));
        comboBoxTocPosition->clear();
        comboBoxTocPosition->insertItems(0, QStringList()
         << QApplication::translate("FormConfig", "No", Q_NULLPTR)
         << QApplication::translate("FormConfig", "At begining", Q_NULLPTR)
         << QApplication::translate("FormConfig", "At end", Q_NULLPTR)
        );
        groupBoxMiscellaneousContent->setTitle(QApplication::translate("FormConfig", "Miscellaneous", Q_NULLPTR));
        labelOutputFileName->setText(QApplication::translate("FormConfig", "Output file name", Q_NULLPTR));
        labelVerticalSpacing->setText(QApplication::translate("FormConfig", "Text vertical spacing", Q_NULLPTR));
        checkBoxFullScreenMode->setText(QApplication::translate("FormConfig", "Open in full screen mode", Q_NULLPTR));
        checkBoxTitleInUppercase->setText(QApplication::translate("FormConfig", "Title in uppercase", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("FormConfig", "Content", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class FormConfig: public Ui_FormConfig {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMCONFIG_H
