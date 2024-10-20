#!/bin/bash

path=$(realpath $(dirname $PWD/$0))
dayPath=$path/${1%/}

if [ -e $dayPath ]; then
    echo Path Exists
    exit
fi

cp -r DayTemplate $dayPath
touch $dayPath/input.txt