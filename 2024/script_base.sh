#!/bin/bash

# arg is usually $0 (the path to the executable you want)
get_path() {
    executable=$1

    echo "$(realpath $(dirname $executable))"
}

# buildtype
validate_build_type() {
    buildType=$1

    case $buildType in
    Release);; Debug);;
    *)
        if [[ -z $buildType ]]; then
            echo "Debug"

            return
        fi

        echo "Invalid Build Type"
        exit 1

        ;;
    esac

    echo $buildType
}

# base path, day
get_day_path() {
    basePath=$1
    day=$2

    echo "$basePath/days/Day$day"
}


validate_day_path() {
    dayPath=$1

    if [ ! -e $dayPath ]; then
        echo invalid
    elif [ ! -e $dayPath/CMakeLists.txt ]; then
        echo invalid
    else
        echo valid
    fi
}

# path (this function basically does nothing but its for if i change something later)
init_build_path() {
    buildPath=$1
    restoreDir=$PWD

    mkdir $buildPath
    cd $buildPath

    cd $restoreDir
}

# path, buildtype, day
run_cmake() {
    path=$1
    buildType=$2
    day=$3

    cmake $path -B $path/build -DCMAKE_BUILD_TYPE=$buildType -DDAY=$day -G Ninja
    cmake --build $path/build -- -j$(nproc)
}