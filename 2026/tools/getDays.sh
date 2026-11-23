#!/usr/bin/env sh

find $1/src/Days -name Day*.cpp | sed -nE 's/^\/.+\/Day([0-9]+).cpp$/\1/p'