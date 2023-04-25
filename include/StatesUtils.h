#ifndef TRIANGLE_INTERSECTIONS_STATESUTILS_H
#define TRIANGLE_INTERSECTIONS_STATESUTILS_H

namespace States {
    enum class InputState {
        IncorrectInput,
        IncorrectFormat,
        NegativeNumbers
    };

    enum class IntersectionState {
        Point,
        Edge,
        Triangle,
        Polygon,
        NoIntersection
    };

    enum class UnitTestState {
        // TODO
    };
}
#endif // TRIANGLE_INTERSECTIONS_STATESUTILS_H