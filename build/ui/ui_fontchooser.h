/********************************************************************************
** Form generated from reading UI file 'fontchooser.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FONTCHOOSER_H
#define UI_FONTCHOOSER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include "colorbutton.h"
#include "fontdialog.h"

QT_BEGIN_NAMESPACE

class Ui_FontChooser
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    FontDialog *widget;
    QHBoxLayout *horizontalLayout;
    QLabel *labelFontColor;
    ColorButton *toolButtonFontColor;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QLabel *labelBackgroundColor;
    ColorButton *toolButtonBackgroundColor;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_3;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *FontChooser)
    {
        if (FontChooser->objectName().isEmpty())
            FontChooser->setObjectName(QStringLiteral("FontChooser"));
        FontChooser->resize(565, 483);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(FontChooser->sizePolicy().hasHeightForWidth());
        FontChooser->setSizePolicy(sizePolicy);
        FontChooser->setMinimumSize(QSize(0, 0));
        FontChooser->setAcceptDrops(false);
        verticalLayout_2 = new QVBoxLayout(FontChooser);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetMinimumSize);
        widget = new FontDialog(FontChooser);
        widget->setObjectName(QStringLiteral("widget"));
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);
        widget->setMinimumSize(QSize(0, 0));
        widget->setBaseSize(QSize(400, 400));

        verticalLayout->addWidget(widget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        labelFontColor = new QLabel(FontChooser);
        labelFontColor->setObjectName(QStringLiteral("labelFontColor"));

        horizontalLayout->addWidget(labelFontColor);

        toolButtonFontColor = new ColorButton(FontChooser);
        toolButtonFontColor->setObjectName(QStringLiteral("toolButtonFontColor"));

        horizontalLayout->addWidget(toolButtonFontColor);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        labelBackgroundColor = new QLabel(FontChooser);
        labelBackgroundColor->setObjectName(QStringLiteral("labelBackgroundColor"));

        horizontalLayout_2->addWidget(labelBackgroundColor);

        toolButtonBackgroundColor = new ColorButton(FontChooser);
        toolButtonBackgroundColor->setObjectName(QStringLiteral("toolButtonBackgroundColor"));

        horizontalLayout_2->addWidget(toolButtonBackgroundColor);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        buttonBox = new QDialogButtonBox(FontChooser);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        horizontalLayout_3->addWidget(buttonBox);


        verticalLayout->addLayout(horizontalLayout_3);

        verticalLayout->setStretch(0, 6);
        verticalLayout->setStretch(1, 1);
        verticalLayout->setStretch(2, 1);
        verticalLayout->setStretch(3, 1);

        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(FontChooser);
        QObject::connect(buttonBox, SIGNAL(accepted()), FontChooser, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), FontChooser, SLOT(reject()));

        QMetaObject::connectSlotsByName(FontChooser);
    } // setupUi

    void retranslateUi(QDialog *FontChooser)
    {
        FontChooser->setWindowTitle(QApplication::translate("FontChooser", "Select Font and colors", Q_NULLPTR));
        labelFontColor->setText(QApplication::translate("FontChooser", "Font color", Q_NULLPTR));
        toolButtonFontColor->setText(QApplication::translate("FontChooser", "...", Q_NULLPTR));
        labelBackgroundColor->setText(QApplication::translate("FontChooser", "Background color", Q_NULLPTR));
        toolButtonBackgroundColor->setText(QApplication::translate("FontChooser", "...", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class FontChooser: public Ui_FontChooser {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FONTCHOOSER_H
