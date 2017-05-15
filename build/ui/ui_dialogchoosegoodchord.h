/********************************************************************************
** Form generated from reading UI file 'dialogchoosegoodchord.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGCHOOSEGOODCHORD_H
#define UI_DIALOGCHOOSEGOODCHORD_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include "chorddiagram.h"

QT_BEGIN_NAMESPACE

class Ui_DialogChooseGoodChord
{
public:
    QHBoxLayout *horizontalLayout_7;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_6;
    QTextEdit *textEdit;
    QHBoxLayout *horizontalLayout_5;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer;
    QLabel *labelNewChord;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout;
    QLabel *labelNameNew;
    QLineEdit *lineEditNewName;
    ChordDiagram *widgetNew;
    QPushButton *pushButtonReplaceOld;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_3;
    QLabel *labelExistingChord;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout_2;
    QLabel *labelOldName;
    QLineEdit *lineEditOldName;
    ChordDiagram *widgetOld;
    QPushButton *pushButtonKeepOld;

    void setupUi(QDialog *DialogChooseGoodChord)
    {
        if (DialogChooseGoodChord->objectName().isEmpty())
            DialogChooseGoodChord->setObjectName(QStringLiteral("DialogChooseGoodChord"));
        DialogChooseGoodChord->resize(530, 417);
        horizontalLayout_7 = new QHBoxLayout(DialogChooseGoodChord);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        textEdit = new QTextEdit(DialogChooseGoodChord);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setMaximumSize(QSize(16777215, 100));
        textEdit->setAutoFillBackground(true);
        textEdit->setReadOnly(true);
        textEdit->setOverwriteMode(false);
        textEdit->setTextInteractionFlags(Qt::NoTextInteraction);

        horizontalLayout_6->addWidget(textEdit);


        verticalLayout_3->addLayout(horizontalLayout_6);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        labelNewChord = new QLabel(DialogChooseGoodChord);
        labelNewChord->setObjectName(QStringLiteral("labelNewChord"));

        horizontalLayout_3->addWidget(labelNewChord);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);


        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        labelNameNew = new QLabel(DialogChooseGoodChord);
        labelNameNew->setObjectName(QStringLiteral("labelNameNew"));

        horizontalLayout->addWidget(labelNameNew);

        lineEditNewName = new QLineEdit(DialogChooseGoodChord);
        lineEditNewName->setObjectName(QStringLiteral("lineEditNewName"));

        horizontalLayout->addWidget(lineEditNewName);


        verticalLayout_2->addLayout(horizontalLayout);

        widgetNew = new ChordDiagram(DialogChooseGoodChord);
        widgetNew->setObjectName(QStringLiteral("widgetNew"));
        widgetNew->setMinimumSize(QSize(0, 0));

        verticalLayout_2->addWidget(widgetNew);

        pushButtonReplaceOld = new QPushButton(DialogChooseGoodChord);
        pushButtonReplaceOld->setObjectName(QStringLiteral("pushButtonReplaceOld"));

        verticalLayout_2->addWidget(pushButtonReplaceOld);


        horizontalLayout_5->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_3);

        labelExistingChord = new QLabel(DialogChooseGoodChord);
        labelExistingChord->setObjectName(QStringLiteral("labelExistingChord"));

        horizontalLayout_4->addWidget(labelExistingChord);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        labelOldName = new QLabel(DialogChooseGoodChord);
        labelOldName->setObjectName(QStringLiteral("labelOldName"));

        horizontalLayout_2->addWidget(labelOldName);

        lineEditOldName = new QLineEdit(DialogChooseGoodChord);
        lineEditOldName->setObjectName(QStringLiteral("lineEditOldName"));
        lineEditOldName->setAutoFillBackground(true);
        lineEditOldName->setReadOnly(true);

        horizontalLayout_2->addWidget(lineEditOldName);


        verticalLayout->addLayout(horizontalLayout_2);

        widgetOld = new ChordDiagram(DialogChooseGoodChord);
        widgetOld->setObjectName(QStringLiteral("widgetOld"));
        widgetOld->setMinimumSize(QSize(0, 0));

        verticalLayout->addWidget(widgetOld);

        pushButtonKeepOld = new QPushButton(DialogChooseGoodChord);
        pushButtonKeepOld->setObjectName(QStringLiteral("pushButtonKeepOld"));

        verticalLayout->addWidget(pushButtonKeepOld);


        horizontalLayout_5->addLayout(verticalLayout);


        verticalLayout_3->addLayout(horizontalLayout_5);


        horizontalLayout_7->addLayout(verticalLayout_3);


        retranslateUi(DialogChooseGoodChord);

        QMetaObject::connectSlotsByName(DialogChooseGoodChord);
    } // setupUi

    void retranslateUi(QDialog *DialogChooseGoodChord)
    {
        DialogChooseGoodChord->setWindowTitle(QApplication::translate("DialogChooseGoodChord", "You defined the same name for two Chord !", Q_NULLPTR));
        textEdit->setHtml(QApplication::translate("DialogChooseGoodChord", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Noto Sans'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">The chords name must be different. You have three choices : </p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">1. you can click on <span style=\" font-weight:600;\">Keep old</span> and cancel the new chord design</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">2. you can try to change the new chord name and click on <span style=\" font-weight:600;\">Keep new</span></p>\n"
"<p style=\" margin-top:0px; marg"
                        "in-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">3. you can click on <span style=\" font-weight:600;\">Keep New</span> to save the new one and cancel the old one</p></body></html>", Q_NULLPTR));
        labelNewChord->setText(QApplication::translate("DialogChooseGoodChord", "New chord", Q_NULLPTR));
        labelNameNew->setText(QApplication::translate("DialogChooseGoodChord", "Name", Q_NULLPTR));
        pushButtonReplaceOld->setText(QApplication::translate("DialogChooseGoodChord", "Keep new", Q_NULLPTR));
        labelExistingChord->setText(QApplication::translate("DialogChooseGoodChord", "Existing chord ", Q_NULLPTR));
        labelOldName->setText(QApplication::translate("DialogChooseGoodChord", "Name", Q_NULLPTR));
        pushButtonKeepOld->setText(QApplication::translate("DialogChooseGoodChord", "Keep old", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class DialogChooseGoodChord: public Ui_DialogChooseGoodChord {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGCHOOSEGOODCHORD_H
