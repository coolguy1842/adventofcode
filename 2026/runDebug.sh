#!/usr/bin/env sh

CC=clang CC_LD=lld CXX=clang++ meson setup build --buildtype=debug --reconfigure
cd build

meson compile
./aoc $@

cd ..