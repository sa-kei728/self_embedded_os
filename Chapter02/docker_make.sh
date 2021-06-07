#!/bin/bash

if [ "$1" == "" ]; then
    docker run -it --rm -v "$PWD":/app -w /app kozosdev make clean
    docker run -it --rm -v "$PWD":/app -w /app kozosdev make
    docker run -it --rm -v "$PWD":/app -w /app kozosdev make image
    docker run -it --rm -v "$PWD":/app -w /app --device=/dev/ttyUSB0 kozosdev make write
elif [ "$1" == "build" ]; then
    docker run -it --rm -v "$PWD":/app -w /app kozosdev make clean
    docker run -it --rm -v "$PWD":/app -w /app kozosdev make
    docker run -it --rm -v "$PWD":/app -w /app kozosdev make image
elif [ "$1" == "write" ]; then
    docker run -it --rm -v "$PWD":/app -w /app --device=/dev/ttyUSB0 kozosdev make write
elif [ "$1" == "debug" ]; then
    docker run -it --rm -v "$PWD":/app -w /app --device=/dev/ttyUSB0 kozosdev
elif [ "$1" == "clean" ]; then
    docker run -it --rm -v "$PWD":/app -w /app kozosdev make clean
else
    echo "Invalid Argument."
fi
