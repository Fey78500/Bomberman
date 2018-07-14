cmake_minimum_required(VERSION 3.10)
project(AI)

set(CMAKE_CXX_STANDARD 11)

add_definitions("-static-libgcc -static-libstdc++")

add_executable(AI main.cpp Player.cpp Player.h)
