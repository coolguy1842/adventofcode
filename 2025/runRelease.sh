#!/usr/bin/env sh

CC=clang CC_LD=lld CXX=clang++ meson setup build --buildtype=release --reconfigure
cd build

meson compile
./aoc $@

cd ..