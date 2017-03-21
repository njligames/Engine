#!/bin/sh

CMAKE_EMSCRIPTEN_BIN=/Applications/Developer/emsdk_portable/emscripten/1.35.0
 

_build_emscripten()
{
    MY_BUILD_TYPE=$1
    MY_BUILD_DIR=$2

    mkdir -p .build
    cd .build

    cmake .. -G "Unix Makefiles" \
        -DCMAKE_INSTALL_PREFIX=../generated/ \
        -DNJLI_THIRDPARTY_DIRECTORY:STRING=${MY_THIRDPARTY_DIR} \
        -DCMAKE_CXX_FLAGS='-std=gnu++11 -stdlib=libc++' \
        -DCMAKE_C_FLAGS='-std=gnu99' \
        -DNJLI_BUILD_PLATFORM="emscripten" \
        -DCMAKE_BUILD_TYPE=${MY_BUILD_TYPE} \
        -DNJLI_BUILD_DIR=${MY_BUILD_DIR} \
        -DNJLI_SOUND_PLATFORM=openal \
        -DCMAKE_TOOLCHAIN_FILE=${CMAKE_EMSCRIPTEN_BIN}/cmake/Modules/Platform/Emscripten.cmake

    make -j4
    make install

    cd ..
}

build_emscripten()
{
    BUILD_TYPES=(Debug Release MinsizeRel RelWithDebugInfo)

    for BUILD_TYPE in ${BUILD_TYPES[@]};do
        _build_emscripten ${BUILD_TYPE} "emscripten"
    done
}

EMSDK_PORTABLE=/Applications/Developer/emsdk_portable

# Fetch the latest registry of available tools.
${EMSDK_PORTABLE}/emsdk update

# Download and install the latest SDK tools.
${EMSDK_PORTABLE}/emsdk install latest

# Make the "latest" SDK "active"
${EMSDK_PORTABLE}/emsdk activate latest

# Set the current Emscripten path on Linux/Mac OS X
source ${EMSDK_PORTABLE}/emsdk_env.sh


#build_emscripten
_build_emscripten Debug "emscripten"

