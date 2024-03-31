#! /usr/bin/env bash

BUILD_MODE="Debug"
if [ -z ${BUILD_RELEASE} ]; then BUILD_MODE="Release"; fi

echo "Building with: ${CXX:-system default C++ compiler}"
echo "To change, run as CXX=<compiler> $0 $@"

cmake -DCMAKE_BUILD_TYPE=$BUILD_MODE -B build/ -S .

rc=$?

if [ ${rc} -eq 0 ]; then
	cmake --build build/ --config $BUILD_MODE
else
	echo "CMake failed with code: $rc"
	exit $rc
fi