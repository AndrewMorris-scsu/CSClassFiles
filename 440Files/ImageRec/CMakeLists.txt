cmake_minimum_required(VERSION 3.3)
project(ImageRec)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Image.cpp Image.h ImageStructs.h template.bmp Editor.cpp Editor.h)
add_executable(ImageRec ${SOURCE_FILES})