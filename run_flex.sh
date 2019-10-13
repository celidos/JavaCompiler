echo "Running FLEX..."
cd src
flex lexer.l
mkdir -p ../target
g++ -std=c++17 -o ../target/lexer main.cpp lex.yy.cc mini_scanner.h mini_scanner.cpp
cd ..
cat $1 | target/lexer
