#!/usr/bin/env bash

# *
# * If not stated otherwise in this file or this component's LICENSE file the
# * following copyright and licenses apply:
# *
# * Copyright 2023 RDK Management
# *
# * Licensed under the Apache License, Version 2.0 (the "License");
# * you may not use this file except in compliance with the License.
# * You may obtain a copy of the License at
# *
# * http://www.apache.org/licenses/LICENSE-2.0
# *
# * Unless required by applicable law or agreed to in writing, software
# * distributed under the License is distributed on an "AS IS" BASIS,
# * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# * See the License for the specific language governing permissions and
# * limitations under the License.
# *

# Clone the Unit Testing Suit for this repo, it follows a standard convention
# HAL Name is replaced with haltest, allowing this script to be part of the template for all

# This will look up the last tag in the git repo, depending on the project this may require modification
TEST_REPO=$(git remote -vv | head -n1 | awk -F ' ' '{print $2}' | sed 's/hal/haltest/g')

# Set default UT_PROJECT_VERSION to master
if [ -z "${UT_PROJECT_VERSION}" ]; then
    UT_PROJECT_VERSION=master
fi

UT_DIR="./ut"

# Simple help
if [ "${1}" == "-h" ]; then
    echo "Script to build the unit testing suite"
    echo " build_ut.sh <clean> - clean the testing"
    echo " build_ut.sh TARGET=xxx - build the xxx version of the tests, linux/arm etc."
    echo " build_ut.sh <noswitch> - build the linux version of tests using skeleton & stubs"
    exit 0
fi

# Check if the common document configuration is present, if not clone it
if [ -d ${UT_DIR} ]; then
    pushd ${UT_DIR} > /dev/null
    ./build.sh $@
    popd > /dev/null
else
    echo "Cloning unit Test Suite for this module"
    git clone ${TEST_REPO} ut
    pushd ${UT_DIR} > /dev/null
    git checkout ${UT_PROJECT_VERSION}
    popd > /dev/null
    ./${0} $@
fi
