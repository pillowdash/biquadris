#!/bin/bash
shopt -s expand_aliases
source ~/.aliases
rm -rf gcm.cache
g++20h iostream memory vector stdexcept string cstdlib
g++20 -c observer.cc
g++20 -c block.cc
g++20 -c Level.cc
g++20 -c Level-impl.cc
g++20 -c Board.cc
g++20 -c Viewver.cc
g++20 -c Viewver-impl.cc
g++20 -c game.cc
g++20 -c game-impl.cc
g++20 -c main.cc
g++20 observer.o block.o Level.o Level-impl.o Board.o Viewver.o Viewver-impl.o game.o game-impl.o main.o -o test
rm *.o
