#!/bin/bash
g++ -c src/LUT.cpp
g++ -c test_harness.cpp
g++ -lm LUT.o test_harness.o -o test_harness.exe