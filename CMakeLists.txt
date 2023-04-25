cmake_minimum_required(VERSION 3.20)
project(triangle_intersections)

set(CMAKE_CXX_STANDARD 20)

add_executable(triangle_intersections
        src/main.cpp
        src/utils/GeometryUtils.cpp src/utils/StatesUtils.cpp)

target_include_directories(triangle_intersections PUBLIC include)