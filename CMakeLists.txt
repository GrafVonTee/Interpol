cmake_minimum_required(VERSION 3.16)
project(triangle_intersections)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(
        unit_tests
        tests/unit_tests.cpp
        src/utils/GeometryUtils.cpp
        src/utils/StatesUtils.cpp
        src/user_interaction/ConsoleInteraction.cpp
        src/user_interaction/Parsing.cpp
        src/math/CalculateIntersections.cpp
)

target_include_directories(unit_tests PUBLIC googletest)
target_include_directories(unit_tests PUBLIC include)

target_link_libraries(
        unit_tests
        gtest
)

add_executable(
        triangle_intersection
        src/main.cpp
        src/utils/GeometryUtils.cpp
        src/utils/StatesUtils.cpp
        src/math/CalculateIntersections.cpp
)

target_include_directories(triangle_intersection PUBLIC include)