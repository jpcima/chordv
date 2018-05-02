#!/bin/sh

PODOFO=podofo-0.9.3

tar xzvf ${PODOFO}.tar.gz
mkdir -p build
cd build 
cmake -G "Unix Makefiles" ../${PODOFO} \
	-DPODOFO_BUILD_SHARED:BOOL=TRUE \
	-DPODOFO_BUILD_STATIC:BOOL=TRUE
make
mkdir -p ../../lib
cp src/libpodofo.a ../../lib
cp src/libpodofo.so ../../lib
cd ..
rm -rf ../include
mkdir -p ../include
mv ${PODOFO}/src ../include
mv ../include/src ../include/podofo
cp build/podofo_config.h ../include/
rm -rf build 
rm -rf ${PODOFO}

