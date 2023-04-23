cmake_minimum_required(VERSION 3.23)
project(triangle_intersections)

set(CMAKE_CXX_STANDARD 20)

add_executable(triangle_intersections
        src/main.cpp
        src/StructUtils.h src/StructUtils.cpp)