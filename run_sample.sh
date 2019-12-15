#!/bin/bash
#!/usr/bin/env bash

if [ $# -ne 2 ]
  then
    echo "Usage: ./run_ast_graphviz.sh [java code filename] [output filenames without extension]";
    exit 0
fi

pwd
# sh make_all.sh



INPUT_FILENAME=$1
OUTPUT_AST_GRAPH_IMG_FILENAME=output/ast_graphs/$2.svg
OUTPUT_AST_GRAPH_DOT_FILENAME=output/ast_graphs/$2.dot
OUTPUT_IRT_GRAPH_IMG_FILENAME=output/irt_graphs/$2.svg
OUTPUT_IRT_GRAPH_DOT_FILENAME=output/irt_graphs/$2.dot

echo "[run] Starting program..."
./build/javacompiler $1 ${OUTPUT_AST_GRAPH_DOT_FILENAME} ${OUTPUT_IRT_GRAPH_DOT_FILENAME}

echo "[run] Running AST graphviz..."
dot -Tsvg ${OUTPUT_AST_GRAPH_DOT_FILENAME} -o ${OUTPUT_AST_GRAPH_IMG_FILENAME}

echo "[run] Running IRT graphviz..."
dot -Tsvg ${OUTPUT_IRT_GRAPH_DOT_FILENAME} -o ${OUTPUT_IRT_GRAPH_IMG_FILENAME}
