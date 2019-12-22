#!/bin/bash
#!/usr/bin/env bash

pwd
cd ..
./run_sample.sh "$1" "$2" "$3"
status=$?

VALGRIND_MEMCHECK_FAIL_CODE=100

# exit codes: 
#   0 ok
#   1 traits as any other error
#   [2 .. 99] javacompiler workflow errors
#   100 valgrid memory leaks

EXPECTED_EXIT_CODE=${3}

if [[ $EXPECTED_EXIT_CODE == 0 && $status != 0 || $EXPECTED_EXIT_CODE != 1 && $status != $EXPECTED_EXIT_CODE \
    || $EXPECTED_EXIT_CODE == 1 && $status == 0 ]]; then
    echo -e "\e[96;1m[test]\e[0m Params " "$1" " " "$2" " " "$3" ", expected " "$4" ", got " "$status"
    exit 1
fi

# ./run_sample.sh "$1" "$2" "$3" mem_check
# status=$?
# echo "Memcheck status" "$status"
# if [ $status -eq $VALGRIND_MEMCHECK_FAIL_CODE ]; then
#     echo -e "\e[96;1m[test]\e[0m " "$1" " " "$2" " " "$3" " - \e[96;1mMemory Check Failed\e[0m"
#    exit 1
# fi

echo -e "\e[96;1m[test]\e[0m Test passed!"
exit 0

