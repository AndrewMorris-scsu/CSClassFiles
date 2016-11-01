cmake_minimum_required(VERSION 3.3)
project(BPlusTree)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp
        Block.cpp Block.h
        BPlusTree.h BPlusTree.cpp
        BulkLoad.cpp
        fileOperations.h
        KeyPos.h
        merge.h
        ReplacementSelection.cpp
        ReplacementSelection.h
        )
add_executable(BPlusTree ${SOURCE_FILES})