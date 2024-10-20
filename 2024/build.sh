#!/bin/bash

path=$(realpath $(dirname $PWD/$0))
dayPath=$path/${1%/}

if [ ! -e $dayPath ]; then
    echo Invalid Path
    exit
elif [ ! -e $dayPath/CMakeLists.txt ]; then
    echo Invalid Path
    exit
fi

init_build() {
    restore_dir=$PWD

    echo Initializing build dir
    
    mkdir $path/build
    cd $path/build

    cmake $dayPath
    cd $restore_dir
}

if [ ! -e $path/build ]; then
    init_build
elif [[ $(cat ./build/Makefile | grep "CMAKE_SOURCE_DIR =" | sed -n 's/.* = \(\/.*\)/\1/p') != $dayPath ]]; then
    echo Reloading build dir
    rm -rf $path/build

    init_build
fi

dir=$PWD
cd build
make -j $(lscpu | grep -E '^CPU\(s\):' | sed -n 's/.*\s\([0-9]*\).*/\1/p')

cd $dir