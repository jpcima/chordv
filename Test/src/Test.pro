QT += core gui widgets

TARGET = Test
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    test.cpp \
    application.cpp

DESTDIR = ../bin
OBJECTS_DIR = build/obj
MOC_DIR = build/moc
RCC_DIR = build/rcc
UI_DIR = build/ui

HEADERS += \
    test.h \
    application.h

DISTFILES += \
	../Docs/txt/TestPresentation-en.txt \
    ../Docs/txt/Makefile
