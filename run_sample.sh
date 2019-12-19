#!/bin/bash
#!/usr/bin/env bash

echo "Running sample ... " $1 $2 $3

if [ $# -ne 3 ]
  then
    echo "Usage: ./run_ast_graphviz.sh [java code filename] [output filenames without extension]";
    exit 0
fi

pwd
# sh make_all.sh

INPUT_FILENAME=$1
OUTPUT_AST_GRAPH_IMG_FILENAME=$2.svg
OUTPUT_AST_GRAPH_DOT_FILENAME=$2.dot
OUTPUT_IRT_GRAPH_IMG_FILENAME=$3.svg
OUTPUT_IRT_GRAPH_DOT_FILENAME=$3.dot



echo "[run] Starting program..."
./build/bin/javacompiler ${INPUT_FILENAME} ${OUTPUT_AST_GRAPH_DOT_FILENAME} ${OUTPUT_IRT_GRAPH_DOT_FILENAME}

status=$?
if [ "$status" == "0" ]; then
    if [ ! -f "$OUTPUT_AST_GRAPH_DOT_FILENAME" ]; then
      touch "$OUTPUT_AST_GRAPH_DOT_FILENAME"
    fi

    if [ ! -f "$OUTPUT_IRT_GRAPH_DOT_FILENAME" ]; then
      touch "$OUTPUT_IRT_GRAPH_DOT_FILENAME"
    fi
    
    echo "[run] Running AST graphviz..."
    dot -Tsvg ${OUTPUT_AST_GRAPH_DOT_FILENAME} -o ${OUTPUT_AST_GRAPH_IMG_FILENAME}
    echo "[run] Running IRT graphviz..."
    dot -Tsvg ${OUTPUT_IRT_GRAPH_DOT_FILENAME} -o ${OUTPUT_IRT_GRAPH_IMG_FILENAME}
else
    echo "Skipping graphvis"
    exit -1
fi
