        #-------------------------------------------------
    #
    # Project created by QtCreator 2016-03-02T18:06:45
    #
    #-------------------------------------------------

    QT       += core gui sql widgets
    TEMPLATE = app

    linux{
    DEFINES += "DATADIR=\\\"/usr/share/chordV\\\""
    DEFINES += "BINDIR=\\\"/usr/bin\\\""
    system(/bin/echo -e \\\x23ifndef VERSION_H >include/version.h)
    system(/bin/echo -e \\\x23define VERSION_H>>include/version.h)
    system(/bin/echo -e \\\x23define VERSION \\\"$$VERSION\\\">>include/version.h)
    system(/bin/echo -e \\\x23define FULLVERSION \\\"$$FULLVERSION\\\" >>include/version.h)
    system(/bin/echo -e \\\x23define DATEUS \\\"$$DATEUS\\\" >> include/version.h)
    system(/bin/echo -e \\\x23endif // VERSION_H >>include/version.h)
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
    src/dialogtranspose.cpp

    HEADERS  += include/mainwindow.h \
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
        include/textedit.h \
        include/dialogdocumentation.h \
        include/formeditor.h \
        include/dialogtwolinestochordpro.h \
        include/dialogchangechordname.h \
        include/forminputoutputchord.h \
        include/chordutil.h \
    include/normalizelist.h \
    include/dialogtranspose.h

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
        ui/dialogbar.ui \
        ui/dialogdocumentation.ui \
        ui/formeditor.ui \
        ui/dialogtwolinestochordpro.ui \
        ui/forminputoutputchord.ui \
        ui/dialogchangechordname.ui \
    ui/dialogtranspose.ui

 #    LIBS += -LLibraries/lib -L/usr/lib -Wl,-Bstatic -lpodofo -Wl,-Bdynamic -lfreetype -lfontconfig -lidn -ljpeg -ltiff -lz  -lm -lpng -lcrypto -lssl
    LIBS += -LLibraries/lib -L/usr/lib -Bdynamic -lpodofo -lfreetype -lfontconfig -lidn -ljpeg -ltiff -lz  -lm -lpng -lcrypto -lssl
    INCLUDEPATH = Libraries/include  ./include


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
        Docs/img/fr/editor.png

    RESOURCES += \
        Resources/resources.qrc


    DESTDIR = bin
    OBJECTS_DIR = build/obj
    MOC_DIR = build/moc
    RCC_DIR = build/rcc
    UI_DIR = build/ui

