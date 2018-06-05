#!/bin/sh
pandoc --help >/dev/null 2>&1 || (echo "Please install pandoc command" && exit 1)
xetex --help >/dev/null  2>&1 || (echo "Please install textlive-xetex package" && exit 1 )
highlight --help>/dev/null 2>&1 || (echo "Please install highlight package" && exit 1)
dpkg-buildpackage --help >/dev/null 2>&1 || (echo "Please install dpkg-dev" && exit 1)
lrelease translations/fr.ts 
cd Docs
make
cd ..
dpkg-buildpackage -uc -us


