#ifndef TRIANGLE_INTERSECTIONS_CALCULATEINTERSECTIONS_H
#define TRIANGLE_INTERSECTIONS_CALCULATEINTERSECTIONS_H

#include <vector>
#include <algorithm>
#include "GeometryUtils.h"
#include "StatesUtils.h"

using namespace Geometry;

namespace Math{

    //Determinant of the 2-dimensional matrix
    coord_t det(coord_t a1, coord_t a2 ,coord_t b1, coord_t b2);

    //Pushing point into vector only if it is a new point of intersection
    void push_back_unique(std::vector<Point>& list, Point& point);

    //Checking that point is locating into polygon (inside of on the border)
    bool isPointInside(Point& point, Polygon& figure);

    //Adding into vector all vertex of "internal" polygon which is locating into "external polygon"
    void addInsideVertex(std::vector<Point>& list, Polygon& internal, Polygon& external);

    //Called when we already know all points of intersection, we sort their in right to output order
    std::vector<Point> sortPoints(std::vector<Point> list);

    //Important case - it is when 2 lines not parallel and sections have intersection. If case is important, we get coords of intersection point, else we get (0,0) point
    Point findLinesInter(Point& firstStart, Point& firstEnd,\
        Point& secondStart,Point& secondEnd, bool& isImportantCase);

    //main function of math module, find intersection area
    Intersection findTriangleInter(Polygon& first, Polygon& second);

}
#endif //TRIANGLE_INTERSECTIONS_CALCULATEINTERSECTIONS_H
