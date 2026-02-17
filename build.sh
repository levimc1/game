#!/bin/bash
# Build script a C játékprojekthez

# hibán kilép
set -e

# Build létrehozása ha nincs
mkdir -p build
cd build

# Cmake és build
cmake ..
make

echo "[B] építés befejezve, futtatható build/Game alatt."
echo "[B] futtatható futtatása"

# futi 
./Game
