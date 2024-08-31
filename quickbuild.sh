#!/bin/bash

mkdir -p build
cd build
cmake .. -DCMAKE_EXPORT_COMPILE_COMMANDS=OFF
make
cd ..
g++ example_testing.cpp -o testing_app -Iinclude -L build/ -lTinyApi
