#! /usr/bin/env bash

BUILD_MODE="Debug"
if [ -z ${BUILD_RELEASE} ]; then BUILD_MODE="Release"; fi

echo "Building with: ${CXX:-system default C++ compiler}"
echo "To change, run as CXX=<compiler> $0 $@"

cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -DCMAKE_BUILD_TYPE=$BUILD_MODE -B build/ -S .
