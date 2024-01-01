#!/bin/bash
if test -f ./$1.c; then
clang ./$1.c -o ./build/$1.o
else
clang++ ./$1.cpp -o ./build/$1.o
fi
./build/$1.o
kitten icat out/output.ppm