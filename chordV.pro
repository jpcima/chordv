#-------------------------------------------------
#
# Project created by QtCreator 2016-03-02T18:06:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = chordIII
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
    lineedittest.cpp

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
    lineedittest.h

FORMS    += mainwindow.ui \
    formconfig.ui \
    fontchooser.ui
