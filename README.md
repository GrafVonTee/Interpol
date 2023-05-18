# Finding Triangle Intersections

[![CI](https://github.com/GrafVonTee/triangle_intersections/actions/workflows/main.yml/badge.svg?branch=main&event=push)](https://github.com/GrafVonTee/triangle_intersections/actions/workflows/main.yml)


Triangle Intersections is a C++20 project that finds intersection (or nonintersection) between two triangles based on their coordinates. The project uses ImGUI and OpenGL libraries and is a student project for the C++ Programming course.

## Contributors

- Maxim Kudasov (@GrafVonTee)
- Nikolay Krasilnikov (@Kitsumetri)
- Ilya Kuznetsov (@Ilya-Kuznetsov2)
- Daniil Yeryomenko (@DanTimson)
- Alexander Yulin (@Alxyll)

## Project Structure

The following files are included in the project:

- **CONTRIBUTING.md:** This file provides guidelines for contributing to the project.
- **LICENCE:** This file specifies the license under which the project is distributed.
- **SECURITY.md:** This file provides guidelines for reporting security vulnerabilities.

## Testing

The project is tested using GTEST, a C++ testing framework.

## Platforms

The project has been tested and works on Linux, Windows, and MacOS.

## Build System

The project uses the CMake build system and the Clang compiler.

## Usage

To run the project, you must compile and run the executable. Follow the steps below:

For MacOS: need python 3.* and PyCocoa lib
```
git clone https://github.com/GrafVonTee/triangle_intersections.git
cd triangle_intersections
mkdir build
cd build
cmake ..
make
./triangle_intersection
```

## Example
### Demo run:
For testing project you can use as input name: ```Demo``` or ```demo```
#### Console output:
<img width="552" alt="Снимок экрана 2023-05-18 в 18 49 05" src="https://github.com/GrafVonTee/triangle_intersections/assets/100523204/4b45ef8f-9f9d-4f56-82e3-e49e2f35e855">

#### UI output:
<img width="1014" alt="Снимок экрана 2023-05-18 в 18 50 36" src="https://github.com/GrafVonTee/triangle_intersections/assets/100523204/97de1c20-4c6e-42eb-8672-9eb0da1fda6d">

### Custom run:
Write your name (or just press Enter for default name ```Travaler```) and then follow the print instruction

#### Console output:
<img width="691" alt="Снимок экрана 2023-05-18 в 20 40 56" src="https://github.com/GrafVonTee/triangle_intersections/assets/100523204/b27b2a20-2195-4d37-8d9d-f5c34e28c35b">

#### UI output:
<img width="1011" alt="Снимок экрана 2023-05-18 в 20 40 23" src="https://github.com/GrafVonTee/triangle_intersections/assets/100523204/473d745a-34d2-4f10-8d9f-bf27cfc9c614">

## Issues and Contributions

If you encounter any issues or want to contribute to the project, please refer to CONTRIBUTING.md and SECURITY.md for guidelines.

## License

This project is licensed under the MIT License - see the LICENCE file for details.
