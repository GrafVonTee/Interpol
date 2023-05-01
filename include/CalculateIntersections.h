#ifndef TRIANGLE_INTERSECTIONS_CALCULATEINTERSECTIONS_H
#define TRIANGLE_INTERSECTIONS_CALCULATEINTERSECTIONS_H

#include <vector>
#include <algorithm>
#include <cmath>
#include "GeometryUtils.h"
#include "StatesUtils.h"


namespace Math{

    // Determinant of the 2-dimensional matrix
    coord_t det(coord_t a1, coord_t a2 ,coord_t b1, coord_t b2);

    // Pushing point into vector only if it is a new point of intersection
    void pushBackUnique(std::vector<Geometry::Point>& list, Geometry::Point& point);

    // Checking that point is locating into polygon (inside of on the border)
    bool isPointInside(Geometry::Point& point, Geometry::Polygon& figure);

    // Adding into vector all vertex of "internal" polygon which is locating into "external polygon"
    void addInsideVertex(std::vector<Geometry::Point>& list, Geometry::Polygon& internal, Geometry::Polygon& external);

    // Important case - it is when 2 lines not parallel and sections have intersection. If case is important, we get coords of intersection point, else we get (0,0) point
    Geometry::Point findLinesInter(Geometry::Point& firstStart, Geometry::Point& firstEnd,\
        Geometry::Point& secondStart,Geometry::Point& secondEnd, bool& isImportantCase);

    // Main function of math module, find intersection area
    Geometry::Intersection findTriangleInter(Geometry::Polygon& first, Geometry::Polygon& second);

}
#endif //TRIANGLE_INTERSECTIONS_CALCULATEINTERSECTIONS_H
