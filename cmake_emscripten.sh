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
        -DNJLI_BUILD_PLATFORM="emscripten" \
        -DCMAKE_BUILD_TYPE=${MY_BUILD_TYPE} \
        -DNJLI_BUILD_DIR=${MY_BUILD_DIR} \
        -DCMAKE_TOOLCHAIN_FILE=${CMAKE_EMSCRIPTEN_BIN}/cmake/Modules/Platform/Emscripten.cmake
        -DCMAKE_C_FLAGS='-D__linux__'

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

build_emscripten

