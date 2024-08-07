#!/bin/sh

g++ -c -fpic libcpp.cpp -o libcpp.o
g++ -shared -Wl,-soname,libcpp.so.1 -o libcpp.so.1.0 libcpp.o
gcc -o main main.c -L. -lcpp -Wl,-rpath=.