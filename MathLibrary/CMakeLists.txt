cmake_minimum_required(VERSION 3.27)
project(MathLibrary)

set(CMAKE_CXX_STANDARD 20)

add_library(MathLibrary STATIC library.cpp
        line.cpp
        point.cpp
        segment.cpp
        vector.cpp)
