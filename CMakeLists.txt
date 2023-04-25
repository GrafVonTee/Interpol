cmake_minimum_required(VERSION 3.23)
project(triangle_intersections)

set(CMAKE_CXX_STANDARD 20)


# Define Google Test library
add_library(gtest STATIC googletest-main/googletest/src/gtest-all.cc googletest-main/googletest/src/gtest_main.cc)

# Add include directories for Google Test library
target_include_directories(gtest PUBLIC googletest-main/googletest/include)
target_include_directories(gtest PUBLIC googletest-main/googletest)

# include(FetchContent)
# FetchContent_Declare(
#   googletest
#   URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
# )
# # For Windows: Prevent overriding the parent project's compiler/linker settings
# set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
# FetchContent_MakeAvailable(googletest)

add_executable(triangle_intersections
        src/main.cpp
        src/utils/GeometryUtils.cpp src/utils/StatesUtils.cpp)

add_executable(
        unit_tests
        tests/unit_tests.cpp
)

target_include_directories(triangle_intersections PUBLIC include)

target_include_directories(unit_tests PUBLIC googletest-main include)

target_link_libraries(
        unit_tests    
        gtest
)

include(GoogleTest)