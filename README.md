# Interpol ♾️
[![CI](https://github.com/GrafVonTee/triangle_intersections/actions/workflows/main.yml/badge.svg)](https://github.com/GrafVonTee/triangle_intersections/actions/workflows/main.yml)


## Interpol - desktop UI application that calculating and ploting intersection between polygons based on user input.
The project uses `ImGUI` and `OpenGL` libraries and is a student project for the C++ Programming course.

## Contributors

- Maxim Kudasov (@GrafVonTee)
- Nikolay Krasilnikov (@Kitsumetri)
- Ilya Kuznetsov (@Ilya-Kuznetsov2)
- Daniil Yeryomenko (@DanTimson)
- Alexander Yulin (@Alxyll)

## Testing

The project is tested using `GTEST`, a C++ testing framework.

## Platforms

The project has been tested and works on `GNU/Linux`, `Windows 10`, and `MacOS Ventura`.

## Build System

The project uses the `CMake` / `ninja` build system and supports `MinGW`, `CLang` and `gcc`.

## Usage

To run the project, you must compile and run the executable. Follow the steps below:

Need python 3.* and PyCocoa lib
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
For testing project you can use as input name: ```Demo```/```demo```/```DEMO```
#### Console Input:
```
>>>
Please, enter your name if you wish (otherwise just press Enter): DEMO

Greetings, *DEMO*!
This program will immerse you in the wonderful world of
        Polygon Intersections!
All you need is entering the values of your two polygons...
...and take resulted intersection!

Your polygon is a hexagon A5,A6,A1,A2,A3,A4 with points:
Point A5 = (500, 0)
Point A6 = (100, 100)
Point A1 = (0, 900)
Point A2 = (800, 800)
Point A3 = (900, 400)
Point A4 = (800, 100)

Your polygon is a hexagon B1,B2,B3,B4,B5,B6 with points:
Point B1 = (900, 0)
Point B2 = (0, 200)
Point B3 = (0, 500)
Point B4 = (100, 800)
Point B5 = (400, 900)
Point B6 = (700, 900)

```

### Custom run:
Write your name (or just press Enter for default name ```Travaler```) and then follow the print instruction

#### Console Input:
```
>>>
Please, enter your name if you wish (otherwise just press Enter): Kitsu

Greetings, Kitsu!
This program will immerse you in the wonderful world of
        Polygon Intersections!
All you need is entering the values of your two polygons...
...and take resulted intersection!

The first thing you need is to define your two polygons (1 and 2)!

Enter the number of points for the polygon A: 6
Please, enter new point A1 in '(x, y)' format: (500, 0)
Please, enter new point A2 in '(x, y)' format: (100, 100)
Please, enter new point A3 in '(x, y)' format: (0, 900)
Please, enter new point A4 in '(x, y)' format: (800, 800)
Please, enter new point A5 in '(x, y)' format: (900, 400)
Please, enter new point A6 in '(x, y)' format: (800, 100)

Enter the number of points for the polygon B: 6
Please, enter new point B1 in '(x, y)' format: (900, 0)
Please, enter new point B2 in '(x, y)' format: (0, 200)
Please, enter new point B3 in '(x, y)' format: (0, 500)
Please, enter new point B4 in '(x, y)' format: (100, 800)
Please, enter new point B5 in '(x, y)' format: (400, 900)
Please, enter new point B6 in '(x, y)' format: (700, 900)
```

#### UI output:
<img width="1440" alt="Снимок экрана 2023-06-16 в 01 49 02" src="https://github.com/GrafVonTee/triangle_intersections/assets/100523204/cdb42dc9-0d6a-4787-a3c4-10d16a30103d">


## Features
- You can change polygon coordinates in "Properties" window and new intersection will be automatically ploted.
- Navigation buttons:
  - `Add Point` - Add default point;
  - `Delete Point` - Delete current point;
  - `Revert` - Revert changes for 1 step back;

## Issues and Contributions

If you encounter any issues or want to contribute to the project, please refer to [CONTRIBUTING.md](CONTRIBUTING.md) and [SECURITY.md](SECURITY.md) for guidelines.

## License

This project is licensed under the MIT License - see the [LICENCE](LICENSE) file for details.
