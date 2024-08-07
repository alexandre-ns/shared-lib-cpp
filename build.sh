#!/bin/sh

#compiles libcpp.cpp file -fpic (position independent code, PIC) and share lib
g++ -fPIC -shared -o libcpp.so libcpp.cpp

#compile the file main.c and link the library
gcc -o main main.c -L. -lcpp

#includ dir lib
export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH