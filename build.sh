#!/bin/bash

rm -rf build
mkdir -p build
cd build
cmake -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_LINKER=lld ..
make -j12
