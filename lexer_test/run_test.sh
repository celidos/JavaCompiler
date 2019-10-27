#!/bin/bash
cd ..
cd src
echo "Running FLEX..."
flex lexer.l
mkdir -p ../target
g++ -std=c++17 -o ../target/lexer main.cpp lex.yy.cc mini_scanner.h mini_scanner.cpp
cd ..
cd lexer_test
mkdir -p ./target
g++ -std=c++17 -o ./target/tester main.cpp
mkdir ./answer
for file in samples/*
do
  filename=$(basename -- "$file")
  extension="${filename##*.}"
  filename="${filename%.*}"
  cat "${file}" | ../target/lexer > ./answer/"$filename"
  ./target/tester ./correct_answer/"$filename" ./answer/"$filename"
done