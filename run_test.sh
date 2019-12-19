#!/bin/bash
#!/usr/bin/env bash

pwd
cd ..
./run_sample.sh $1 $2 $3
status=$?

if [ $(($status == 0)) != $(($4 == 0)) ]; then
    echo -e "test " $1 " " $2 " " $3 ", expected " $4 ", got " $status
    exit 1
else
    echo "Test passed"
    exit 0
fi
