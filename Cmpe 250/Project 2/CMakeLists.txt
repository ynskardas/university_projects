cmake_minimum_required(VERSION 3.6)
project(CmpeAirlines)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Passenger.cpp Passenger.h Event.cpp Event.h)
add_executable(CmpeAirlines ${SOURCE_FILES})