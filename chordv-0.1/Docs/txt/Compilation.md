# Compilation installation

## Podofo compilation from sources

### Install dependancies

~~~bash
    sudo apt-get install -y subversion cmake
    sudo apt-get install -y libz-dev libfreetype6-dev libfontconfig1-dev libjpeg-dev libssl-dev libcrypto++9v5-dev libtiff5-dev
    sudo apt-get install -y libcppunit-dev liblua50-dev libidn11-dev lua5.1-dev
~~~

### Compilation

~~~
    cd Libraries/src
    ./build.sh
~~~

### Notes on pro file

-
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


