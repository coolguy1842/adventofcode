#!/bin/bash

source "$(realpath $(dirname $0))/script_base.sh"

run_build() {
    path=$1
    buildType=$2
    day=$3

    dayPath="$(get_day_path $path $day)"
    if [[ $(validate_day_path $dayPath) == "invalid" ]]; then
        echo "Invalid Path"
        exit 1
    fi

    if [ ! -e $path/build ]; then
        init_build_path $path/build
    fi
        
    run_cmake $path $buildType $day
}

if [[ "${BASH_SOURCE[0]}" == "${0}" ]]; then
    path=$(get_path $0)
    buildType=$(validate_build_type $2)

    day=$1
    
    run_build $path $buildType $day
fi