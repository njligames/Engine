#!/bin/sh

MY_BUILT_LIBRARY=$1

MY_IOS_PATH=/Applications/Xcode.app/Contents/Developer/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOS.sdk/System/Library/Frameworks/OpenGLES.framework 


export CMAKE_IOS_SYSROOT=/Applications/Xcode.app/Contents/Developer/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOS.sdk
export CMAKE_TVOS_SYSROOT=/Applications/Xcode.app/Contents/Developer/Platforms/AppleTVOS.platform/Developer/SDKs/AppleTVOS.sdk/
export CMAKE_WATCHOS_SYSROOT=/Applications/Xcode.app/Contents/Developer/Platforms/WatchOS.platform/Developer/SDKs/WatchOS.sdk
export CMAKE_MACOS_SYSROOT=/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/

export CMAKE_IOS_SYSTEM_VERSION=`xcodebuild -sdk /Applications/Xcode.app/Contents/Developer/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOS.sdk -version SDKVersion`
export CMAKE_TVOS_SYSTEM_VERSION=`xcodebuild -sdk /Applications/Xcode.app/Contents/Developer/Platforms/AppleTVOS.platform/Developer/SDKs/AppleTVOS.sdk/ -version SDKVersion`
export CMAKE_WATCHOS_SYSTEM_VERSION=`xcodebuild -sdk /Applications/Xcode.app/Contents/Developer/Platforms/WatchOS.platform/Developer/SDKs/WatchOS.sdk -version SDKVersion`
export CMAKE_MACOS_SYSTEM_VERSION=`xcodebuild -sdk /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/ -version SDKVersion`

#codesign -s "James Folk" /Users/jamesfolk/Dropbox/Developer/NJLI/NJLIGameEngine-0.1.1-Darwin/module/ios/10.2/SIMULATOR/Release/njli.so

build_apple_xcode()
{
#    #Debug Release MinsizeRel RelWithDebugInfo
#    MY_BUILD_TYPE=$1
#    #ios appletvos applewatchos
#    MY_PLATFORM=$2
#    MY_SIMULATOR=$3
#    MY_BUILD_PLAT=$4
#    MY_LIBRARY=$5
#    MY_VERSION=$6

    MY_PLATFORM=$1
    MY_BUILD_PLAT=$2
    MY_VERSION=$3

    MY_BUILD_DIR="${MY_PLATFORM}/${MY_VERSION}/${MY_BUILD_PLAT}"

    MY_BUILD_DIRECTORY=Xcode_build

    rm -rf ${MY_BUILD_DIRECTORY}
    mkdir -p ${MY_BUILD_DIRECTORY}
    cd ${MY_BUILD_DIRECTORY}

    cmake .. -G "Xcode" \
        -DCMAKE_CXX_FLAGS='-std=gnu++11' \
        -DNJLI_THIRDPARTY_DIRECTORY:STRING=${MY_THIRDPARTY_DIR} \
        -DNJLI_BUILD_PLATFORM=${MY_PLATFORM} \
        -DCMAKE_BUILD_TYPE=Debug \
        -DNJLI_BUILD_DIR=${MY_BUILD_DIR}
    cmake --build .

#    cmake .. -G "Xcode" \
#        -DCMAKE_CXX_FLAGS='-std=gnu++11' \
#        -DNJLI_THIRDPARTY_DIRECTORY:STRING=${MY_THIRDPARTY_DIR} \
#        -DNJLI_BUILD_PLATFORM=${MY_PLATFORM} \
#        -DCMAKE_BUILD_TYPE=Release \
#        -DNJLI_BUILD_DIR=${MY_BUILD_DIR}
#
#    cmake .. -G "Xcode" \
#        -DCMAKE_CXX_FLAGS='-std=gnu++11' \
#        -DNJLI_THIRDPARTY_DIRECTORY:STRING=${MY_THIRDPARTY_DIR} \
#        -DNJLI_BUILD_PLATFORM=${MY_PLATFORM} \
#        -DCMAKE_BUILD_TYPE=MinSizeRel \
#        -DNJLI_BUILD_DIR=${MY_BUILD_DIR}
#
#    cmake .. -G "Xcode" \
#        -DCMAKE_CXX_FLAGS='-std=gnu++11' \
#        -DNJLI_THIRDPARTY_DIRECTORY:STRING=${MY_THIRDPARTY_DIR} \
#        -DNJLI_BUILD_PLATFORM=${MY_PLATFORM} \
#        -DCMAKE_BUILD_TYPE=RelWithDebugInfo \
#        -DNJLI_BUILD_DIR=${MY_BUILD_DIR}

    cd ..
}

