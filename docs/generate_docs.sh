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

# In the future this should moved to a fixed verison
HAL_GENERATOR_VERSION=develop

# This will look up the last tag in the git repo, depending on the project this may require modification
PROJECT_VERSION=$(git describe --tags | head -n1)

# Check if the common document configuration is present, if not clone it
if [ -d "./build" ]; then
    make -C ./build PROJECT_NAME="RDK-B Wifi HAL" PROJECT_VERSION=${PROJECT_VERSION}
else
    echo "Cloning Common documentation generation"
    git clone git@github.com:rdkcentral/hal-doxygen.git build
    cd ./build
    git checkout ${HAL_GENERATOR_VERSION}
    cd ..
    ./${0}
fi