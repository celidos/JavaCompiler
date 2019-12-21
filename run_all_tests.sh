#!/bin/bash
#!/usr/bin/env bash

VERBOSE=${1:-}

cd build

ctest . ${VERBOSE}
