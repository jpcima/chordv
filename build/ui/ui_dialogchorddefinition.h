/********************************************************************************
** Form generated from reading UI file 'dialogchorddefinition.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGCHORDDEFINITION_H
#define UI_DIALOGCHORDDEFINITION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "chorddiagram.h"
#include "neck.h"

QT_BEGIN_NAMESPACE

class Ui_DialogChordDefinition
{
public:
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout_2;
    QTabWidget *tabWidget;
    QWidget *tabNewChord;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout;
    Neck *neck;
    QHBoxLayout *horizontalLayout_2;
    QLabel *labelChordName;
    QLineEdit *lineEditChord;
    QListWidget *listWidgetChords;
    QLineEdit *lineEditNotation;
    QLineEdit *lineEditName;
    QToolButton *toolButtonPlus;
    QLabel *labelChordsCount;
    QWidget *tab_2;
    QHBoxLayout *horizontalLayout_10;
    QHBoxLayout *horizontalLayout_9;
    QTableView *tableView;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_7;
    QLineEdit *lineEditNameIndex;
    QLineEdit *lineEditValueIndex;
    QHBoxLayout *horizontalLayout_8;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *pushButtonDelete;
    QPushButton *pushButtonModify;
    QSpacerItem *horizontalSpacer_4;
    ChordDiagram *widget;
    QWidget *tab;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_6;
    QPlainTextEdit *plainTextEditImport;
    QVBoxLayout *verticalLayout_3;
    QLabel *label81;
    QLabel *label_3;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButtonImport;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButtonCancel;

    void setupUi(QDialog *DialogChordDefinition)
    {
        if (DialogChordDefinition->objectName().isEmpty())
            DialogChordDefinition->setObjectName(QStringLiteral("DialogChordDefinition"));
        DialogChordDefinition->resize(712, 304);
        horizontalLayout_4 = new QHBoxLayout(DialogChordDefinition);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        tabWidget = new QTabWidget(DialogChordDefinition);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabNewChord = new QWidget();
        tabNewChord->setObjectName(QStringLiteral("tabNewChord"));
        horizontalLayout_3 = new QHBoxLayout(tabNewChord);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        neck = new Neck(tabNewChord);
        neck->setObjectName(QStringLiteral("neck"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(neck->sizePolicy().hasHeightForWidth());
        neck->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(neck);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        labelChordName = new QLabel(tabNewChord);
        labelChordName->setObjectName(QStringLiteral("labelChordName"));

        horizontalLayout_2->addWidget(labelChordName);

        lineEditChord = new QLineEdit(tabNewChord);
        lineEditChord->setObjectName(QStringLiteral("lineEditChord"));
        lineEditChord->setReadOnly(true);

        horizontalLayout_2->addWidget(lineEditChord);

        listWidgetChords = new QListWidget(tabNewChord);
        listWidgetChords->setObjectName(QStringLiteral("listWidgetChords"));
        listWidgetChords->setMaximumSize(QSize(150, 60));

        horizontalLayout_2->addWidget(listWidgetChords);

        lineEditNotation = new QLineEdit(tabNewChord);
        lineEditNotation->setObjectName(QStringLiteral("lineEditNotation"));
        lineEditNotation->setReadOnly(true);

        horizontalLayout_2->addWidget(lineEditNotation);

        lineEditName = new QLineEdit(tabNewChord);
        lineEditName->setObjectName(QStringLiteral("lineEditName"));

        horizontalLayout_2->addWidget(lineEditName);

        toolButtonPlus = new QToolButton(tabNewChord);
        toolButtonPlus->setObjectName(QStringLiteral("toolButtonPlus"));
        QFont font;
        font.setPointSize(20);
        toolButtonPlus->setFont(font);

        horizontalLayout_2->addWidget(toolButtonPlus);

        labelChordsCount = new QLabel(tabNewChord);
        labelChordsCount->setObjectName(QStringLiteral("labelChordsCount"));

        horizontalLayout_2->addWidget(labelChordsCount);


        verticalLayout->addLayout(horizontalLayout_2);


        horizontalLayout_3->addLayout(verticalLayout);

        tabWidget->addTab(tabNewChord, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        horizontalLayout_10 = new QHBoxLayout(tab_2);
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        tableView = new QTableView(tab_2);
        tableView->setObjectName(QStringLiteral("tableView"));

        horizontalLayout_9->addWidget(tableView);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        lineEditNameIndex = new QLineEdit(tab_2);
        lineEditNameIndex->setObjectName(QStringLiteral("lineEditNameIndex"));

        horizontalLayout_7->addWidget(lineEditNameIndex);

        lineEditValueIndex = new QLineEdit(tab_2);
        lineEditValueIndex->setObjectName(QStringLiteral("lineEditValueIndex"));

        horizontalLayout_7->addWidget(lineEditValueIndex);


        verticalLayout_5->addLayout(horizontalLayout_7);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_3);

        pushButtonDelete = new QPushButton(tab_2);
        pushButtonDelete->setObjectName(QStringLiteral("pushButtonDelete"));

        horizontalLayout_8->addWidget(pushButtonDelete);

        pushButtonModify = new QPushButton(tab_2);
        pushButtonModify->setObjectName(QStringLiteral("pushButtonModify"));

        horizontalLayout_8->addWidget(pushButtonModify);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_4);


        verticalLayout_5->addLayout(horizontalLayout_8);

        widget = new ChordDiagram(tab_2);
        widget->setObjectName(QStringLiteral("widget"));

        verticalLayout_5->addWidget(widget);


        horizontalLayout_9->addLayout(verticalLayout_5);


        horizontalLayout_10->addLayout(horizontalLayout_9);

        tabWidget->addTab(tab_2, QString());
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        verticalLayout_4 = new QVBoxLayout(tab);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        plainTextEditImport = new QPlainTextEdit(tab);
        plainTextEditImport->setObjectName(QStringLiteral("plainTextEditImport"));

        horizontalLayout_6->addWidget(plainTextEditImport);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        label81 = new QLabel(tab);
        label81->setObjectName(QStringLiteral("label81"));

        verticalLayout_3->addWidget(label81);

        label_3 = new QLabel(tab);
        label_3->setObjectName(QStringLiteral("label_3"));

        verticalLayout_3->addWidget(label_3);

        label_2 = new QLabel(tab);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout_3->addWidget(label_2);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_2);

        pushButtonImport = new QPushButton(tab);
        pushButtonImport->setObjectName(QStringLiteral("pushButtonImport"));

        horizontalLayout_5->addWidget(pushButtonImport);


        verticalLayout_3->addLayout(horizontalLayout_5);


        horizontalLayout_6->addLayout(verticalLayout_3);


        verticalLayout_4->addLayout(horizontalLayout_6);

        tabWidget->addTab(tab, QString());

        verticalLayout_2->addWidget(tabWidget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButtonCancel = new QPushButton(DialogChordDefinition);
        pushButtonCancel->setObjectName(QStringLiteral("pushButtonCancel"));

        horizontalLayout->addWidget(pushButtonCancel);


        verticalLayout_2->addLayout(horizontalLayout);


        horizontalLayout_4->addLayout(verticalLayout_2);


        retranslateUi(DialogChordDefinition);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(DialogChordDefinition);
    } // setupUi

    void retranslateUi(QDialog *DialogChordDefinition)
    {
        DialogChordDefinition->setWindowTitle(QApplication::translate("DialogChordDefinition", "Chord Definition", Q_NULLPTR));
        labelChordName->setText(QApplication::translate("DialogChordDefinition", "Chord name", Q_NULLPTR));
        toolButtonPlus->setText(QApplication::translate("DialogChordDefinition", "+", Q_NULLPTR));
        labelChordsCount->setText(QApplication::translate("DialogChordDefinition", "0", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tabNewChord), QApplication::translate("DialogChordDefinition", "Chord Definition", Q_NULLPTR));
        pushButtonDelete->setText(QApplication::translate("DialogChordDefinition", "Delete", Q_NULLPTR));
        pushButtonModify->setText(QApplication::translate("DialogChordDefinition", "Modifiy", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("DialogChordDefinition", "Chord Management", Q_NULLPTR));
        label81->setText(QApplication::translate("DialogChordDefinition", "Copy paste chords in form ", Q_NULLPTR));
        label_3->setText(QApplication::translate("DialogChordDefinition", "chord=relative position 6 ..position 1 ", Q_NULLPTR));
        label_2->setText(QApplication::translate("DialogChordDefinition", "C(III)=3 0 0 3 3 3 0  ", Q_NULLPTR));
        pushButtonImport->setText(QApplication::translate("DialogChordDefinition", "Import", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("DialogChordDefinition", "Chord Inport", Q_NULLPTR));
        pushButtonCancel->setText(QApplication::translate("DialogChordDefinition", "Close", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class DialogChordDefinition: public Ui_DialogChordDefinition {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGCHORDDEFINITION_H
