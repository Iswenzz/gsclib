#!/bin/sh

conan remote add iswenzz-conan https://iswenzz.jfrog.io/artifactory/api/conan/iswenzz-conan

cd ..
mkdir build -p && cd build
conan install .. --build --profile ../.conan/linux.conf
cmake ..
