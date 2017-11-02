cmake_minimum_required(VERSION 3.7)
project(ticTacToe)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp game/Game.cpp game/Game.h)
add_executable(ticTacToe ${SOURCE_FILES})