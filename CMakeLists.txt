cmake_minimum_required(VERSION 3.16)
project(triangle_intersections)

set(CMAKE_CXX_STANDARD 20)

# Define Google Test library
add_library(gtest STATIC googletest-main/googletest/src/gtest-all.cc googletest-main/googletest/src/gtest_main.cc)

# Add include directories for Google Test library
target_include_directories(gtest PUBLIC googletest-main/googletest/include)
target_include_directories(gtest PUBLIC googletest-main/googletest)

add_executable(
        unit_tests
        tests/unit_tests.cpp
        src/utils/GeometryUtils.cpp src/utils/StatesUtils.cpp
        src/CalculateIntersections.cpp
)

target_include_directories(unit_tests PUBLIC googletest-main/include)
target_include_directories(unit_tests PUBLIC include)

target_link_libraries(
        unit_tests
        gtest
)
