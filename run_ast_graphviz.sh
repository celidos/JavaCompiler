#!/bin/bash
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

echo "[run] Starting Graphviz..."
rm -rf ../output
mkdir ../output
touch ../output/$2
touch ../output/$3

./javacompiler ../$1 ../output/$2
dot -Tsvg ../output/$2 -o ../output/$3