build_apple()
{
    #Debug Release MinsizeRel RelWithDebugInfo
    MY_BUILD_TYPE=$1
    #ios appletvos applewatchos
    MY_PLATFORM=$2
    MY_SIMULATOR=$3
    MY_BUILD_PLAT=$4
    MY_LIBRARY=$5
    MY_VERSION=$6

    MY_BUILD_DIR="${MY_PLATFORM}/${MY_VERSION}/${MY_BUILD_PLAT}"

    MY_BUILD_DIRECTORY=.build
    rm -rf ${MY_BUILD_DIRECTORY}
    mkdir -p ${MY_BUILD_DIRECTORY}
    cd ${MY_BUILD_DIRECTORY}

    cmake .. -G "Ninja" \
        -DCMAKE_CXX_FLAGS='-std=gnu++11' \
        -DCMAKE_INSTALL_PREFIX=../generated/ \
        -DNJLI_THIRDPARTY_DIRECTORY:STRING=${MY_THIRDPARTY_DIR} \
        -DNJLI_BUILD_PLATFORM=${MY_PLATFORM} \
        -DCMAKE_BUILD_TYPE=${MY_BUILD_TYPE} \
        -DNJLI_BUILD_DIR=${MY_BUILD_DIR} \
        -DCMAKE_TOOLCHAIN_FILE=${MY_THIRDPARTY_DIR}/apple.toolchain.cmake \
        -DSIMULATOR:BOOL=${MY_SIMULATOR} \
        -DENABLE_BITCODE:BOOL=OFF \
        -DPLATFORM=${MY_PLATFORM}

    ninja -C.
    ninja install

    cd ..
}

build_ios()
{
    build_apple Debug ios ON iphonesimulator ${MY_IOS_PATH} ${CMAKE_IOS_SYSTEM_VERSION}
    build_apple Debug ios OFF iphoneos ${MY_IOS_PATH} ${CMAKE_IOS_SYSTEM_VERSION}

    build_apple Release ios ON iphonesimulator ${MY_IOS_PATH} ${CMAKE_IOS_SYSTEM_VERSION}
    build_apple Release ios OFF iphoneos ${MY_IOS_PATH} ${CMAKE_IOS_SYSTEM_VERSION}

    build_apple MinsizeRel ios ON iphonesimulator ${MY_IOS_PATH} ${CMAKE_IOS_SYSTEM_VERSION}
    build_apple MinsizeRel ios OFF iphoneos ${MY_IOS_PATH} ${CMAKE_IOS_SYSTEM_VERSION}

    build_apple RelWithDebugInfo ios ON iphonesimulator ${MY_IOS_PATH} ${CMAKE_IOS_SYSTEM_VERSION}
    build_apple RelWithDebugInfo ios OFF iphoneos ${MY_IOS_PATH} ${CMAKE_IOS_SYSTEM_VERSION}
}

