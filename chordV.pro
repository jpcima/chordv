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
    chordsbook.cpp \
    lyricsbook.cpp \
    textbook.cpp \
    dialogabout.cpp \
    memoryconfig.cpp \
    spinboxunit.cpp \
    dialogconfiguration.cpp \
    settings.cpp

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
    chordsbook.h \
    lyricsbook.h \
    textbook.h \
    dialogabout.h \
    memoryconfig.h \
    spinboxunit.h \
    dialogconfiguration.h \
    settings.h

FORMS    += mainwindow.ui \
    formconfig.ui \
    fontchooser.ui \
    dialogabout.ui \
    dialogconfiguration.ui

LIBS += -L/usr/lib/ -lpodofo
INCLUDEPATH += /usr/include
DEPENDPATH += /usr/include

TRANSLATIONS=chordV_fr_FR.ts

DISTFILES += \
    Docs/Todo.md \
    Docs/Compilation.md
