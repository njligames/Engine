
build_doc()
{
    rm -rf .build
    mkdir -p .build
    cd .build

    cmake .. -G "Unix Makefiles" \
        -DCMAKE_INSTALL_PREFIX=../generated/ \
        -DGENERATE_DOCUMENTATION=ON \
        -DGENERATE_LIB=OFF

    make -j4
    make install

    cd ..
}

build_doc 
