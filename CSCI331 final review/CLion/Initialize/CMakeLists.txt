cmake_minimum_required(VERSION 3.3)
project(Initialize)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES BulkLoad.cpp Block.h Block.cpp Block.h)
add_executable(Initialize ${SOURCE_FILES})