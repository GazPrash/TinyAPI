#!/bin/bash

mkdir -p build
cd build
cmake .. -DCMAKE_EXPORT_COMPILE_COMMANDS=OFF
make
cd ..
g++ example/example_app1.cpp -o example_app1 -Iinclude -L build/ -lTinyApi
