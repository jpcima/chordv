#-------------------------------------------------
#
# Project created by QtCreator 2016-03-02T18:06:45
#
#-------------------------------------------------

QT       += core gui sql widgets
TARGET = chordV
TEMPLATE = app

linux{
target.path = /usr/bin
INSTALLS += target
VERSION=$$system(git tag -l | head -1)
FULLVERSION=$$system(git log -1 --format=format:%H)
DATEUS=$$system(date +%Y/%m/%d)
system(/bin/echo -e \\\x23ifndef VERSION_H >include/version.h)
system(/bin/echo -e \\\x23define VERSION_H>>include/version.h)
system(/bin/echo -e \\\x23define VERSION \\\"$$VERSION\\\">>include/version.h)
system(/bin/echo -e \\\x23define FULLVERSION \\\"$$FULLVERSION\\\" >>include/version.h)
system(/bin/echo -e \\\x23define DATEUS \\\"$$DATEUS\\\" >> include/version.h)
system(/bin/echo -e \\\x23endif // VERSION_H >>include/version.h)
}

SOURCES += src/main.cpp\
        src/mainwindow.cpp \
    src/util.cpp \
    src/formconfig.cpp \
    src/lyricsconfig.cpp \
    src/chordconfig.cpp \
    src/textconfig.cpp \
    src/fontchooser.cpp \
    src/fontbutton.cpp \
    src/fontdialog.cpp \
    src/colorbutton.cpp \
    src/lineedittest.cpp \
    src/logmessages.cpp \
    src/editorhighlighter.cpp \
    src/imagebutton.cpp \
    src/examplelabel.cpp \
    src/pagesize.cpp \
    src/processor.cpp \
    src/dialogabout.cpp \
    src/memoryconfig.cpp \
    src/spinboxunit.cpp \
    src/dialogconfiguration.cpp \
    src/settings.cpp \
    src/processortext.cpp \
    src/verticalspacing.cpp \
    src/dialogchorddefinition.cpp \
    src/ChordDetector.cpp\
    src/neck.cpp \
    src/dialogsysteminfo.cpp \
    src/chorddiagram.cpp \
    src/dialogchoosegoodchord.cpp \
    src/dialogsearch.cpp \
    src/dialogreplace.cpp \
    src/processorlyrics.cpp \
    src/language.cpp \
    src/chord.cpp \
    src/langnotes.cpp \
    src/pdfviewer.cpp \
    src/dialogbar.cpp \
    src/processorchord.cpp \
    src/textedit.cpp

HEADERS  += include/mainwindow.h \
    include/util.h \
    include/formconfig.h \
    include/lyricsconfig.h \
    include/chordconfig.h \
    include/textconfig.h \
    include/fontchooser.h \
    include/fontbutton.h \
    include/fontdialog.h \
    include/colorbutton.h \
    include/lineedittest.h \
    include/logmessages.h \
    include/editorhighlighter.h \
    include/imagebutton.h \
    include/examplelabel.h \
    include/pagesize.h \
    include/processor.h \
    include/dialogabout.h \
    include/memoryconfig.h \
    include/spinboxunit.h \
    include/dialogconfiguration.h \
    include/settings.h \
    include/processortext.h \
    include/const.h \
    include/verticalspacing.h \
    include/dialogchorddefinition.h \
    include/ChordDetector.h \
    include/neck.h \
    include/dialogsysteminfo.h \
    include/chorddiagram.h \
    include/dialogchoosegoodchord.h \
    include/dialogsearch.h \
    include/dialogreplace.h \
    include/processorlyrics.h \
    include/language.h \
    include/chord.h \
    include/langnotes.h \
    include/pdfviewer.h \
    include/dialogbar.h \
    include/processorchord.h \
    include/textedit.h

FORMS    += ui/mainwindow.ui \
    ui/formconfig.ui \
    ui/fontchooser.ui \
    ui/dialogabout.ui \
    ui/dialogconfiguration.ui \
    ui/dialogchorddefinition.ui \
    ui/dialogsysteminfo.ui \
    ui/dialogchoosegoodchord.ui \
    ui/dialogsearch.ui \
    ui/dialogreplace.ui \
    ui/dialogbar.ui

LIBS += -L/usr/local/lib -L/usr/lib -lpodofo  -lfreetype -lfontconfig -lidn -ljpeg -ltiff -lz  -lm -lpng -lcrypto -lssl
INCLUDEPATH += /usr/local/include ./include
DEPENDPATH += /usr/local/include


TRANSLATIONS=translations/fr.ts

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
    Test/data/Makefile \
    Test/Docs/txt/Makefile \
    Docs/txt/ChoFormat_en.txt \
    Docs/txt/ChoFormat_fr.txt

RESOURCES += \
    Resources/resources.qrc \
    ui/resources.qrc


DESTDIR = bin
OBJECTS_DIR = build/obj
MOC_DIR = build/moc
RCC_DIR = build/rcc
UI_DIR = build/ui
