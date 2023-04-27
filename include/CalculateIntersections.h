#ifndef TRIANGLE_INTERSECTIONS_CALCULATEINTERSECTIONS_H
#define TRIANGLE_INTERSECTIONS_CALCULATEINTERSECTIONS_H

#include <vector>
#include <math.h>
#include "GeometryUtils.h"
#include "StatesUtils.h"

using namespace Geometry;

namespace Math{

    coord_t det(coord_t a1, coord_t a2 ,coord_t b1, coord_t b2);

    void push_back_unique(std::vector<Point>& list, Point& point);

    bool isPointInside(Point& point, Polygon& figure);

    void addInsideVertex(std::vector<Point>& list, Polygon& internal, Polygon& external);

    std::vector<Point> sortPoints(std::vector<Point> list);

    Point findLinesInter(Point& firstStart, Point& firstEnd,\
        Point& secondStart,Point& secondEnd, bool& isImportantCase);

    Intersection findTriangleInter(Polygon& first, Polygon& second);

}
#endif //TRIANGLE_INTERSECTIONS_CALCULATEINTERSECTIONS_H
