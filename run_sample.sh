#!/bin/bash
#!/usr/bin/env bash

if ! [[ $# -eq 3 || $# -eq 4 ]]
  then
    echo "Usage: ./run_sample.sh [java code filename] [output folder] [[ no_mem_check | mem_check ]]";
    exit 0
fi

echo -e "\e[92;1m[run]\e[0m Running sample" "$1" "$2" "$3" "..."

INPUT_FILENAME="$1"
OUTPUT_FOLDER="$2"
MEMORY_CHECK=${3:-no_mem_check}
VALGRIND_MEMCHECK_FAIL_CODE=100

echo -e "\e[92;1m[run]\e[0m Starting program..."    
if [ ! -d "$OUTPUT_FOLDER" ]; then
  mkdir -p "$OUTPUT_FOLDER"
fi

#if [ ! -f "$OUTPUT_AST_GRAPH_DOT_FILENAME" ]; then
#    touch "$OUTPUT_AST_GRAPH_DOT_FILENAME"
#fi
#
#if [ ! -f "$OUTPUT_IRT_GRAPH_DOT_FILENAME" ]; then
#    touch "$OUTPUT_IRT_GRAPH_DOT_FILENAME"
#fi

if [ "${MEMORY_CHECK}" = "mem_check" ]; then
    echo "\e[92;1m[run]\e[0m MEMORY_CHECK flag found, running via valgrind"
    
    valgrind --leak-check=full --error-exitcode="${VALGRIND_MEMCHECK_FAIL_CODE}" \
        ./build/bin/javacompiler "${INPUT_FILENAME}" \
        "${OUTPUT_FOLDER}" > valgrind.log 2>&1
    status=$?
    
else
    ./build/bin/javacompiler "${INPUT_FILENAME}" "${OUTPUT_FOLDER}"
    status=$?
fi

if [ "$status" == "0" ]; then

    # echo "[run] Running AST graphviz..."
    # dot -Tsvg "${OUTPUT_AST_GRAPH_DOT_FILENAME}" -o "${OUTPUT_AST_GRAPH_IMG_FILENAME}"
    # echo "[run] Running IRT graphviz..."
    #dot -Tsvg "${OUTPUT_IRT_GRAPH_DOT_FILENAME}" -o "${OUTPUT_IRT_GRAPH_IMG_FILENAME}"
    
    for filename in "$OUTPUT_FOLDER"/*.dot; do
        name=${filename##*/}
        base=${name%.dot}
        dot -Tsvg "${filename}" -o "${OUTPUT_FOLDER}/${base}.svg"
    done
    
    
    exit ${status}
else
    echo -e "\e[92;1m[run]\e[0m Skipping graphvis, exiting with code =" "$status"
    exit ${status}
fi
