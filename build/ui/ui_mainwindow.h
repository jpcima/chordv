/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "chordconfig.h"
#include "logmessages.h"
#include "lyricsconfig.h"
#include "memoryconfig.h"
#include "textconfig.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionNew_Project;
    QAction *actionOpen_Project;
    QAction *actionQuit;
    QAction *actionSave_Current_as_Defaut;
    QAction *actionSave;
    QAction *actionSave_As;
    QAction *actionHelp;
    QAction *actionAbout;
    QAction *actionLast_Project;
    QAction *actionLast_Poject;
    QAction *actionProduce_PDF_files;
    QAction *actionPreferences;
    QAction *actionOpen_Song_File;
    QAction *actionReset_Preference_as_origine;
    QAction *actionChord_defintion;
    QAction *actionSystem_Info;
    QAction *actionSearch;
    QAction *actionReplace;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_6;
    QSplitter *splitter;
    QTabWidget *tabWidget;
    QWidget *General;
    QVBoxLayout *verticalLayout_12;
    QVBoxLayout *verticalLayout_11;
    QHBoxLayout *horizontalLayout_11;
    QHBoxLayout *horizontalLayout_10;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout;
    QLabel *labelInputFile;
    QLineEdit *lineEditInputFile;
    QToolButton *toolButtonInputFile;
    QHBoxLayout *horizontalLayout_2;
    QLabel *labelCreatorName;
    QLineEdit *lineEditCreatorName;
    QHBoxLayout *horizontalLayout_3;
    QLabel *labelChordLanguage;
    QComboBox *comboBoxChordLanguage;
    QCheckBox *checkBoxLyricsMode;
    QCheckBox *checkBoxChordMode;
    QCheckBox *checkBoxTextMode;
    QCheckBox *checkBoxMemoryMode;
    QHBoxLayout *horizontalLayout_4;
    QLabel *labelWatermark;
    QLineEdit *lineEditWatermark;
    QVBoxLayout *verticalLayout_8;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_5;
    QLabel *labelProjectName;
    QLabel *labelNameProjectName;
    QHBoxLayout *horizontalLayout_7;
    QLabel *labelDirProject;
    QLabel *labelNameDirProject;
    QPushButton *pushButtonMakePDF;
    QPushButton *pushButtonMakeAndShowPDF;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer;
    QWidget *LyricsMode;
    QVBoxLayout *verticalLayout_3;
    LyricsConfig *widgetLyricsMode;
    QWidget *ChordMode;
    QVBoxLayout *verticalLayout_4;
    ChordConfig *widgetChordMode;
    QWidget *TextMode;
    QVBoxLayout *verticalLayout_2;
    TextConfig *widgetTextMode;
    QWidget *MemoryMode;
    QVBoxLayout *verticalLayout;
    MemoryConfig *widgetMemoryMode;
    QWidget *Editor2;
    QHBoxLayout *horizontalLayout_9;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout_8;
    QToolButton *toolButtonCT;
    QToolButton *toolButtonCS;
    QToolButton *toolButtonT;
    QToolButton *toolButtonST;
    QToolButton *toolButtonCol;
    QToolButton *toolButtonCB;
    QToolButton *toolButtonCompress;
    QToolButton *toolButtonSOC;
    QToolButton *toolButtonEOC;
    QToolButton *toolButtonREF;
    QComboBox *comboBox;
    QFrame *line;
    QCheckBox *checkBoxLongShort;
    QTextEdit *textEditCho3File;
    LogMessages *log;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuTools;
    QMenu *menuHelp;
    QMenu *menuEdition;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1101, 732);
        QIcon icon;
        icon.addFile(QStringLiteral(":/Image/Images/icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        actionNew_Project = new QAction(MainWindow);
        actionNew_Project->setObjectName(QStringLiteral("actionNew_Project"));
        actionOpen_Project = new QAction(MainWindow);
        actionOpen_Project->setObjectName(QStringLiteral("actionOpen_Project"));
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QStringLiteral("actionQuit"));
        actionSave_Current_as_Defaut = new QAction(MainWindow);
        actionSave_Current_as_Defaut->setObjectName(QStringLiteral("actionSave_Current_as_Defaut"));
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        actionSave_As = new QAction(MainWindow);
        actionSave_As->setObjectName(QStringLiteral("actionSave_As"));
        actionHelp = new QAction(MainWindow);
        actionHelp->setObjectName(QStringLiteral("actionHelp"));
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        actionLast_Project = new QAction(MainWindow);
        actionLast_Project->setObjectName(QStringLiteral("actionLast_Project"));
        actionLast_Poject = new QAction(MainWindow);
        actionLast_Poject->setObjectName(QStringLiteral("actionLast_Poject"));
        actionProduce_PDF_files = new QAction(MainWindow);
        actionProduce_PDF_files->setObjectName(QStringLiteral("actionProduce_PDF_files"));
        actionPreferences = new QAction(MainWindow);
        actionPreferences->setObjectName(QStringLiteral("actionPreferences"));
        actionOpen_Song_File = new QAction(MainWindow);
        actionOpen_Song_File->setObjectName(QStringLiteral("actionOpen_Song_File"));
        actionReset_Preference_as_origine = new QAction(MainWindow);
        actionReset_Preference_as_origine->setObjectName(QStringLiteral("actionReset_Preference_as_origine"));
        actionChord_defintion = new QAction(MainWindow);
        actionChord_defintion->setObjectName(QStringLiteral("actionChord_defintion"));
        actionSystem_Info = new QAction(MainWindow);
        actionSystem_Info->setObjectName(QStringLiteral("actionSystem_Info"));
        actionSearch = new QAction(MainWindow);
        actionSearch->setObjectName(QStringLiteral("actionSearch"));
        actionReplace = new QAction(MainWindow);
        actionReplace->setObjectName(QStringLiteral("actionReplace"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout_6 = new QHBoxLayout(centralWidget);
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        splitter = new QSplitter(centralWidget);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Vertical);
        tabWidget = new QTabWidget(splitter);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setTabBarAutoHide(true);
        General = new QWidget();
        General->setObjectName(QStringLiteral("General"));
        verticalLayout_12 = new QVBoxLayout(General);
        verticalLayout_12->setSpacing(6);
        verticalLayout_12->setContentsMargins(11, 11, 11, 11);
        verticalLayout_12->setObjectName(QStringLiteral("verticalLayout_12"));
        verticalLayout_11 = new QVBoxLayout();
        verticalLayout_11->setSpacing(6);
        verticalLayout_11->setObjectName(QStringLiteral("verticalLayout_11"));
        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        labelInputFile = new QLabel(General);
        labelInputFile->setObjectName(QStringLiteral("labelInputFile"));

        horizontalLayout->addWidget(labelInputFile);

        lineEditInputFile = new QLineEdit(General);
        lineEditInputFile->setObjectName(QStringLiteral("lineEditInputFile"));

        horizontalLayout->addWidget(lineEditInputFile);

        toolButtonInputFile = new QToolButton(General);
        toolButtonInputFile->setObjectName(QStringLiteral("toolButtonInputFile"));

        horizontalLayout->addWidget(toolButtonInputFile);


        verticalLayout_5->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        labelCreatorName = new QLabel(General);
        labelCreatorName->setObjectName(QStringLiteral("labelCreatorName"));

        horizontalLayout_2->addWidget(labelCreatorName);

        lineEditCreatorName = new QLineEdit(General);
        lineEditCreatorName->setObjectName(QStringLiteral("lineEditCreatorName"));

        horizontalLayout_2->addWidget(lineEditCreatorName);


        verticalLayout_5->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        labelChordLanguage = new QLabel(General);
        labelChordLanguage->setObjectName(QStringLiteral("labelChordLanguage"));

        horizontalLayout_3->addWidget(labelChordLanguage);

        comboBoxChordLanguage = new QComboBox(General);
        comboBoxChordLanguage->setObjectName(QStringLiteral("comboBoxChordLanguage"));

        horizontalLayout_3->addWidget(comboBoxChordLanguage);


        verticalLayout_5->addLayout(horizontalLayout_3);

        checkBoxLyricsMode = new QCheckBox(General);
        checkBoxLyricsMode->setObjectName(QStringLiteral("checkBoxLyricsMode"));
        checkBoxLyricsMode->setChecked(true);

        verticalLayout_5->addWidget(checkBoxLyricsMode);

        checkBoxChordMode = new QCheckBox(General);
        checkBoxChordMode->setObjectName(QStringLiteral("checkBoxChordMode"));
        checkBoxChordMode->setChecked(true);

        verticalLayout_5->addWidget(checkBoxChordMode);

        checkBoxTextMode = new QCheckBox(General);
        checkBoxTextMode->setObjectName(QStringLiteral("checkBoxTextMode"));
        checkBoxTextMode->setChecked(true);

        verticalLayout_5->addWidget(checkBoxTextMode);

        checkBoxMemoryMode = new QCheckBox(General);
        checkBoxMemoryMode->setObjectName(QStringLiteral("checkBoxMemoryMode"));
        checkBoxMemoryMode->setChecked(true);

        verticalLayout_5->addWidget(checkBoxMemoryMode);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        labelWatermark = new QLabel(General);
        labelWatermark->setObjectName(QStringLiteral("labelWatermark"));

        horizontalLayout_4->addWidget(labelWatermark);

        lineEditWatermark = new QLineEdit(General);
        lineEditWatermark->setObjectName(QStringLiteral("lineEditWatermark"));

        horizontalLayout_4->addWidget(lineEditWatermark);


        verticalLayout_5->addLayout(horizontalLayout_4);


        horizontalLayout_10->addLayout(verticalLayout_5);

        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        labelProjectName = new QLabel(General);
        labelProjectName->setObjectName(QStringLiteral("labelProjectName"));

        horizontalLayout_5->addWidget(labelProjectName);

        labelNameProjectName = new QLabel(General);
        labelNameProjectName->setObjectName(QStringLiteral("labelNameProjectName"));

        horizontalLayout_5->addWidget(labelNameProjectName);


        verticalLayout_6->addLayout(horizontalLayout_5);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        labelDirProject = new QLabel(General);
        labelDirProject->setObjectName(QStringLiteral("labelDirProject"));

        horizontalLayout_7->addWidget(labelDirProject);

        labelNameDirProject = new QLabel(General);
        labelNameDirProject->setObjectName(QStringLiteral("labelNameDirProject"));

        horizontalLayout_7->addWidget(labelNameDirProject);


        verticalLayout_6->addLayout(horizontalLayout_7);


        verticalLayout_8->addLayout(verticalLayout_6);

        pushButtonMakePDF = new QPushButton(General);
        pushButtonMakePDF->setObjectName(QStringLiteral("pushButtonMakePDF"));
        pushButtonMakePDF->setMinimumSize(QSize(100, 100));

        verticalLayout_8->addWidget(pushButtonMakePDF);

        pushButtonMakeAndShowPDF = new QPushButton(General);
        pushButtonMakeAndShowPDF->setObjectName(QStringLiteral("pushButtonMakeAndShowPDF"));
        pushButtonMakeAndShowPDF->setMinimumSize(QSize(100, 100));

        verticalLayout_8->addWidget(pushButtonMakeAndShowPDF);


        horizontalLayout_10->addLayout(verticalLayout_8);


        horizontalLayout_11->addLayout(horizontalLayout_10);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer);


        verticalLayout_11->addLayout(horizontalLayout_11);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_11->addItem(verticalSpacer);


        verticalLayout_12->addLayout(verticalLayout_11);

        tabWidget->addTab(General, QString());
        LyricsMode = new QWidget();
        LyricsMode->setObjectName(QStringLiteral("LyricsMode"));
        verticalLayout_3 = new QVBoxLayout(LyricsMode);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        widgetLyricsMode = new LyricsConfig(LyricsMode);
        widgetLyricsMode->setObjectName(QStringLiteral("widgetLyricsMode"));

        verticalLayout_3->addWidget(widgetLyricsMode);

        tabWidget->addTab(LyricsMode, QString());
        ChordMode = new QWidget();
        ChordMode->setObjectName(QStringLiteral("ChordMode"));
        verticalLayout_4 = new QVBoxLayout(ChordMode);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        widgetChordMode = new ChordConfig(ChordMode);
        widgetChordMode->setObjectName(QStringLiteral("widgetChordMode"));

        verticalLayout_4->addWidget(widgetChordMode);

        tabWidget->addTab(ChordMode, QString());
        TextMode = new QWidget();
        TextMode->setObjectName(QStringLiteral("TextMode"));
        verticalLayout_2 = new QVBoxLayout(TextMode);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        widgetTextMode = new TextConfig(TextMode);
        widgetTextMode->setObjectName(QStringLiteral("widgetTextMode"));

        verticalLayout_2->addWidget(widgetTextMode);

        tabWidget->addTab(TextMode, QString());
        MemoryMode = new QWidget();
        MemoryMode->setObjectName(QStringLiteral("MemoryMode"));
        verticalLayout = new QVBoxLayout(MemoryMode);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        widgetMemoryMode = new MemoryConfig(MemoryMode);
        widgetMemoryMode->setObjectName(QStringLiteral("widgetMemoryMode"));

        verticalLayout->addWidget(widgetMemoryMode);

        tabWidget->addTab(MemoryMode, QString());
        Editor2 = new QWidget();
        Editor2->setObjectName(QStringLiteral("Editor2"));
        horizontalLayout_9 = new QHBoxLayout(Editor2);
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        toolButtonCT = new QToolButton(Editor2);
        toolButtonCT->setObjectName(QStringLiteral("toolButtonCT"));

        horizontalLayout_8->addWidget(toolButtonCT);

        toolButtonCS = new QToolButton(Editor2);
        toolButtonCS->setObjectName(QStringLiteral("toolButtonCS"));

        horizontalLayout_8->addWidget(toolButtonCS);

        toolButtonT = new QToolButton(Editor2);
        toolButtonT->setObjectName(QStringLiteral("toolButtonT"));

        horizontalLayout_8->addWidget(toolButtonT);

        toolButtonST = new QToolButton(Editor2);
        toolButtonST->setObjectName(QStringLiteral("toolButtonST"));

        horizontalLayout_8->addWidget(toolButtonST);

        toolButtonCol = new QToolButton(Editor2);
        toolButtonCol->setObjectName(QStringLiteral("toolButtonCol"));

        horizontalLayout_8->addWidget(toolButtonCol);

        toolButtonCB = new QToolButton(Editor2);
        toolButtonCB->setObjectName(QStringLiteral("toolButtonCB"));

        horizontalLayout_8->addWidget(toolButtonCB);

        toolButtonCompress = new QToolButton(Editor2);
        toolButtonCompress->setObjectName(QStringLiteral("toolButtonCompress"));

        horizontalLayout_8->addWidget(toolButtonCompress);

        toolButtonSOC = new QToolButton(Editor2);
        toolButtonSOC->setObjectName(QStringLiteral("toolButtonSOC"));

        horizontalLayout_8->addWidget(toolButtonSOC);

        toolButtonEOC = new QToolButton(Editor2);
        toolButtonEOC->setObjectName(QStringLiteral("toolButtonEOC"));

        horizontalLayout_8->addWidget(toolButtonEOC);

        toolButtonREF = new QToolButton(Editor2);
        toolButtonREF->setObjectName(QStringLiteral("toolButtonREF"));

        horizontalLayout_8->addWidget(toolButtonREF);

        comboBox = new QComboBox(Editor2);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_8->addWidget(comboBox);

        line = new QFrame(Editor2);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        horizontalLayout_8->addWidget(line);

        checkBoxLongShort = new QCheckBox(Editor2);
        checkBoxLongShort->setObjectName(QStringLiteral("checkBoxLongShort"));
        checkBoxLongShort->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_8->addWidget(checkBoxLongShort);


        verticalLayout_7->addLayout(horizontalLayout_8);

        textEditCho3File = new QTextEdit(Editor2);
        textEditCho3File->setObjectName(QStringLiteral("textEditCho3File"));

        verticalLayout_7->addWidget(textEditCho3File);


        horizontalLayout_9->addLayout(verticalLayout_7);

        tabWidget->addTab(Editor2, QString());
        splitter->addWidget(tabWidget);
        log = new LogMessages(splitter);
        log->setObjectName(QStringLiteral("log"));
        splitter->addWidget(log);

        horizontalLayout_6->addWidget(splitter);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1101, 22));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuTools = new QMenu(menuBar);
        menuTools->setObjectName(QStringLiteral("menuTools"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        menuEdition = new QMenu(menuBar);
        menuEdition->setObjectName(QStringLiteral("menuEdition"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuEdition->menuAction());
        menuBar->addAction(menuTools->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionNew_Project);
        menuFile->addAction(actionOpen_Project);
        menuFile->addAction(actionOpen_Song_File);
        menuFile->addAction(actionSave);
        menuFile->addAction(actionSave_As);
        menuFile->addAction(actionQuit);
        menuTools->addAction(actionProduce_PDF_files);
        menuTools->addAction(actionPreferences);
        menuTools->addAction(actionChord_defintion);
        menuTools->addAction(actionSave_Current_as_Defaut);
        menuTools->addAction(actionReset_Preference_as_origine);
        menuHelp->addAction(actionHelp);
        menuHelp->addAction(actionAbout);
        menuHelp->addAction(actionSystem_Info);
        menuEdition->addAction(actionSearch);
        menuEdition->addAction(actionReplace);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Chord V", Q_NULLPTR));
        actionNew_Project->setText(QApplication::translate("MainWindow", "&New Project", Q_NULLPTR));
        actionOpen_Project->setText(QApplication::translate("MainWindow", "&Open Project", Q_NULLPTR));
        actionQuit->setText(QApplication::translate("MainWindow", "&Quit", Q_NULLPTR));
        actionSave_Current_as_Defaut->setText(QApplication::translate("MainWindow", "&Save Current as Defaut", Q_NULLPTR));
        actionSave->setText(QApplication::translate("MainWindow", "Sa&ve", Q_NULLPTR));
        actionSave->setShortcut(QApplication::translate("MainWindow", "Ctrl+S", Q_NULLPTR));
        actionSave_As->setText(QApplication::translate("MainWindow", "Sav&e As", Q_NULLPTR));
        actionHelp->setText(QApplication::translate("MainWindow", "&Help", Q_NULLPTR));
        actionAbout->setText(QApplication::translate("MainWindow", "&About", Q_NULLPTR));
        actionLast_Project->setText(QApplication::translate("MainWindow", "Last Project", Q_NULLPTR));
        actionLast_Poject->setText(QApplication::translate("MainWindow", "&Last Projects", Q_NULLPTR));
        actionProduce_PDF_files->setText(QApplication::translate("MainWindow", "&Produce PDF files", Q_NULLPTR));
        actionPreferences->setText(QApplication::translate("MainWindow", "Pr&eferences", Q_NULLPTR));
        actionOpen_Song_File->setText(QApplication::translate("MainWindow", "Open &Song File", Q_NULLPTR));
        actionReset_Preference_as_origine->setText(QApplication::translate("MainWindow", "&Reset Preference as origine", Q_NULLPTR));
        actionChord_defintion->setText(QApplication::translate("MainWindow", "&Chord definition", Q_NULLPTR));
        actionChord_defintion->setShortcut(QApplication::translate("MainWindow", "F3", Q_NULLPTR));
        actionSystem_Info->setText(QApplication::translate("MainWindow", "&System Info", Q_NULLPTR));
        actionSearch->setText(QApplication::translate("MainWindow", "Find", Q_NULLPTR));
        actionSearch->setShortcut(QApplication::translate("MainWindow", "Ctrl+F", Q_NULLPTR));
        actionReplace->setText(QApplication::translate("MainWindow", "Replace", Q_NULLPTR));
        actionReplace->setShortcut(QApplication::translate("MainWindow", "Ctrl+R", Q_NULLPTR));
        labelInputFile->setText(QApplication::translate("MainWindow", "Input File", Q_NULLPTR));
        toolButtonInputFile->setText(QApplication::translate("MainWindow", "...", Q_NULLPTR));
        labelCreatorName->setText(QApplication::translate("MainWindow", "Creator name", Q_NULLPTR));
        labelChordLanguage->setText(QApplication::translate("MainWindow", "Chord Language", Q_NULLPTR));
        comboBoxChordLanguage->clear();
        comboBoxChordLanguage->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "English", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Fran\303\247ais", Q_NULLPTR)
        );
        checkBoxLyricsMode->setText(QApplication::translate("MainWindow", "Lyrics and chords mode book", Q_NULLPTR));
        checkBoxChordMode->setText(QApplication::translate("MainWindow", "Chords only mode book", Q_NULLPTR));
        checkBoxTextMode->setText(QApplication::translate("MainWindow", "Text only mode book", Q_NULLPTR));
        checkBoxMemoryMode->setText(QApplication::translate("MainWindow", "Memory mode book", Q_NULLPTR));
        labelWatermark->setText(QApplication::translate("MainWindow", "Watermark", Q_NULLPTR));
        labelProjectName->setText(QApplication::translate("MainWindow", "Project name :", Q_NULLPTR));
        labelNameProjectName->setText(QString());
        labelDirProject->setText(QApplication::translate("MainWindow", "Project directory :", Q_NULLPTR));
        labelNameDirProject->setText(QString());
        pushButtonMakePDF->setText(QApplication::translate("MainWindow", "Make PDF", Q_NULLPTR));
        pushButtonMakeAndShowPDF->setText(QApplication::translate("MainWindow", "Make  and show PDF ", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(General), QApplication::translate("MainWindow", "General", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(LyricsMode), QApplication::translate("MainWindow", "Lyrics mode", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(ChordMode), QApplication::translate("MainWindow", "Chord mode", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(TextMode), QApplication::translate("MainWindow", "Text mode", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(MemoryMode), QApplication::translate("MainWindow", "Memory mode", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        toolButtonCT->setToolTip(QApplication::translate("MainWindow", "Cover Title", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        toolButtonCT->setText(QApplication::translate("MainWindow", "ct", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        toolButtonCS->setToolTip(QApplication::translate("MainWindow", "Cover Subtitle", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        toolButtonCS->setText(QApplication::translate("MainWindow", "cs", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        toolButtonT->setToolTip(QApplication::translate("MainWindow", "Song Title", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        toolButtonT->setText(QApplication::translate("MainWindow", "t", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        toolButtonST->setToolTip(QApplication::translate("MainWindow", "Song Sub Titile", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        toolButtonST->setText(QApplication::translate("MainWindow", "st", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        toolButtonCol->setToolTip(QApplication::translate("MainWindow", "Column number for this song", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        toolButtonCol->setText(QApplication::translate("MainWindow", "c:", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        toolButtonCB->setToolTip(QApplication::translate("MainWindow", "Column break", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        toolButtonCB->setText(QApplication::translate("MainWindow", "cb", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        toolButtonCompress->setToolTip(QApplication::translate("MainWindow", "Compression until end of song", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        toolButtonCompress->setText(QApplication::translate("MainWindow", "c", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        toolButtonSOC->setToolTip(QApplication::translate("MainWindow", "Start of chorus", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        toolButtonSOC->setText(QApplication::translate("MainWindow", "soc", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        toolButtonEOC->setToolTip(QApplication::translate("MainWindow", "End of chorus", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        toolButtonEOC->setText(QApplication::translate("MainWindow", "eoc", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        toolButtonREF->setToolTip(QApplication::translate("MainWindow", "Refrain", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        toolButtonREF->setText(QApplication::translate("MainWindow", "ref", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        checkBoxLongShort->setToolTip(QApplication::translate("MainWindow", "Long/Short notation in text", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        checkBoxLongShort->setText(QApplication::translate("MainWindow", "Long syntax", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(Editor2), QApplication::translate("MainWindow", "Editor", Q_NULLPTR));
        menuFile->setTitle(QApplication::translate("MainWindow", "F&ile", Q_NULLPTR));
        menuTools->setTitle(QApplication::translate("MainWindow", "Too&ls", Q_NULLPTR));
        menuHelp->setTitle(QApplication::translate("MainWindow", "&Help", Q_NULLPTR));
        menuEdition->setTitle(QApplication::translate("MainWindow", "Edition", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
