cmake_minimum_required(VERSION 3.10)
project(GameEngine)

set(CMAKE_CXX_STANDARD 11)

add_definitions("-static-libgcc -static-libstdc++")

add_executable(GameEngine main.cpp Level.cpp Level.h Player.cpp Player.h Bomb.cpp Bomb.h)