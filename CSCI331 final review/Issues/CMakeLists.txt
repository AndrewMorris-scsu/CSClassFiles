cmake_minimum_required(VERSION 3.3)
project(Issues)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES KeyPos.h keypostest.cpp)
add_executable(Issues ${SOURCE_FILES})