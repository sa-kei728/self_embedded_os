#!/bin/bash

if [ "$1" == "" ]; then
    docker run -it --rm -v "$PWD":/app -w /app kozosdev make clean
    docker run -it --rm -v "$PWD":/app -w /app kozosdev make
elif [ "$1" == "build" ]; then
    docker run -it --rm -v "$PWD":/app -w /app kozosdev make clean
    docker run -it --rm -v "$PWD":/app -w /app kozosdev make
elif [ "$1" == "debug" ]; then
    docker run -it --rm -v "$PWD":/app -w /app --device=/dev/ttyUSB0 kozosdev
elif [ "$1" == "clean" ]; then
    docker run -it --rm -v "$PWD":/app -w /app kozosdev make clean
else
    echo "Invalid Argument."
fi
