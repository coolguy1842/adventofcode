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

input=`aocd $1 2025`
if [[ $? == 1 ]]; then
    input=""
fi

input="${input//\\/\\\\}"
input="${input//\//\\/}"
input="${input//&/\\&}"
input="${input//$'\n'/\\n}"

path=$(realpath $(dirname $(realpath $0))/..)
sed -E "s/\(INPUT\)/\($input\)/" $path/DayTemplate/Input.hpp > $path/include/Input/Day$(printf "%02d" $1).hpp