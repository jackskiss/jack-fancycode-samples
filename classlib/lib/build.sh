#!/bin/bash
g++ -c -fPIC -I../inc iflib.cpp -o iflib.o
g++ -shared -o libif.so iflib.o

