# Compilation installation

## Get chordV 


~~~bash
sudo apt-get install git 
git clone https://git.code.sf.net/p/chordv/code chordv-code
~~~

## Podofo compilation from sources

### Install dependancies on Ubuntu 1.04

~~~bash
    sudo apt-get install -y subversion cmake
    sudo apt-get install -y libz-dev libfreetype6-dev libfontconfig1-dev libjpeg-dev libssl-dev libcrypto++9v5-dev libtiff5-dev
    sudo apt-get install -y libcppunit-dev liblua50-dev libidn11-dev lua5.1-dev
~~~

### Install dependancies on Ubuntu 16.04 LTS

~~~bash
    sudo apt-get install -y subversion cmake
    sudo apt-get install -y libz-dev libfreetype6-dev libfontconfig1-dev libjpeg-dev libssl-dev libcrypto++-dev libtiff5-dev
    sudo apt-get install -y libcppunit-dev liblua50-dev libidn11-dev lua5.1-dev
    sudo apt-get install qtmultimedia5-dev libqt5multimediawidgets5 libqt5multimedia5-plugins libqt5multimedia5
~~~

### Compile documentation 

~~~bash 
sudo apt-get install pandoc highlight texlive-xetex
cd Docs
make 
~~~

### Install /usr/share/chordV dir

~~~bash
sudo ./install
~~~

### Librairy Podofo compilation

~~~
    cd Libraries/src
    ./build.sh
~~~

### Chord V compilation 

~~~bash
cd ../..
qmake
make
~~~

## Install Doxygen

~~~bash
sudo apt install doxygen doxygen-gui graphviz
~~~
