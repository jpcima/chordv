/********************************************************************************
** Form generated from reading UI file 'dialogsearch.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGSEARCH_H
#define UI_DIALOGSEARCH_H

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

class Ui_DialogSearch
{
public:
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *labelTextToSearch;
    QLineEdit *lineEditTextToSearch;
    QHBoxLayout *horizontalLayout;
    QCheckBox *checkBoxCaseSenstitve;
    QCheckBox *checkBoxWordONly;
    QPushButton *pushButtonPrevious;
    QPushButton *pushButtonSearch;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButtonClose;

    void setupUi(QDialog *DialogSearch)
    {
        if (DialogSearch->objectName().isEmpty())
            DialogSearch->setObjectName(QStringLiteral("DialogSearch"));
        DialogSearch->resize(387, 113);
        horizontalLayout_4 = new QHBoxLayout(DialogSearch);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        labelTextToSearch = new QLabel(DialogSearch);
        labelTextToSearch->setObjectName(QStringLiteral("labelTextToSearch"));

        horizontalLayout_2->addWidget(labelTextToSearch);

        lineEditTextToSearch = new QLineEdit(DialogSearch);
        lineEditTextToSearch->setObjectName(QStringLiteral("lineEditTextToSearch"));

        horizontalLayout_2->addWidget(lineEditTextToSearch);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        checkBoxCaseSenstitve = new QCheckBox(DialogSearch);
        checkBoxCaseSenstitve->setObjectName(QStringLiteral("checkBoxCaseSenstitve"));

        horizontalLayout->addWidget(checkBoxCaseSenstitve);

        checkBoxWordONly = new QCheckBox(DialogSearch);
        checkBoxWordONly->setObjectName(QStringLiteral("checkBoxWordONly"));

        horizontalLayout->addWidget(checkBoxWordONly);

        pushButtonPrevious = new QPushButton(DialogSearch);
        pushButtonPrevious->setObjectName(QStringLiteral("pushButtonPrevious"));
        pushButtonPrevious->setAutoDefault(false);

        horizontalLayout->addWidget(pushButtonPrevious);

        pushButtonSearch = new QPushButton(DialogSearch);
        pushButtonSearch->setObjectName(QStringLiteral("pushButtonSearch"));

        horizontalLayout->addWidget(pushButtonSearch);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        pushButtonClose = new QPushButton(DialogSearch);
        pushButtonClose->setObjectName(QStringLiteral("pushButtonClose"));
        pushButtonClose->setAutoDefault(false);

        horizontalLayout_3->addWidget(pushButtonClose);


        verticalLayout->addLayout(horizontalLayout_3);


        horizontalLayout_4->addLayout(verticalLayout);


        retranslateUi(DialogSearch);

        pushButtonSearch->setDefault(true);


        QMetaObject::connectSlotsByName(DialogSearch);
    } // setupUi

    void retranslateUi(QDialog *DialogSearch)
    {
        DialogSearch->setWindowTitle(QApplication::translate("DialogSearch", "Search", Q_NULLPTR));
        labelTextToSearch->setText(QApplication::translate("DialogSearch", "Text to Search ", Q_NULLPTR));
        checkBoxCaseSenstitve->setText(QApplication::translate("DialogSearch", "Case sentitive", Q_NULLPTR));
        checkBoxWordONly->setText(QApplication::translate("DialogSearch", "Word only", Q_NULLPTR));
        pushButtonPrevious->setText(QApplication::translate("DialogSearch", "Previous", Q_NULLPTR));
        pushButtonSearch->setText(QApplication::translate("DialogSearch", "Search", Q_NULLPTR));
        pushButtonClose->setText(QApplication::translate("DialogSearch", "Close", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class DialogSearch: public Ui_DialogSearch {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGSEARCH_H
