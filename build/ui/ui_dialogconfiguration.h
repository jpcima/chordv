/********************************************************************************
** Form generated from reading UI file 'dialogconfiguration.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGCONFIGURATION_H
#define UI_DIALOGCONFIGURATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "chordconfig.h"
#include "lyricsconfig.h"
#include "memoryconfig.h"
#include "textconfig.h"

QT_BEGIN_NAMESPACE

class Ui_DialogConfiguration
{
public:
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout_10;
    QHBoxLayout *horizontalLayout_5;
    QVBoxLayout *verticalLayout_8;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_4;
    QLabel *labelInterfaceLanguage;
    QComboBox *comboBoxInterfaceLanguage;
    QHBoxLayout *horizontalLayout_7;
    QLabel *labelUnit;
    QComboBox *comboBoxUnit;
    QHBoxLayout *horizontalLayout_8;
    QLabel *labelPDFReaderName;
    QLineEdit *lineEditPDFReaderName;
    QToolButton *toolButtonPDFReaderName;
    QHBoxLayout *horizontalLayout_3;
    QLabel *labelCreatorName;
    QLineEdit *lineEditCreatoName;
    QLineEdit *lineEditCreatoName_2;
    QSpacerItem *verticalSpacer;
    QSpacerItem *horizontalSpacer_2;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_3;
    LyricsConfig *lyricsConfig;
    QWidget *tab_3;
    QVBoxLayout *verticalLayout_4;
    ChordConfig *chordConfig;
    QWidget *tab_4;
    QVBoxLayout *verticalLayout_5;
    TextConfig *textConfig;
    QWidget *tab_5;
    QVBoxLayout *verticalLayout_6;
    MemoryConfig *memoryConfig;
    QWidget *tab_6;
    QVBoxLayout *verticalLayout_7;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButtonClose;
    QPushButton *pushButtonSave;

    void setupUi(QDialog *DialogConfiguration)
    {
        if (DialogConfiguration->objectName().isEmpty())
            DialogConfiguration->setObjectName(QStringLiteral("DialogConfiguration"));
        DialogConfiguration->resize(784, 520);
        horizontalLayout_2 = new QHBoxLayout(DialogConfiguration);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        tabWidget = new QTabWidget(DialogConfiguration);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        verticalLayout_10 = new QVBoxLayout(tab);
        verticalLayout_10->setObjectName(QStringLiteral("verticalLayout_10"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        labelInterfaceLanguage = new QLabel(tab);
        labelInterfaceLanguage->setObjectName(QStringLiteral("labelInterfaceLanguage"));

        horizontalLayout_4->addWidget(labelInterfaceLanguage);

        comboBoxInterfaceLanguage = new QComboBox(tab);
        QIcon icon;
        icon.addFile(QStringLiteral("Images/en.png"), QSize(), QIcon::Normal, QIcon::Off);
        comboBoxInterfaceLanguage->addItem(icon, QStringLiteral("English"));
        comboBoxInterfaceLanguage->setObjectName(QStringLiteral("comboBoxInterfaceLanguage"));

        horizontalLayout_4->addWidget(comboBoxInterfaceLanguage);


        verticalLayout_2->addLayout(horizontalLayout_4);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        labelUnit = new QLabel(tab);
        labelUnit->setObjectName(QStringLiteral("labelUnit"));

        horizontalLayout_7->addWidget(labelUnit);

        comboBoxUnit = new QComboBox(tab);
        comboBoxUnit->setObjectName(QStringLiteral("comboBoxUnit"));

        horizontalLayout_7->addWidget(comboBoxUnit);


        verticalLayout_2->addLayout(horizontalLayout_7);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        labelPDFReaderName = new QLabel(tab);
        labelPDFReaderName->setObjectName(QStringLiteral("labelPDFReaderName"));

        horizontalLayout_8->addWidget(labelPDFReaderName);

        lineEditPDFReaderName = new QLineEdit(tab);
        lineEditPDFReaderName->setObjectName(QStringLiteral("lineEditPDFReaderName"));

        horizontalLayout_8->addWidget(lineEditPDFReaderName);

        toolButtonPDFReaderName = new QToolButton(tab);
        toolButtonPDFReaderName->setObjectName(QStringLiteral("toolButtonPDFReaderName"));

        horizontalLayout_8->addWidget(toolButtonPDFReaderName);


        verticalLayout_2->addLayout(horizontalLayout_8);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        labelCreatorName = new QLabel(tab);
        labelCreatorName->setObjectName(QStringLiteral("labelCreatorName"));

        horizontalLayout_3->addWidget(labelCreatorName);

        lineEditCreatoName = new QLineEdit(tab);
        lineEditCreatoName->setObjectName(QStringLiteral("lineEditCreatoName"));

        horizontalLayout_3->addWidget(lineEditCreatoName);


        verticalLayout_2->addLayout(horizontalLayout_3);


        verticalLayout_8->addLayout(verticalLayout_2);

        lineEditCreatoName_2 = new QLineEdit(tab);
        lineEditCreatoName_2->setObjectName(QStringLiteral("lineEditCreatoName_2"));

        verticalLayout_8->addWidget(lineEditCreatoName_2);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_8->addItem(verticalSpacer);


        horizontalLayout_5->addLayout(verticalLayout_8);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_2);


        verticalLayout_10->addLayout(horizontalLayout_5);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        verticalLayout_3 = new QVBoxLayout(tab_2);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        lyricsConfig = new LyricsConfig(tab_2);
        lyricsConfig->setObjectName(QStringLiteral("lyricsConfig"));

        verticalLayout_3->addWidget(lyricsConfig);

        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        verticalLayout_4 = new QVBoxLayout(tab_3);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        chordConfig = new ChordConfig(tab_3);
        chordConfig->setObjectName(QStringLiteral("chordConfig"));

        verticalLayout_4->addWidget(chordConfig);

        tabWidget->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QStringLiteral("tab_4"));
        verticalLayout_5 = new QVBoxLayout(tab_4);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        textConfig = new TextConfig(tab_4);
        textConfig->setObjectName(QStringLiteral("textConfig"));

        verticalLayout_5->addWidget(textConfig);

        tabWidget->addTab(tab_4, QString());
        tab_5 = new QWidget();
        tab_5->setObjectName(QStringLiteral("tab_5"));
        verticalLayout_6 = new QVBoxLayout(tab_5);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        memoryConfig = new MemoryConfig(tab_5);
        memoryConfig->setObjectName(QStringLiteral("memoryConfig"));

        verticalLayout_6->addWidget(memoryConfig);

        tabWidget->addTab(tab_5, QString());
        tab_6 = new QWidget();
        tab_6->setObjectName(QStringLiteral("tab_6"));
        verticalLayout_7 = new QVBoxLayout(tab_6);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        widget = new QWidget(tab_6);
        widget->setObjectName(QStringLiteral("widget"));

        verticalLayout_7->addWidget(widget);

        tabWidget->addTab(tab_6, QString());

        verticalLayout->addWidget(tabWidget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButtonClose = new QPushButton(DialogConfiguration);
        pushButtonClose->setObjectName(QStringLiteral("pushButtonClose"));

        horizontalLayout->addWidget(pushButtonClose);

        pushButtonSave = new QPushButton(DialogConfiguration);
        pushButtonSave->setObjectName(QStringLiteral("pushButtonSave"));

        horizontalLayout->addWidget(pushButtonSave);


        verticalLayout->addLayout(horizontalLayout);


        horizontalLayout_2->addLayout(verticalLayout);


        retranslateUi(DialogConfiguration);

        tabWidget->setCurrentIndex(0);
        pushButtonSave->setDefault(true);


        QMetaObject::connectSlotsByName(DialogConfiguration);
    } // setupUi

    void retranslateUi(QDialog *DialogConfiguration)
    {
        DialogConfiguration->setWindowTitle(QApplication::translate("DialogConfiguration", "Configuration", Q_NULLPTR));
        labelInterfaceLanguage->setText(QApplication::translate("DialogConfiguration", " Interface language", Q_NULLPTR));

        labelUnit->setText(QApplication::translate("DialogConfiguration", "Preferred units", Q_NULLPTR));
        comboBoxUnit->clear();
        comboBoxUnit->insertItems(0, QStringList()
         << QApplication::translate("DialogConfiguration", "mm", Q_NULLPTR)
         << QApplication::translate("DialogConfiguration", "cm", Q_NULLPTR)
         << QApplication::translate("DialogConfiguration", "in", Q_NULLPTR)
        );
        labelPDFReaderName->setText(QApplication::translate("DialogConfiguration", "PDF Reader program", Q_NULLPTR));
        toolButtonPDFReaderName->setText(QApplication::translate("DialogConfiguration", "...", Q_NULLPTR));
        labelCreatorName->setText(QApplication::translate("DialogConfiguration", "Creator name", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("DialogConfiguration", "General", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("DialogConfiguration", "Lyrics mode", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("DialogConfiguration", "Chord mode", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QApplication::translate("DialogConfiguration", "Text mode", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_5), QApplication::translate("DialogConfiguration", "Memory mode", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_6), QApplication::translate("DialogConfiguration", "Editor", Q_NULLPTR));
        pushButtonClose->setText(QApplication::translate("DialogConfiguration", "Close", Q_NULLPTR));
        pushButtonSave->setText(QApplication::translate("DialogConfiguration", "Save", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class DialogConfiguration: public Ui_DialogConfiguration {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGCONFIGURATION_H
