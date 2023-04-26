#ifndef TRIANGLE_INTERSECTIONS_CALCULATEINTERSECTIONS_H
#define TRIANGLE_INTERSECTIONS_CALCULATEINTERSECTIONS_H

#include <vector>
#include "GeometryUtils.h"
#include "StatesUtils.h"

using namespace Geometry;

namespace Math{

    coord_t det(coord_t a1, coord_t a2 ,coord_t b1, coord_t b2);

    Point findLinesInter(Point& firstStart, Point& firstEnd,\
        Point& secondStart,Point& secondEnd, States::IntersectionState& state);

    Polygon findTriangleInter(Polygon& first, Polygon& second);

}
#endif //TRIANGLE_INTERSECTIONS_CALCULATEINTERSECTIONS_H
