#!/bin/bash

git submodule init
git submodule update
docker build -t kozosdev ./kozos-build-server
