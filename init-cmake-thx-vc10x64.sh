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
  ../.. \
  -G "Visual Studio 10 Win64"


