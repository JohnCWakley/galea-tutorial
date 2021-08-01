#!/bin/bash

./compile.sh

mkdir -p build
cd build

if [[ "$OSTYPE" == "linux-gnu"* ]]; then
    echo "setting up for linux..."
    cmake -DCMAKE_BUILD_TYPE=Debug ..
elif [[ "$OSTYPE" == "darwin"* ]]; then
    echo "setting up for macos..."
elif [[ "$OSTYPE" == "cygwin" ]]; then
    echo "setting up for cygwin..."
elif [[ "$OSTYPE" == "msys" ]]; then
    echo "setting up for msys/mingw..."
    cmake -DCMAKE_BUILD_TYPE=Debug -G "MinGW Makefiles" ..
elif [[ "$OSTYPE" == "win32" ]]; then
    echo "setting up for windows..."
elif [[ "$OSTYPE" == "freebsd"* ]]; then
    echo "setting up for freebsd..."
else
    echo "setting up for unknown..."
fi

echo 
echo build environment is ready...
echo 
echo $ make
echo 
