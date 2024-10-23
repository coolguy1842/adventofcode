#!/bin/bash

path=$(realpath $(dirname $PWD/$0))
day=${1%/}
dayPath=$path/days/Day$day

if [ ! -e $dayPath ]; then
    echo Invalid Path
    exit
elif [ ! -e $dayPath/CMakeLists.txt ]; then
    echo Invalid Path
    exit
fi

./build.sh $1
buildFile=$path/build/days/Day$day/day
if [ ! -e $buildFile ]; then
    echo Failed to build
    exit
fi

# run with sudo for better tracy profiling
sudo $buildFile ${@:2}