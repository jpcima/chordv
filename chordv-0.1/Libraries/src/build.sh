#!/bin/sh

mkdir -p build
cd build 
cmake -G "Unix Makefiles" ../podofo-0.9.5 \
	-DPODOFO_BUILD_SHARED:BOOL=TRUE \
	-DPODOFO_BUILD_STATIC:BOOL=TRUE
make
mkdir -p ../lib
cp src/libpodofo.a ../lib
cp src/libpodofo.so ../lib

