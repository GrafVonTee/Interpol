cmake_minimum_required(VERSION 3.16)
project(triangle_intersections)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
find_package(OpenGL REQUIRED)

add_library(
  imgui_lib STATIC
  imgui/imgui.cpp
  imgui/imgui_draw.cpp
  imgui/imgui_demo.cpp
  imgui/imgui_tables.cpp
  imgui/imgui_widgets.cpp

  imgui/imgui_impl_glfw.cpp
  imgui/imgui_impl_opengl3.cpp
)


# unit_test configuration
add_executable(
        unit_tests
        tests/unit_tests.cpp

        src/utils/GeometryUtils.cpp
        src/utils/StatesUtils.cpp

        src/drawing/DrawImage.cpp

        src/user_interaction/ConsoleInteraction.cpp
        src/user_interaction/Parsing.cpp

        src/math/CalculateIntersections.cpp

        src/user_interaction/ConsoleInteraction.cpp
        src/user_interaction/Parsing.cpp
)


target_include_directories(unit_tests PUBLIC googletest)
target_include_directories(unit_tests PUBLIC include)
target_include_directories(unit_tests PUBLIC imgui)

target_link_libraries(
        unit_tests
        imgui_lib
        gtest
        gtest_main
)

# triangle_intersection configuration
add_executable(
        triangle_intersection
        src/main.cpp

        src/utils/GeometryUtils.cpp
        src/utils/StatesUtils.cpp

        src/math/CalculateIntersections.cpp
        src/user_interaction/ConsoleInteraction.cpp

        src/user_interaction/Parsing.cpp
)

target_include_directories(triangle_intersection PUBLIC include)