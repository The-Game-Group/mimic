#! /usr/bin/env bash

BUILD_MODE="Debug"
if [ -z ${BUILD_RELEASE} ]; then BUILD_MODE="Release"; fi

echo "Building with: ${CXX:-system default C++ compiler}"
echo "To change, run as CXX=<compiler> $0 $@"

cmake --build build/ --config $BUILD_MODE
