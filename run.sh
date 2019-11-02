#!/usr/bin/env bash

echo "[run] Cleaning..."
rm -rf ./build

echo "[run] Creating build directory..."
mkdir build
cd build

echo "[run] Starting cmake..."
cmake ..

echo "[run] Starting make..."
pwd
make

# echo "Running test.java ... "
# ./my_wc test/test.java
# echo "Done!"
