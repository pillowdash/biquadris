#!/bin/bash
shopt -s expand_aliases
source .aliases
rm -rf gcm.cache

# 1. Define the specific location of the X11 headers for the COMPILER
X11_INCLUDE="-I/opt/X11/include"

# 2. Define the specific location of the X11 binaries for the LINKER
X11_LIB="-L/opt/X11/lib -lX11"

# 3. Add the include path to the compilation steps
g++20h iostream fstream memory vector stdexcept string cstdlib
g++20 -c window.cc ${X11_INCLUDE}
g++20 -c window-impl.cc ${X11_INCLUDE}
g++20 -c observer.cc
g++20 -c observer-impl.cc
g++20 -c block.cc
g++20 -c block-impl.cc
g++20 -c Level.cc
g++20 -c Level-impl.cc
g++20 -c Board.cc
g++20 -c board-impl.cc
g++20 -c Viewver.cc ${X11_INCLUDE} 
g++20 -c Viewver-impl.cc ${X11_INCLUDE}
g++20 -c game.cc
g++20 -c game-impl.cc
g++20 -c main.cc

# 4. Link everything together
g++20 window.o window-impl.o observer.o observer-impl.o block.o block-impl.o Level.o Level-impl.o Board.o board-impl.o Viewver.o Viewver-impl.o game.o game-impl.o main.o -o test ${X11_LIB} ${X11_INCLUDE}

rm *.o