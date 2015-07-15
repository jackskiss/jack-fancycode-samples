#!/bin/bash

g++ -Isrc -Itest -I/usr/local/include test/testmain.cpp test/calculator_test.cpp -o testexec -lgtest -lgtest_main -lpthread
