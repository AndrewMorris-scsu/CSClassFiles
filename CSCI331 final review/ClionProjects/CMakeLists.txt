cmake_minimum_required(VERSION 3.3)
project(RepSelect)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    DualHeap.cpp
    DualHeap.h
    Heap.cpp
    Heap.h
    replaceSelection.cpp
    replaceSelection.h
    TestDualHeap.cpp)

add_executable(RepSelect ${SOURCE_FILES})