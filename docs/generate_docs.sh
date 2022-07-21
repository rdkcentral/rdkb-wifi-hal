#!/usr/bin/env bash

# Check if the common document configuration is present, if not clone it

PROJECT_VERSION = $(shell git describe --tags | head -n1)

if [ -d "./build" ]; then
    make -C ./build PROJECT_NAME="RDK-B Wifi HAL" PROJECT_VERSION=${PROJECT_VERSION}
else
    echo "Cloning Common documentation generation"
    git clone git@github.com:comcast-sky/rdk-components-hal-doxygen.git build
    cd ./build
    git flow init -d
    cd ..
    ./${0}
fi