How make installers
===================


Linux Debian
------------

- Installation for debian 
- debhelper and dh-make must be installed

~~~bash
apt-get install debhelper dh-make
~~~

- Qt must be installed

~~~bash
apt install qtdeclarative-dev qt5-default qtdevtool5-dev-tools
~~~

- LibPodofo must be installed

~~~bash
apt install libpodofo-0.9 libpodofo-dev
~~~

- The Debian rep contains incormations ( control, changes, etc).
- on each distribution you have to maintains this files


- The  debian directory is made by :

~~~bash
DEBFULLNAME="Gilles Maire"
dh_make -p chordv-0.2 -e gilles@gillesmaire.com -c gpl3 -s -y -n
~~~

- The *.ex  file unused has been deleted et the two files chordv.conf and chordv.desktop has been created

- To modify version :

~~~bash
dch -v 3.0
~~~

~~~bash
cd ..
dpkg-buildpackage -uc -us
~~~



