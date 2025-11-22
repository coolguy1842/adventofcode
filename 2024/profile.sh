#!/bin/bash

source "$(realpath $(dirname $0))/script_base.sh"
source "$(realpath $(dirname $0))/build.sh"

if [[ $_ != $0 ]]; then
    path=$(get_path $0)
    buildType=$(validate_build_type $2)

    day=$1
    
    run_build $path $buildType $day

    restore_dir=$PWD
    cd $path/build/days/Day$day
    
    perf record -g ./day ${@:3}
    perf report --sort comm,dso,symbol

    cd $restore_dir
fi