#!/bin/bash
# конвертирует текстовое представление графа в графическое
# graphviz.sh out.dot output.svg
cmake .
make
./GraphvizWarmup $1
dot -Tsvg $1 -o $2
