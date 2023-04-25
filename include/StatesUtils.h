#ifndef TRIANGLE_INTERSECTIONS_STATESUTILS_H
#define TRIANGLE_INTERSECTIONS_STATESUTILS_H

namespace States {
    enum class InputState {
        IncorrectInput,
        IncorrectFormat,
        NegativeNumbers,
        Correct
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