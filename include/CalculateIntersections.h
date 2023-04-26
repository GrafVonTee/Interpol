#ifndef TRIANGLE_INTERSECTIONS_CALCULATEINTERSECTIONS_H
#define TRIANGLE_INTERSECTIONS_CALCULATEINTERSECTIONS_H

#include <vector>
#include <math.h>
#include "GeometryUtils.h"
#include "StatesUtils.h"

using namespace Geometry;

namespace Math{

    enum class SectionsState{
        NoIntersection,
        Dot,
        FirstFullInSecond,
        SecondFullInFirst,
        StartInEndOut,
        StartOutEndIn
    };

    coord_t det(coord_t a1, coord_t a2 ,coord_t b1, coord_t b2);

    coord_t d(Point& first,Point& second);

    void push_back_unique(std::vector<Point>& list, Point& point);

    void smartSwap(std::vector<Point>& list);

    bool isPointInside(Point& point, Polygon& figure);

    Point findLinesInter(Point& firstStart, Point& firstEnd,\
        Point& secondStart,Point& secondEnd, SectionsState& state);

    Polygon findTriangleInter(Polygon& first, Polygon& second);

}
#endif //TRIANGLE_INTERSECTIONS_CALCULATEINTERSECTIONS_H
