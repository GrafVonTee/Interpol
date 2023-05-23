# Finding Triangle Intersections

[![CI](https://github.com/GrafVonTee/triangle_intersections/actions/workflows/main.yml/badge.svg)](https://github.com/GrafVonTee/triangle_intersections/actions/workflows/main.yml)


Triangle Intersections is a C++20 project that finds intersection (or nonintersection) between two triangles based on their coordinates. The project uses ImGUI and OpenGL libraries and is a student project for the C++ Programming course.

## Contributors

- Maxim Kudasov (@GrafVonTee)
- Nikolay Krasilnikov (@Kitsumetri)
- Ilya Kuznetsov (@Ilya-Kuznetsov2)
- Daniil Yeryomenko (@DanTimson)
- Alexander Yulin (@Alxyll)

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
#### Console Input:
<img width="583" alt="Снимок экрана 2023-05-23 в 21 29 04" src="https://github.com/GrafVonTee/triangle_intersections/assets/100523204/26834d0f-4adf-4fca-b0b3-5b4d7f60ad9c">

#### UI output:
<img width="1440" alt="Снимок экрана 2023-05-23 в 21 29 28" src="https://github.com/GrafVonTee/triangle_intersections/assets/100523204/ec9b2f05-fd9f-46a4-9cf8-1450eeb6c226">

### Custom run:
Write your name (or just press Enter for default name ```Travaler```) and then follow the print instruction

#### Console Input:
<img width="584" alt="Снимок экрана 2023-05-23 в 21 27 40" src="https://github.com/GrafVonTee/triangle_intersections/assets/100523204/056d089b-65b0-4ef0-ac11-7c3954a3f2be">

#### UI output:
<img width="1439" alt="Снимок экрана 2023-05-23 в 21 28 17" src="https://github.com/GrafVonTee/triangle_intersections/assets/100523204/af89ba71-c683-4c16-ab07-e389eef88018">


## New Feature:
You can change triangle's coordinates in "Properties" window and it's automatically plot new intersection.
<img width="531" alt="Снимок экрана 2023-05-23 в 21 27 09" src="https://github.com/GrafVonTee/triangle_intersections/assets/100523204/58745e49-62db-47b5-bdad-db16b9342aa2">


## Issues and Contributions

If you encounter any issues or want to contribute to the project, please refer to [CONTRIBUTING.md](CONTRIBUTING.md) and [SECURITY.md](SECURITY.md) for guidelines.

## License

This project is licensed under the MIT License - see the [LICENCE](LICENSE) file for details.
