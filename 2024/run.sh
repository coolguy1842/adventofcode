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

./build.sh $1
if [ ! -e $path/build/day ]; then
    echo Failed to build
    exit
fi

$path/build/day ${@:2}