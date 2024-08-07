#!/bin/sh

#compiles libcpp.cpp file -fpic (position independent code, PIC)
g++ -c -fpic libcpp.cpp -o libcpp.o

#shared lib
g++ -shared -Wl,-soname,libcpp.so.1 -o libcpp.so.1.0 libcpp.o

#compile the file main.c and link the library
gcc -o main main.c -L. -lcpp -Wl,-rpath=.