#!/usr/bin/env bash

# Clone the HTS Testing Suit for this repo, it follows a standard convention
TEST_REPO=$(git remote -vv | head -n1 | awk -F ' ' '{print $2}' | sed 's/hal/haltest/g')

# This will look up the last tag in the git repo, depending on the project this may require modification
PROJECT_VERSION=feature/RDKB-43403_v4_hal_creation

HTS_DIR="./hts"

# Check if the common document configuration is present, if not clone it
if [ -d ${HTS_DIR} ]; then
    pushd ${HTS_DIR} > /dev/null
    ./build.sh $@
    popd > /dev/null
else
    echo "Cloning Hal Test Suite for this module"
    git clone ${TEST_REPO} hts
    pushd ${HTS_DIR} > /dev/null
    git flow init -d
    git checkout ${PROJECT_VERSION}
    popd > /dev/null
    ${0}
fi
