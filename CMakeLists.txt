cmake_minimum_required(VERSION 3.10)

project(Hinae)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS -Wall)

include_directories(include)

add_executable(test test/test.cpp)
