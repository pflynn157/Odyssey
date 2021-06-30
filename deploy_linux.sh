#!/bin/bash

if [ ! -d ./build ] ; then
    echo "Error: The application does not seem to be built."
    exit 1
fi

cd build

if [ -d ./linux_bin ]; then
    rm -rf ./linux_bin
fi

mkdir linux_bin

cp src/uds-explorer linux_bin
cp ../src/icons/system-file-manager.svg linux_bin
cp ../linux/* linux_bin
cp ../COPYING* linux_bin

tar -czvf uds-explorer_bin_linux.tar.gz linux_bin/*

