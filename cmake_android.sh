
export MY_ANDROID_NDK=/Users/jamesfolk/Library/Android/sdk/ndk-bundle
export MY_ANDROID_API_LEVEL=24

_build_android()
{
    MY_BUILD_TYPE=$1
    MY_BUILD_DIR=$2
    MY_ABI=$3

    MY_BUILD_DIRECTORY=.build
    rm -rf ${MY_BUILD_DIRECTORY}
    mkdir -p ${MY_BUILD_DIRECTORY}
    cd ${MY_BUILD_DIRECTORY}

    cmake .. -G "Ninja" \
        -DCMAKE_CXX_FLAGS='-std=gnu++11' \
        -DCMAKE_INSTALL_PREFIX=../generated/ \
        -DNJLI_THIRDPARTY_DIRECTORY:STRING=${MY_THIRDPARTY_DIR} \
        -DNJLI_BUILD_PLATFORM='android' \
        -DCMAKE_BUILD_TYPE=${MY_BUILD_TYPE} \
        -DNJLI_BUILD_DIR=${MY_BUILD_DIR} \
        -DANDROID_ABI=${MY_ABI} \
        -DANDROID_NATIVE_API_LEVEL=${MY_ANDROID_API_LEVEL} \
        -DANDROID_STL=c++_shared \
        -DANDROID_TOOLCHAIN=gcc \
        -DCMAKE_CXX_FLAGS='-std=gnu++11' \
        -DCMAKE_TOOLCHAIN_FILE=${MY_ANDROID_NDK}/build/cmake/android.toolchain.cmake

    ninja -C.
    ninja install

    cd ..
}

build_android()
{
    BUILD_TYPES=(Debug Release MinsizeRel RelWithDebugInfo)
    ABIS=(armeabi-v7a x86 mips arm64-v8a x86_64 mips64)

    for ABI in ${ABIS[@]}; do
        for BUILD_TYPE in ${BUILD_TYPES[@]};do
            _build_android ${BUILD_TYPE} "android/${MY_ANDROID_API_LEVEL}/${ABI}" ${ABI}
        done
    done
}

#build_android
_build_android Release "android/${MY_ANDROID_API_LEVEL}/armeabi-v7a" armeabi-v7a


