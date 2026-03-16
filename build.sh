#!/bin/bash
set -e

BUILD_TYPE=${1:-Debug}

rm -rf build
mkdir -p build

cmake -S . -B build -DCMAKE_BUILD_TYPE=$BUILD_TYPE -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
cmake --build build

echo "[B] építés befejezve ($BUILD_TYPE)"
echo "[B] futtatható futtatása"

./build/Game.exe