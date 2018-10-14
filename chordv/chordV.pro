    #-------------------------------------------------
    #
    # Project created by QtCreator 2016-03-02T18:06:45
    #
    #-------------------------------------------------

    QT       += core gui sql widgets multimedia
    TEMPLATE = app

    linux{
    DEFINES += "DATADIR=\\\"/usr/share/chordV\\\""
    DEFINES += "BINDIR=\\\"/usr/bin\\\""
    DATEBUILD=$$system(date +"%Y/%m/%d")
    GIT=$$system(git log -n 1 --format="%H")
    VERSIONWORK=$$system(  git tag | tail -n 1 )
    system(/bin/echo -e \\\x23define VERSIONWORK \\\"$$VERSIONWORK\\\" >src/version.h)
    system(/bin/echo -e \\\x23define DATEBUILD \\\"$$DATEBUILD\\\" >>src/version.h)
    system(/bin/echo -e \\\x23define GIT \\\"$$GIT\\\" >> src/version.h)
    }
    SOURCES += src/main.cpp\
            src/mainwindow.cpp \
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
        src/textedit.cpp \
        src/dialogdocumentation.cpp \
        src/formeditor.cpp \
        src/dialogtwolinestochordpro.cpp \
        src/dialogchangechordname.cpp \
        src/forminputoutputchord.cpp \
        src/chordutil.cpp \
        src/normalizelist.cpp \
        src/dialogtranspose.cpp \
        src/dialognewsong.cpp \
        src/formmemoryinfo.cpp \
        src/dialogprocessmemory.cpp

    HEADERS  += src/mainwindow.h \
        src/formconfig.h \
        src/lyricsconfig.h \
        src/chordconfig.h \
        src/textconfig.h \
        src/fontchooser.h \
        src/fontbutton.h \
        src/fontdialog.h \
        src/colorbutton.h \
        src/lineedittest.h \
        src/logmessages.h \
        src/editorhighlighter.h \
        src/imagebutton.h \
        src/examplelabel.h \
        src/pagesize.h \
        src/processor.h \
        src/dialogabout.h \
        src/memoryconfig.h \
        src/spinboxunit.h \
        src/dialogconfiguration.h \
        src/settings.h \
        src/processortext.h \
        src/const.h \
        src/verticalspacing.h \
        src/dialogchorddefinition.h \
        src/ChordDetector.h \
        src/neck.h \
        src/dialogsysteminfo.h \
        src/chorddiagram.h \
        src/dialogchoosegoodchord.h \
        src/dialogsearch.h \
        src/dialogreplace.h \
        src/processorlyrics.h \
        src/language.h \
        src/chord.h \
        src/langnotes.h \
        src/pdfviewer.h \
        src/dialogbar.h \
        src/processorchord.h \
        src/textedit.h \
        src/dialogdocumentation.h \
        src/formeditor.h \
        src/dialogtwolinestochordpro.h \
        src/dialogchangechordname.h \
        src/forminputoutputchord.h \
        src/chordutil.h \
        src/normalizelist.h \
        src/dialogtranspose.h \
        src/version.h \
        src/dialognewsong.h \
    src/formmemoryinfo.h \
    src/dialogprocessmemory.h

    FORMS    += src/mainwindow.ui \
        src/formconfig.ui \
        src/fontchooser.ui \
        src/dialogabout.ui \
        src/dialogconfiguration.ui \
        src/dialogchorddefinition.ui \
        src/dialogsysteminfo.ui \
        src/dialogchoosegoodchord.ui \
        src/dialogsearch.ui \
        src/dialogreplace.ui \
        src/dialogbar.ui \
        src/dialogdocumentation.ui \
        src/formeditor.ui \
        src/dialogtwolinestochordpro.ui \
        src/forminputoutputchord.ui \
        src/dialogchangechordname.ui \
        src/dialogtranspose.ui \
        src/dialognewsong.ui \
    src/formmemoryinfo.ui \
    src/dialogprocessmemory.ui

 #    LIBS += -LLibraries/lib -L/usr/lib -Wl,-Bstatic -lpodofo -Wl,-Bdynamic -lfreetype -lfontconfig -lidn -ljpeg -ltiff -lz  -lm -lpng -lcrypto -lssl
    LIBS += -Bdynamic -lpodofo -lfreetype -lfontconfig -lidn -ljpeg -ltiff -lz  -lm -lpng -lcrypto -lssl -ljack
    INCLUDEPATH = ./src


    TRANSLATIONS=translations/fr.ts

    DISTFILES += \
        Example/deuxdisques.png \
        Example/Chansons.cho3 \
        Example/Chansons.chop \
        Docs/txt/Documentation_en.txt \
        Docs/txt/Documentation_fr.txt \
        Docs/txt/Compilation.md \
        Docs/txt/Todo.md \
        Docs/txt/Makefile \
        Docs/txt/index.txt \
        Test/data/Makefile \
        Test/Docs/txt/Makefile \
        Docs/txt/ChoFormat_en.txt \
        Docs/txt/ChoFormat_fr.txt \
        Docs/txt/fr/Documentation.md \
        Docs/txt/fr/ChoFormat.txt \
        Docs/txt/en/Documentation.txt \
        Docs/txt/en/ChoFormat.txt \
        Docs/img/fr/menupreferences.png \
        Docs/img/fr/preferencegeneral.png \
        Docs/img/fr/fontselection.png \
        Docs/img/fr/preferencetext.png \
        Docs/img/fr/preferencestextcontent.png \
        Docs/img/fr/editor.png \
    Install/README.md \
    Docs/txt/Compilation.md \
    Docs/txt/Index.md \
    Docs/txt/fr/fr.md \
    Docs/txt/en/en.md

    RESOURCES += \
        Resources/resources.qrc
    DESTDIR = bin


