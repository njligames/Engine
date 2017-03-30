#!/bin/sh

PWD=`pwd`

CMAKE_EMSCRIPTEN_BIN=/Applications/Developer/emsdk_portable/emscripten/1.35.0

build_emscripten()
{
    ASM=/Users/jamesfolk/Dropbox/Developer/NJLI/External/thirdparty/dockcross-browser-asmjs

    flags='-Wno-warn-absolute-paths --memory-init-file 0 -s DISABLE_EXCEPTION_CATCHING=0 -s ALLOW_MEMORY_GROWTH=1'

    MY_BUILD_DIRECTORY=.build
    rm -rf .build

    cd ..

    ${ASM} cmake -HEngine -B${MY_BUILD_DIRECTORY} -G Ninja \
        -DCMAKE_INSTALL_PREFIX=../generated/ \
        -DNJLI_THIRDPARTY_DIRECTORY:STRING=${MY_THIRDPARTY_DIR} \
        "-DCMAKE_CXX_FLAGS=${flags} " \
        "-DCMAKE_C_FLAGS=${flags}" \
        -DNJLI_BUILD_PLATFORM="emscripten" \
        -DCMAKE_BUILD_TYPE=Release \
        -DNJLI_BUILD_DIR="emscripten" \
        -DNJLI_SOUND_PLATFORM=openal

    ${ASM} cmake -HEngine -B${MY_BUILD_DIRECTORY} -G Ninja \
        -DCMAKE_INSTALL_PREFIX=../generated/ \
        -DNJLI_THIRDPARTY_DIRECTORY:STRING=${MY_THIRDPARTY_DIR} \
        "-DCMAKE_CXX_FLAGS=${flags} " \
        "-DCMAKE_C_FLAGS=${flags}" \
        -DNJLI_BUILD_PLATFORM="emscripten" \
        -DCMAKE_BUILD_TYPE=Release \
        -DNJLI_BUILD_DIR="emscripten" \
        -DNJLI_SOUND_PLATFORM=openal

    ${ASM} ninja -C${MY_BUILD_DIRECTORY} install
    ninja -t graph all | dot -Tpng -ograph.png
}

#build_emscripten()
#{
#    BUILD_TYPES=(Debug Release MinsizeRel RelWithDebugInfo)
#
#    for BUILD_TYPE in ${BUILD_TYPES[@]};do
#        _build_emscripten ${BUILD_TYPE} "emscripten"
#    done
#}
#
#EMSDK_PORTABLE=/Applications/Developer/emsdk_portable
#
## Fetch the latest registry of available tools.
#${EMSDK_PORTABLE}/emsdk update
#
## Download and install the latest SDK tools.
#${EMSDK_PORTABLE}/emsdk install latest
#
## Make the "latest" SDK "active"
#${EMSDK_PORTABLE}/emsdk activate latest
#
## Set the current Emscripten path on Linux/Mac OS X
#source ${EMSDK_PORTABLE}/emsdk_env.sh
#
#
##build_emscripten
build_emscripten

