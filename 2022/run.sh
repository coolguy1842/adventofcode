#!/bin/bash

rm main

g++ -std=c++20 -O3 -Wall -o main main.cpp -I days -I include
./main