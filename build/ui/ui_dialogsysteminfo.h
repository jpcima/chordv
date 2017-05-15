/********************************************************************************
** Form generated from reading UI file 'dialogsysteminfo.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGSYSTEMINFO_H
#define UI_DIALOGSYSTEMINFO_H

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
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DialogSystemInfo
{
public:
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *labelNme;
    QLabel *labelNameProgramArguments;
    QLabel *labelNameProgramArguments_2;
    QLabel *labelVersion;
    QLabel *labelGitVersion;
    QLabel *labelDateCompilation;
    QLabel *labelPid;
    QLabel *labelConfiguration;
    QLabel *labelDatabase;
    QVBoxLayout *verticalLayout_2;
    QLineEdit *lineEditName;
    QLineEdit *lineEditProgramArguments;
    QLineEdit *lineEditLocation;
    QLineEdit *lineEditVersion;
    QLineEdit *lineEditGitVersion;
    QLineEdit *lineEditDateCompilation;
    QLineEdit *lineEditPid;
    QLineEdit *lineEditConfiguration;
    QLineEdit *lineEditDatabase;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButtonClose;

    void setupUi(QDialog *DialogSystemInfo)
    {
        if (DialogSystemInfo->objectName().isEmpty())
            DialogSystemInfo->setObjectName(QStringLiteral("DialogSystemInfo"));
        DialogSystemInfo->resize(478, 330);
        horizontalLayout_3 = new QHBoxLayout(DialogSystemInfo);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        labelNme = new QLabel(DialogSystemInfo);
        labelNme->setObjectName(QStringLiteral("labelNme"));

        verticalLayout->addWidget(labelNme);

        labelNameProgramArguments = new QLabel(DialogSystemInfo);
        labelNameProgramArguments->setObjectName(QStringLiteral("labelNameProgramArguments"));

        verticalLayout->addWidget(labelNameProgramArguments);

        labelNameProgramArguments_2 = new QLabel(DialogSystemInfo);
        labelNameProgramArguments_2->setObjectName(QStringLiteral("labelNameProgramArguments_2"));

        verticalLayout->addWidget(labelNameProgramArguments_2);

        labelVersion = new QLabel(DialogSystemInfo);
        labelVersion->setObjectName(QStringLiteral("labelVersion"));

        verticalLayout->addWidget(labelVersion);

        labelGitVersion = new QLabel(DialogSystemInfo);
        labelGitVersion->setObjectName(QStringLiteral("labelGitVersion"));

        verticalLayout->addWidget(labelGitVersion);

        labelDateCompilation = new QLabel(DialogSystemInfo);
        labelDateCompilation->setObjectName(QStringLiteral("labelDateCompilation"));

        verticalLayout->addWidget(labelDateCompilation);

        labelPid = new QLabel(DialogSystemInfo);
        labelPid->setObjectName(QStringLiteral("labelPid"));

        verticalLayout->addWidget(labelPid);

        labelConfiguration = new QLabel(DialogSystemInfo);
        labelConfiguration->setObjectName(QStringLiteral("labelConfiguration"));

        verticalLayout->addWidget(labelConfiguration);

        labelDatabase = new QLabel(DialogSystemInfo);
        labelDatabase->setObjectName(QStringLiteral("labelDatabase"));

        verticalLayout->addWidget(labelDatabase);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        lineEditName = new QLineEdit(DialogSystemInfo);
        lineEditName->setObjectName(QStringLiteral("lineEditName"));
        lineEditName->setReadOnly(true);

        verticalLayout_2->addWidget(lineEditName);

        lineEditProgramArguments = new QLineEdit(DialogSystemInfo);
        lineEditProgramArguments->setObjectName(QStringLiteral("lineEditProgramArguments"));
        lineEditProgramArguments->setReadOnly(true);

        verticalLayout_2->addWidget(lineEditProgramArguments);

        lineEditLocation = new QLineEdit(DialogSystemInfo);
        lineEditLocation->setObjectName(QStringLiteral("lineEditLocation"));
        lineEditLocation->setReadOnly(true);

        verticalLayout_2->addWidget(lineEditLocation);

        lineEditVersion = new QLineEdit(DialogSystemInfo);
        lineEditVersion->setObjectName(QStringLiteral("lineEditVersion"));
        lineEditVersion->setReadOnly(true);

        verticalLayout_2->addWidget(lineEditVersion);

        lineEditGitVersion = new QLineEdit(DialogSystemInfo);
        lineEditGitVersion->setObjectName(QStringLiteral("lineEditGitVersion"));
        lineEditGitVersion->setReadOnly(true);

        verticalLayout_2->addWidget(lineEditGitVersion);

        lineEditDateCompilation = new QLineEdit(DialogSystemInfo);
        lineEditDateCompilation->setObjectName(QStringLiteral("lineEditDateCompilation"));
        lineEditDateCompilation->setReadOnly(true);

        verticalLayout_2->addWidget(lineEditDateCompilation);

        lineEditPid = new QLineEdit(DialogSystemInfo);
        lineEditPid->setObjectName(QStringLiteral("lineEditPid"));
        lineEditPid->setReadOnly(true);

        verticalLayout_2->addWidget(lineEditPid);

        lineEditConfiguration = new QLineEdit(DialogSystemInfo);
        lineEditConfiguration->setObjectName(QStringLiteral("lineEditConfiguration"));
        lineEditConfiguration->setReadOnly(true);

        verticalLayout_2->addWidget(lineEditConfiguration);

        lineEditDatabase = new QLineEdit(DialogSystemInfo);
        lineEditDatabase->setObjectName(QStringLiteral("lineEditDatabase"));
        lineEditDatabase->setReadOnly(true);

        verticalLayout_2->addWidget(lineEditDatabase);


        horizontalLayout->addLayout(verticalLayout_2);


        verticalLayout_3->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        pushButtonClose = new QPushButton(DialogSystemInfo);
        pushButtonClose->setObjectName(QStringLiteral("pushButtonClose"));

        horizontalLayout_2->addWidget(pushButtonClose);


        verticalLayout_3->addLayout(horizontalLayout_2);


        horizontalLayout_3->addLayout(verticalLayout_3);


        retranslateUi(DialogSystemInfo);
        QObject::connect(pushButtonClose, SIGNAL(clicked()), DialogSystemInfo, SLOT(close()));

        QMetaObject::connectSlotsByName(DialogSystemInfo);
    } // setupUi

    void retranslateUi(QDialog *DialogSystemInfo)
    {
        DialogSystemInfo->setWindowTitle(QApplication::translate("DialogSystemInfo", "System informations", Q_NULLPTR));
        labelNme->setText(QApplication::translate("DialogSystemInfo", "Program name", Q_NULLPTR));
        labelNameProgramArguments->setText(QApplication::translate("DialogSystemInfo", "Program arguments", Q_NULLPTR));
        labelNameProgramArguments_2->setText(QApplication::translate("DialogSystemInfo", "Program Location", Q_NULLPTR));
        labelVersion->setText(QApplication::translate("DialogSystemInfo", "Program version", Q_NULLPTR));
        labelGitVersion->setText(QApplication::translate("DialogSystemInfo", "Git version", Q_NULLPTR));
        labelDateCompilation->setText(QApplication::translate("DialogSystemInfo", "Compilation date", Q_NULLPTR));
        labelPid->setText(QApplication::translate("DialogSystemInfo", "Program Pid", Q_NULLPTR));
        labelConfiguration->setText(QApplication::translate("DialogSystemInfo", "Configuration file", Q_NULLPTR));
        labelDatabase->setText(QApplication::translate("DialogSystemInfo", "Database name", Q_NULLPTR));
        pushButtonClose->setText(QApplication::translate("DialogSystemInfo", "Close", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class DialogSystemInfo: public Ui_DialogSystemInfo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGSYSTEMINFO_H
