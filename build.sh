#!/bin/bash

if [ ! -d "build" ]; then
  # 文件夹不存在，创建文件夹
  mkdir -p "build"
fi

cd build/
cmake ..
make