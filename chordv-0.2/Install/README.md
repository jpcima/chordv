How make installers
===================



Linux Debian 
------------

- Installation for debian 
- debhelper and dh-make must be installed

~~~bash
sudo apt-get install debhelper dh-make
~~~


- The Debian rep contains incormations ( control, changes, etc).
- on each distribution you have to maintains this files


- The  debian directory is made by :

~~~bash
DEBFULLNAME="Gilles Maire"
dh_make -p chordv-0.2 -e gilles@gillesmaire.com -c gpl3 -s -y -n
~~~

- The *.ex  file unused has been deleted et the two files chordv.conf and chordv.desktop has been created

- La modification du fichier changelog peut se faire au moyen de la commande 

~~~bash
dch -v 3.0
~~~

- Enfin la commande suivante génère les fichiers source et binaires dans au répertoire au dessus du répertoire des sources ( qdictionnaire-3.0)


~~~bash
dpkg-buildpackage -uc -us
~~~

Machine de développement
~~~~~~~~~~~~~~~~~~~~~~~~

- Installer une debian 7
- dans le fichier  `/etc/apt/sources.list` ajouter 


~~~
deb http://ftp.debian.org/debian wheezy-backports main
~~~
- faire apt-get upgrade	
- Installer le sdk et git par 

~~~bash
apt-get install qt5-default git
~~~

- installer les sources par 

~~~bash
git clone https://git.code.sf.net/p/dicorime/qdicorime dicorime-qdicorime
~~~

Paquets rpm
-----------


MacosOSX
--------

- Aller dans install et lancher ./makedistribmacosx


PC
---

- Pour cloner les sources, prendre gitbash

~~~bash
cd Desktop
git clone https://git.code.sf.net/dicorime/qdicorime qdictionnaire
~~~



- Deux fichiers sont présents dans le répertoire install :
    - Dicorime.MSVC.icss : fichier pour fabriquer l'installeur inno setup avec le Qt compilé avec Microsoft Visual Studio
    - Dicorime.MINGW.icss : gichier pour fabriquer l'installeur inno setup avec Qt compilé avec le comilateur Min GW
-


