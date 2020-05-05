cmake_minimum_required(VERSION 3.16)
project(Decipherer)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic")


set(headers Hamming.h HammingPacket.h Elias.h)
set(sources Decipherer.cpp Hamming.cpp HammingPacket.cpp Elias.cpp)

add_executable(Decipherer ${headers} ${sources})