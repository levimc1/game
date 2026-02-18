#!/bin/bash
# Build script a C játékprojekthez

# hibán kilép
set -e

# Build létrehozása ha nincs
rm -rf build
mkdir -p build

# Cmake és build
cmake -S . -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
cmake --build build

echo "[B] építés befejezve, futtatható build/Game alatt."
echo "[B] futtatható futtatása"

# futi 
./build/Game
