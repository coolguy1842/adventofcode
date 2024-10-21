#!/bin/bash

path=$(realpath $(dirname $PWD/$0))
day=${1%/}
dayPath=$path/days/Day$day

if [ -e $dayPath ]; then
    echo Path Exists
    exit
fi

cp -r $path/days/DayTemplate $dayPath
touch $dayPath/input.txt