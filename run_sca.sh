#!/bin/bash
#!/usr/bin/env bash

cppcheck src --error-exitcode=1
if [[ $? != 0 ]]; then
    exit 101
fi

cppcheck tests --error-exitcode=1
if [[ $? != 0 ]]; then
    exit 101
fi
