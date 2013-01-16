#!/bin/bash

build_path="build/vc10"
rm -rf $build_path
echo "Removed $build_path"
mkdir $build_path
echo "Created $build_path"
cd $build_path

#-DCMAKE_BUILD_TYPE=RELEASE \
cmake \
  -DCMAKE_INSTALL_PREFIX=../.. \
  -DTHX_INCLUDE_PATH=D:/GitHub/thx/include \
  -DGTEST_INCLUDE_PATH=D:/code/gtest-1.6.0/include \
  -DGTEST_LIB_PATH=D:/code/gtest-1.6.0/msvc/gtest \
  ../.. \
  -G "Visual Studio 10"


