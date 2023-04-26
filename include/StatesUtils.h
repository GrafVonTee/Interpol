#ifndef TRIANGLE_INTERSECTIONS_STATESUTILS_H
#define TRIANGLE_INTERSECTIONS_STATESUTILS_H

namespace States {
    enum class InputState {
        IncorrectInput,
        IncorrectFormat,
        NegativeNumbers,
        Correct
    };

    enum class PolygonState {
        NotPolygon = 0,
        Point = 1,
        Edge = 2,
        Triangle = 3,
        Quadrilateral = 4,
        Pentagon = 5,
        Hexagon = 6,
    };

    enum class IntersectionState {
        Point,
        Edge,
        Polygon,
        Matched,
        Nested,
        NoIntersection
    };

    enum class UnitTestState {
        // TODO
    };
}
#endif // TRIANGLE_INTERSECTIONS_STATESUTILS_H