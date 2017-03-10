rm -rf .build
mkdir .build
cd .build

export MY_THIRDPARTY_DIR=/Users/jamesfolk/Dropbox/Developer/NJLI/External/thirdparty

export MY_NJLI_DIR=/Users/jamesfolk/Dropbox/Developer/GameEngine/Source/jli_game_engine/version-1.0/src 

export MY_NJLICORE_DIR=/Users/jamesfolk/Dropbox/Developer/GameEngine/Source/platform/core 
export MY_ANDROID_DIR=/Users/jamesfolk/Dropbox/Developer/GameEngine/Source/platform/android 
export MY_EMSCRIPTEN_DIR=/Users/jamesfolk/Dropbox/Developer/GameEngine/Source/platform/emscripten 
export MY_IOS_DIR=/Users/jamesfolk/Dropbox/Developer/GameEngine/Source/platform/ios 
export MY_MAC_DIR=/Users/jamesfolk/Dropbox/Developer/GameEngine/Source/platform/mac 
export MY_TVOS_DIR=/Users/jamesfolk/Dropbox/Developer/GameEngine/Source/platform/tvos 

export GLES20_DIR=/Users/jamesfolk/Dropbox/Developer/GameEngine/Source/jli_game_engine/version-1.0/src/render/OpenGLES20 


cmake .. -G "Unix Makefiles" \
-DCMAKE_CXX_FLAGS='-std=c++11 -stdlib=libc++' \
-DCMAKE_INSTALL_PREFIX=../generated/ \
-DNJLI_THIRDPARTY_DIRECTORY:STRING=${MY_THIRDPARTY_DIR}

make -j4
make install

cpack .. --config CPackConfig.cmake

cd ..

rm -rf cmake.in/docbook/
rm -rf cmake.in/html/
rm -rf cmake.in/latex/
rm -rf cmake.in/rtf/
rm -rf cmake.in/xml/
rm -rf ldoc/
rm -rf src/njli/xml.out

#if [ -f ./.build/NJLIGameEngine* ]; then
    rm -rf install
    mkdir -p install
    cp ./.build/NJLIGameEngine* ./install
    cp ./.build/install_manifest.txt ./install
#fi

#rm -rf .build/