build_appletvos()
{
    build_apple Debug appletvos ON appletvsimulator ${MY_IOS_PATH} ${CMAKE_TVOS_SYSTEM_VERSION}
    build_apple Debug appletvos OFF appletvos ${MY_IOS_PATH} ${CMAKE_TVOS_SYSTEM_VERSION}

    build_apple Release appletvos ON appletvsimulator ${MY_IOS_PATH} ${CMAKE_TVOS_SYSTEM_VERSION}
    build_apple Release appletvos OFF appletvos ${MY_IOS_PATH} ${CMAKE_TVOS_SYSTEM_VERSION}

    build_apple MinsizeRel appletvos ON appletvsimulator ${MY_IOS_PATH} ${CMAKE_TVOS_SYSTEM_VERSION}
    build_apple MinsizeRel appletvos OFF appletvos ${MY_IOS_PATH} ${CMAKE_TVOS_SYSTEM_VERSION}

    build_apple RelWithDebugInfo appletvos ON appletvsimulator ${MY_IOS_PATH} ${CMAKE_TVOS_SYSTEM_VERSION}
    build_apple RelWithDebugInfo appletvos OFF appletvos ${MY_IOS_PATH} ${CMAKE_TVOS_SYSTEM_VERSION}
}

build_applewatchos()
{
    build_apple Debug applewatchos ON SIMULATOR ${MY_IOS_PATH} ${CMAKE_WATCHOS_SYSTEM_VERSION}
    build_apple Debug applewatchos OFF OS ${MY_IOS_PATH} ${CMAKE_WATCHOS_SYSTEM_VERSION}

    build_apple Release applewatchos ON SIMULATOR ${MY_IOS_PATH} ${CMAKE_WATCHOS_SYSTEM_VERSION}
    build_apple Release applewatchos OFF OS ${MY_IOS_PATH} ${CMAKE_WATCHOS_SYSTEM_VERSION}

    build_apple MinsizeRel applewatchos ON SIMULATOR ${MY_IOS_PATH} ${CMAKE_WATCHOS_SYSTEM_VERSION}
    build_apple MinsizeRel applewatchos OFF OS ${MY_IOS_PATH} ${CMAKE_WATCHOS_SYSTEM_VERSION}

    build_apple RelWithDebugInfo applewatchos ON SIMULATOR ${MY_IOS_PATH} ${CMAKE_WATCHOS_SYSTEM_VERSION}
    build_apple RelWithDebugInfo applewatchos OFF OS ${MY_IOS_PATH} ${CMAKE_WATCHOS_SYSTEM_VERSION}
}

_build_macos()
{
    MY_BUILD_DIRECTORY=.build
    rm -rf ${MY_BUILD_DIRECTORY}
    mkdir -p ${MY_BUILD_DIRECTORY}
    cd ${MY_BUILD_DIRECTORY}

    #Debug Release MinsizeRel RelWithDebugInfo
    MY_BUILD_TYPE=$1
    MY_VERSION=$2
    MY_BUILD_DIR="macOS/${MY_VERSION}"

    cmake .. -G "Ninja" \
        -DGL_GLEXT_PROTOTYPES:BOOL=ON \
        -DCMAKE_CXX_FLAGS='-std=gnu++11' \
        -DCMAKE_INSTALL_PREFIX=../generated/ \
        -DNJLI_THIRDPARTY_DIRECTORY:STRING=${MY_THIRDPARTY_DIR} \
        -DNJLI_GRAPHICS_PLATFORM=opengl_2.1 \
        -DCMAKE_OSX_ARCHITECTURES="i386;x86_64" \
        -DNJLI_BUILD_PLATFORM="macOS" \
        -DCMAKE_BUILD_TYPE=${MY_BUILD_TYPE} \
        -DNJLI_BUILD_DIR=${MY_BUILD_DIR}

    ninja -C.
    ninja install

    cd ..
}

build_macos()
{
    BUILD_TYPES=(Debug Release MinsizeRel RelWithDebugInfo)

    for BUILD_TYPE in ${BUILD_TYPES[@]};do
        _build_macos ${BUILD_TYPE} ${CMAKE_MACOS_SYSTEM_VERSION}
    done
}

#build_macos
#build_ios
#build_appletvos
#build_applewatchos

build_apple_xcode ios iphonesimulator ${CMAKE_IOS_SYSTEM_VERSION}

#build_apple Debug ios ON iphonesimulator ${MY_IOS_PATH} ${CMAKE_IOS_SYSTEM_VERSION}
#build_apple Debug appletvos ON appletvsimulator ${MY_IOS_PATH} ${CMAKE_TVOS_SYSTEM_VERSION}
