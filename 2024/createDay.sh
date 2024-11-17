#!/bin/bash
source "$(realpath $(dirname $0))/script_base.sh"

day=$1
path=$(get_path $0)

dayPath=$(get_day_path $path $day)
if [ -e $dayPath ]; then
    echo Path Exists
    exit
fi

cp -r $path/DayTemplate $dayPath
touch $dayPath/input.txt
