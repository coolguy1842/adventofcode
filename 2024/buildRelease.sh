#!/bin/bash

path=$(realpath $(dirname $PWD/$0))
day=${1%/}
dayPath=$path/days/Day${1%/}

if [ ! -e $dayPath ]; then
    echo Invalid Path
    exit
elif [ ! -e $dayPath/CMakeLists.txt ]; then
    echo Invalid Path
    exit
fi

run_cmake() {
    cmake $path -DCMAKE_BUILD_TYPE=Release -DDAY=$day
}

init_build() {
    restore_dir=$PWD

    echo Initializing build dir
    
    mkdir $path/build
    cd $path/build

    run_cmake
    cd $restore_dir
}

if [ ! -e $path/build ]; then
    init_build
fi

dir=$PWD
cd build

run_cmake
make -j $(lscpu | grep -E '^CPU\(s\):' | sed -n 's/.*\s\([0-9]*\).*/\1/p')

cd $dir