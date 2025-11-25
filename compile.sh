#!/bin/bash
shopt -s expand_aliases
source ~/.aliases
rm -rf gcm.cache
g++20h iostream utility algorithm string
g++20 observer.cc block.cc Level.cc Level-impl.cc board.cc viewver.cc viewver-impl.cc game.cc game-impl.cc main.cc -c
g++20 -c observer.cc
g++20 -c block.cc
g++20 -c Level.cc
g++20 -c Level-impl.cc
g++20 -c board.cc
g++20 -c viewver.cc
g++20 -c viewver-impl.cc
g++20 -c game.cc
g++20 -c game-impl.cc
g++20 -c main.cc
g++20 observer.o block.o Level.o Level-impl.o board.o viewver.o viewver-impl.o game.o game-impl.o main.o -o test
rm *.o
