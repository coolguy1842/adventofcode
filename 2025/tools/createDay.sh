#!/usr/bin/env sh

if [[ -z $1 ]]; then
    echo Day must be specified
    exit
fi

regex='^[0-9]+$'
if ! [[ $1 =~ $regex ]] ; then
   echo Day must be a number
   exit
fi

path=`realpath $(dirname $(realpath $0))/..`

fileNumber=`printf "%02d" $1`
if [[ ! -f $path/src/Days/Day$fileNumber.hpp ]]; then
    sed -e "s/N/$1/" $path/DayTemplate/Day.hpp > $path/include/Days/Day$fileNumber.hpp
fi

if [[ ! -f $path/src/Days/Day$fileNumber.cpp ]]; then
    sed -e "s/N:/$1:/" -e "s/N.hpp/$fileNumber.hpp/" $path/DayTemplate/Day.cpp > $path/src/Days/Day$fileNumber.cpp
fi

if [[ ! -f $path/include/Input/Day$fileNumber.hpp ]]; then
    $path/tools/createInput.sh $1
fi
