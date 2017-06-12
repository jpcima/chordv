# Compilation installation

## Podofo library installation 9.8

### Linux Debian

  - In a shell script

~~~bash
sudo apt-get install libpodofo-dev
~~~
  - In the pro file add

~~~qmake
LIBS +=
INCLUDEPATH +=
DEPENDPATH +=
~~~

## Podofo compilation from sources

### Install dependancies

~~~bash
    sudo apt-get install -y subversion cmake
    sudo apt-get install -y libz-dev libfreetype6-dev libfontconfig1-dev libjpeg-dev libssl-dev libcrypto++9v5-dev libtiff5-dev
    sudo apt-get install -y libcppunit-dev liblua50-dev libidn11-dev lua5.1-dev
~~~

### Compilation

~~~
    svn co http://svn.code.sf.net/p/podofo/code/podofo/trunk podofo
    cd podofo
    mkdir podofo-build
    cd podofo-build
    cmake ../podofo
    make
    su
    make install
~~~

### add in pro file

~~~
    LIBS += -L/usr/local/lib -lpodofo -lz -lfreetype -lfontconfig -lidn -ljpeg -lcrypto -lssl
    INCLUDEPATH += /usr/local/include
    DEPENDPATH += /usr/local/include
~~~

## Documentation generation

  - The documentation is generated in HTML format with pandoc

  - You need ot install pandoc by :


~~~bash
sudo apt-get install pandoc highlight
~~~

- To make documentation pdf you need to install xetex

~~~
sudo apt-get install texlive-xetex
~~~


