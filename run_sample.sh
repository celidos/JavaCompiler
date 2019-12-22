#!/bin/bash
#!/usr/bin/env bash

if ! [[ $# -eq 3 || $# -eq 4 ]]
  then
    echo "Usage: ./run_sample.sh [java code filename] [output .dot filename for ast without extension]" \
        "[output .dot filename for irt without extension] [[ no_mem_check | mem_check ]]";
    exit 0
fi

echo "[run] Running sample" "$1" "$2" "$3" "$4" "..."
pwd

INPUT_FILENAME=$1
OUTPUT_AST_GRAPH_IMG_FILENAME="$2.svg"
OUTPUT_AST_GRAPH_DOT_FILENAME="$2.dot"
OUTPUT_IRT_GRAPH_IMG_FILENAME="$3.svg"
OUTPUT_IRT_GRAPH_DOT_FILENAME="$3.dot"
MEMORY_CHECK=${4:-no_mem_check}
VALGRIND_MEMCHECK_FAIL_CODE=100

echo "[run] Starting program..."    
if [ ! -f "$OUTPUT_AST_GRAPH_DOT_FILENAME" ]; then
    touch "$OUTPUT_AST_GRAPH_DOT_FILENAME"
fi

if [ ! -f "$OUTPUT_IRT_GRAPH_DOT_FILENAME" ]; then
    touch "$OUTPUT_IRT_GRAPH_DOT_FILENAME"
fi
if [ "$MEMORY_CHECK" = "mem_check" ]; then
    echo "[run] MEMORY_CHECK flag found, running via valgrind"
    
    valgrind --leak-check=full --error-exitcode="${VALGRIND_MEMCHECK_FAIL_CODE}" \
        ./build/bin/javacompiler "${INPUT_FILENAME}" \
        "${OUTPUT_AST_GRAPH_DOT_FILENAME}" "${OUTPUT_IRT_GRAPH_DOT_FILENAME}" > valgrind.log 2>&1
    status=$?
    
else
    ./build/bin/javacompiler "${INPUT_FILENAME}" "${OUTPUT_AST_GRAPH_DOT_FILENAME}" "${OUTPUT_IRT_GRAPH_DOT_FILENAME}"
    status=$?
fi

if [ "$status" == "0" ]; then

    echo "[run] Running AST graphviz..."
    dot -Tsvg "${OUTPUT_AST_GRAPH_DOT_FILENAME}" -o "${OUTPUT_AST_GRAPH_IMG_FILENAME}"
    echo "[run] Running IRT graphviz..."
    dot -Tsvg "${OUTPUT_IRT_GRAPH_DOT_FILENAME}" -o "${OUTPUT_IRT_GRAPH_IMG_FILENAME}"
    
    exit ${status}
else
    echo "[run] Skipping graphvis, exiting with code =" "$status"
    exit ${status}
fi
