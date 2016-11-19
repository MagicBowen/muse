#!/bin/bash

gtest_root_path="/Users/wangbo/codes/googletest"

if [ ! -d ${gtest_root_path} ]; then
   echo "gtest path ${gtest_root_path} is not exist, please install gtest and modify the build.sh..."
   exit 0
fi

if [ ! -d "build" ]; then
    mkdir -p build
fi

cd build

echo "*******************************************************************************"
echo "start to build cmake project..."


cmake -DGTEST_ROOT=${gtest_root_path} ../../code
cmake --build .

if [ $? -ne 0 ]; then
    echo "FAILED!"
    cd ..
    exit 1
fi

echo "*******************************************************************************"
echo "start to run tests..."

./test/test_muse --gtest_color=yes $1 $2

if [ $? -ne 0 ]; then
    echo "FAILED!"
    cd ..
    exit 1
fi

cd ..

echo "*******************************************************************************"
echo "SUCCESS!"