#!/bin/bash
# Build script for the project
# Make build directory if it doesn't exist

# Read flags
while getopts "r" opt; do
    case $opt in
        r)
            # Rebuild
            rm -rf build bin
            ;;
        \?)
            echo "Invalid option: -$OPTARG" >&2
            ;;
    esac
done

mkdir -p build
cd build

# Run cmake
cmake ..
# cmake --build . --config Release --parallel
cmake --build . -j 8

# Cmake install
cmake --install .