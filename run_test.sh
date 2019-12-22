#!/bin/bash
#!/usr/bin/env bash

pwd
# cd ..
./run_sample.sh "$1" "$2" "$3"
status=$?

VALGRIND_MEMCHECK_FAIL_CODE=100

# exit codes: 
#   0 ok
#   1 traits as any other error
#   [2 .. 99] javacompiler workflow errors
#   100 valgrid memory leaks

if [[ $4 == 0 && $status != 0 || $4 != 1 && $status != $4 || $4 == 1 && $status == 0 ]]; then
    echo -e "test " "$1" " " "$2" " " "$3" ", expected " "$4" ", got " "$status"
    exit 1
fi

# ./run_sample.sh "$1" "$2" "$3" mem_check
# status=$?
# echo "Memcheck status" "$status"
# if [ $status -eq $VALGRIND_MEMCHECK_FAIL_CODE ]; then
#     echo -e "test " "$1" " " "$2" " " "$3" " - Memory check failed"
#    exit 1
# fi

echo "Test passed!"
exit 0

