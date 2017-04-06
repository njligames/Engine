#!/bin/sh

build_emscripten()
{
    flags='-Wno-warn-absolute-paths --memory-init-file 0 -s DISABLE_EXCEPTION_CATCHING=0 -s ALLOW_MEMORY_GROWTH=1 -s LEGACY_GL_EMULATION=1'

    emcmake cmake -G "Sublime Text 2 - Unix Makefiles" ../.. \
        -DCMAKE_INSTALL_PREFIX=../../generated/ \
        -DNJLI_THIRDPARTY_DIRECTORY:STRING=${MY_THIRDPARTY_DIR} \
        "-DCMAKE_CXX_FLAGS=${flags} -std=gnu++11" \
        "-DCMAKE_C_FLAGS=${flags}" \
        -DNJLI_BUILD_PLATFORM="emscripten" \
        -DCMAKE_BUILD_TYPE=Release \
        -DNJLI_BUILD_DIR="emscripten" \
        -DNJLI_SOUND_PLATFORM=openal

    emmake make -j8
}

#build_emscripten()
#{
#    BUILD_TYPES=(Debug Release MinsizeRel RelWithDebugInfo)
#
#    for BUILD_TYPE in ${BUILD_TYPES[@]};do
#        _build_emscripten ${BUILD_TYPE} "emscripten"
#    done
#}

cd projects

rm -rf emscripten_Sublime
mkdir emscripten_Sublime
cd emscripten_Sublime
build_emscripten
cd ..

