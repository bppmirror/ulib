#!/bin/sh
#
# Build this example, which does not use that standard IDF app template. See README.md for
# more information about the build and how to run this example on the target once built.

BASEDIR=$(dirname "$0")
CURRDIR=$(dirname 'pwd')

if [ "$1" = "esp32" ] ; then
    mkdir -p ${BASEDIR}/build/esp
    cd ${BASEDIR}/build/esp
    cmake ../.. -DCMAKE_TOOLCHAIN_FILE=$IDF_PATH/tools/cmake/toolchain-esp32.cmake -DBPP_PLATFORM=esp32 
ret=$?
if [ $ret -ne 0 ]; then
    echo "Error while cmake call"
    exit $ret
fi
else
    mkdir -p ${BASEDIR}/build/pc
    cd ${BASEDIR}/build/pc
    cmake ../..
fi

cmake --build .
ret=$?
if [ $ret -ne 0 ]; then
    echo "Build error"
    exit $ret
fi

cd ${CURDIR}
