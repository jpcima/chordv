# Compilation installation

## Podofo library installation 9.8

### Linux Debian


- In a shell script

~~~bash
sudo apt-get install libpodofo-dev
~~~
- In the pro file add

~~~
LIBS +=
INCLUDEPATH +=
DEPENDPATH +=
~~~


### Podofo compilation from sources

### Install dependancies

~~~bash
sudo apt-get install -y subversion cmake
sudo apt-get install -y libz-dev libfreetype6-dev libfontconfig-dev libjpeg-dev libssl-dev libcrypto++9v5-dev libtiff-dev
sudo apt-get instal -u libcppunit-dev liblua50-dev libidn11-dev
~~~

### Compilation


~~~bash
svn co http://svn.code.sf.net/p/podofo/code/podofo/trunk podofo
mkdir podofo-build
cd podofo-build
cmake ../podofo
make
su
make install
~~~~

### add in pro file

~~~ini
LIBS += -L/usr/local/lib -lpodofo -lz -lfreetype -lfontconfig -lidn -ljpeg -lcrypto -lssl
INCLUDEPATH += /usr/local/include
DEPENDPATH += /usr/local/include
~~~
