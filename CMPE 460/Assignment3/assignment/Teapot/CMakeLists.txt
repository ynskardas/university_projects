cmake_minimum_required(VERSION 3.17)
project(Teapot2)

set(CMAKE_CXX_STANDARD 14)

add_executable(Teapot2 teapot.cpp geometry.h TeaPotRayTrace.cpp)