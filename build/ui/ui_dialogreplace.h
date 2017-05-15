/********************************************************************************
** Form generated from reading UI file 'dialogreplace.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGREPLACE_H
#define UI_DIALOGREPLACE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DialogReplace
{
public:
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *labelTextToReplace;
    QLabel *labelReplaceWith;
    QVBoxLayout *verticalLayout_2;
    QLineEdit *lineEditTextToReplace;
    QLineEdit *lineEditReplaceWith;
    QVBoxLayout *verticalLayout_3;
    QPushButton *pushButtonSearch;
    QPushButton *pushButtonReplace;
    QPushButton *pushButtonSkip;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_3;
    QCheckBox *checkBoxBackward;
    QCheckBox *checkBoxAllDocument;
    QCheckBox *checkBoxCaseSensitive;
    QCheckBox *checkBoxWordOnly;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButtonClose;

    void setupUi(QDialog *DialogReplace)
    {
        if (DialogReplace->objectName().isEmpty())
            DialogReplace->setObjectName(QStringLiteral("DialogReplace"));
        DialogReplace->resize(530, 191);
        horizontalLayout_4 = new QHBoxLayout(DialogReplace);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        labelTextToReplace = new QLabel(DialogReplace);
        labelTextToReplace->setObjectName(QStringLiteral("labelTextToReplace"));

        verticalLayout->addWidget(labelTextToReplace);

        labelReplaceWith = new QLabel(DialogReplace);
        labelReplaceWith->setObjectName(QStringLiteral("labelReplaceWith"));

        verticalLayout->addWidget(labelReplaceWith);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        lineEditTextToReplace = new QLineEdit(DialogReplace);
        lineEditTextToReplace->setObjectName(QStringLiteral("lineEditTextToReplace"));

        verticalLayout_2->addWidget(lineEditTextToReplace);

        lineEditReplaceWith = new QLineEdit(DialogReplace);
        lineEditReplaceWith->setObjectName(QStringLiteral("lineEditReplaceWith"));

        verticalLayout_2->addWidget(lineEditReplaceWith);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        pushButtonSearch = new QPushButton(DialogReplace);
        pushButtonSearch->setObjectName(QStringLiteral("pushButtonSearch"));

        verticalLayout_3->addWidget(pushButtonSearch);

        pushButtonReplace = new QPushButton(DialogReplace);
        pushButtonReplace->setObjectName(QStringLiteral("pushButtonReplace"));

        verticalLayout_3->addWidget(pushButtonReplace);

        pushButtonSkip = new QPushButton(DialogReplace);
        pushButtonSkip->setObjectName(QStringLiteral("pushButtonSkip"));

        verticalLayout_3->addWidget(pushButtonSkip);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);


        horizontalLayout->addLayout(verticalLayout_3);


        verticalLayout_4->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        checkBoxBackward = new QCheckBox(DialogReplace);
        checkBoxBackward->setObjectName(QStringLiteral("checkBoxBackward"));

        horizontalLayout_3->addWidget(checkBoxBackward);

        checkBoxAllDocument = new QCheckBox(DialogReplace);
        checkBoxAllDocument->setObjectName(QStringLiteral("checkBoxAllDocument"));

        horizontalLayout_3->addWidget(checkBoxAllDocument);

        checkBoxCaseSensitive = new QCheckBox(DialogReplace);
        checkBoxCaseSensitive->setObjectName(QStringLiteral("checkBoxCaseSensitive"));

        horizontalLayout_3->addWidget(checkBoxCaseSensitive);

        checkBoxWordOnly = new QCheckBox(DialogReplace);
        checkBoxWordOnly->setObjectName(QStringLiteral("checkBoxWordOnly"));

        horizontalLayout_3->addWidget(checkBoxWordOnly);


        verticalLayout_4->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        pushButtonClose = new QPushButton(DialogReplace);
        pushButtonClose->setObjectName(QStringLiteral("pushButtonClose"));
        pushButtonClose->setAutoDefault(false);

        horizontalLayout_2->addWidget(pushButtonClose);


        verticalLayout_4->addLayout(horizontalLayout_2);


        horizontalLayout_4->addLayout(verticalLayout_4);


        retranslateUi(DialogReplace);

        pushButtonSearch->setDefault(true);
        pushButtonReplace->setDefault(false);


        QMetaObject::connectSlotsByName(DialogReplace);
    } // setupUi

    void retranslateUi(QDialog *DialogReplace)
    {
        DialogReplace->setWindowTitle(QApplication::translate("DialogReplace", "Search and replace", Q_NULLPTR));
        labelTextToReplace->setText(QApplication::translate("DialogReplace", "Text to replace", Q_NULLPTR));
        labelReplaceWith->setText(QApplication::translate("DialogReplace", "Replace with ", Q_NULLPTR));
        pushButtonSearch->setText(QApplication::translate("DialogReplace", "Search", Q_NULLPTR));
        pushButtonReplace->setText(QApplication::translate("DialogReplace", "Replace", Q_NULLPTR));
        pushButtonSkip->setText(QApplication::translate("DialogReplace", "Skip", Q_NULLPTR));
        checkBoxBackward->setText(QApplication::translate("DialogReplace", "Backward", Q_NULLPTR));
        checkBoxAllDocument->setText(QApplication::translate("DialogReplace", "All Document", Q_NULLPTR));
        checkBoxCaseSensitive->setText(QApplication::translate("DialogReplace", "Case sensitive", Q_NULLPTR));
        checkBoxWordOnly->setText(QApplication::translate("DialogReplace", "Word only", Q_NULLPTR));
        pushButtonClose->setText(QApplication::translate("DialogReplace", "Close", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class DialogReplace: public Ui_DialogReplace {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGREPLACE_H
