#ifndef TRIANGLE_INTERSECTIONS_STATESUTILS_H
#define TRIANGLE_INTERSECTIONS_STATESUTILS_H

namespace States {
    enum class InputState {
        IncorrectInput,
        EmptyString,
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
        OtherPolygon,
        AllStates,
    };

    enum class IntersectionState {
        NoIntersection,
        Nested,
        Matched,
        Polygon
    };
}
#endif // TRIANGLE_INTERSECTIONS_STATESUTILS_H