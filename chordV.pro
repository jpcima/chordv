#-------------------------------------------------
#
# Project created by QtCreator 2016-03-02T18:06:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = chordV
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    util.cpp \
    formconfig.cpp \
    lyricsconfig.cpp \
    chordconfig.cpp \
    textconfig.cpp \
    fontchooser.cpp \
    fontbutton.cpp \
    fontdialog.cpp \
    colorbutton.cpp \
    lineedittest.cpp \
    logmessages.cpp \
    editorhighlighter.cpp \
    imagebutton.cpp \
    examplelabel.cpp \
    pagesize.cpp \
    processor.cpp \
    dialogabout.cpp \
    memoryconfig.cpp \
    spinboxunit.cpp \
    dialogconfiguration.cpp \
    settings.cpp \
    processortext.cpp

HEADERS  += mainwindow.h \
    util.h \
    formconfig.h \
    lyricsconfig.h \
    chordconfig.h \
    textconfig.h \
    fontchooser.h \
    fontbutton.h \
    fontdialog.h \
    colorbutton.h \
    lineedittest.h \
    logmessages.h \
    editorhighlighter.h \
    imagebutton.h \
    examplelabel.h \
    pagesize.h \
    processor.h \
    dialogabout.h \
    memoryconfig.h \
    spinboxunit.h \
    dialogconfiguration.h \
    settings.h \
    processortext.h \
    const.h

FORMS    += mainwindow.ui \
    formconfig.ui \
    fontchooser.ui \
    dialogabout.ui \
    dialogconfiguration.ui

LIBS += -L/usr/local/lib -lpodofo  -lfreetype -lfontconfig -lidn -ljpeg -ltiff -lz  -lm -lpng -lcrypto -lssl
INCLUDEPATH += /usr/local/include
DEPENDPATH += /usr/local/include


TRANSLATIONS=chordV_fr_FR.ts

DISTFILES += \
    Example/deuxdisques.png \
    Example/Chansons.cho3 \
    Example/Chansons.chop \
	Docs/txt/Documentation_en.txt \
	Docs/txt/Documentation_fr.txt \
	Docs/txt/Compilation.txt \
	Docs/txt/Todo.txt \
	Docs/txt/Makefile \
    Docs/txt/index.txt \
    Test/data/Makefile

RESOURCES += \
    resources.qrc


DESTDIR = ../bin
OBJECTS_DIR = build/obj
MOC_DIR = build/moc
RCC_DIR = build/rcc
UI_DIR = build/ui
