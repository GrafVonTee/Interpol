#include "CalculateIntersections.h"

namespace Math {
    using namespace Geometry;

    // Determinant of 2*2 matrix

    coord_t det(coord_t a1, coord_t a2, coord_t b1, coord_t b2) {
        return a1 * b2 - a2 * b1;
    }

    // Add the element into vector if this element is unique in vector

    void pushBackUnique(std::vector<Point> &list, const Point &point) {
        if (std::find(list.begin(), list.end(), point) == list.end())
            list.push_back(point);
    }

    bool isPointInside(const Point &point, const Polygon &figure) {

        using std::min, std::max;

        // If point located inside polygon, the horizontal line through this point must intersect any edge left and right.
        // Only if we had and left, and right intersection with any edge, we had the situation, that point located into polygon.

        bool left = false, right = false;
        coord_t k;
        coord_t X0, dY, interX;

        for (size_t numP = 0; numP < figure.size(); numP++) {

            // We are considering the edge only if this edge has an intersection with horizontal line, built through our point.

            if (min(figure[numP].getY(), figure[(numP + 1) % figure.size()].getY()) <= point.getY() &&
                max(figure[numP].getY(), figure[(numP + 1) % figure.size()].getY()) >= point.getY()) {

                if (figure[numP].getY() - figure[(numP + 1) % figure.size()].getY() == 0)

                    // If our point and one edge of polygon are located in one horizontal line, we return true.
                    // (If point is located between vertex, that are bounding this edge).

                    // In another case, we return true, because the point not belongs to the edge.

                    return (figure[numP].getX() - point.getX()) *
                           (figure[(numP + 1) % figure.size()].getX() - point.getX()) == (-1);
                else {

                    // In this block, we find the point of horizontal line and one of the edge intersections.
                    // If this point on the left side from point, we establish that we have left intersection.
                    // Also with the right side.

                    k = (figure[(numP + 1) % figure.size()].getX() - figure[numP].getX()) /
                        (figure[(numP + 1) % figure.size()].getY() - figure[numP].getY());

                    if (figure[numP].getY() == min(figure[numP].getY(), figure[(numP + 1) % figure.size()].getY())) {
                        X0 = figure[numP].getX();
                        dY = point.getY() - figure[numP].getY();
                    }
                    else {
                        X0 = figure[(numP + 1) % figure.size()].getX();
                        dY = point.getY() - figure[(numP + 1) % figure.size()].getY();
                    }

                    interX = X0 + k * dY;

                    if (interX == point.getX())
                        return true;

                    if (interX <= point.getX())
                        left = true;
                    else if (interX >= point.getX())
                        right = true;
                }
            }

            // If we find all sides, we return true
            if (left && right)
                return true;
        }
        return false;
    }

    // We take first triangle (internal) and add into vector all vertexes, that located into second triangle (external)

    void addInsideVertex(std::vector<Point> &list, const Polygon &internal, const Polygon &external) {
        for (size_t vertex = 0; vertex < internal.size(); vertex++)
            if (isPointInside(internal[vertex], external))
                pushBackUnique(list, internal[vertex]);
    }


    LineIntersection findLinesInter(Point &firstStart, Point &firstEnd,
                        Point &secondStart, Point &secondEnd) {

        // We define a lot of variables, that are used a linear algebra's part of code (we solve the system linear equations).

        const coord_t
            tFirstX {firstEnd.getX() - firstStart.getX()},
            tFirstY {firstEnd.getY() - firstStart.getY()},
            tSecondX {-(secondEnd.getX() - secondStart.getX())},
            tSecondY {-(secondEnd.getY() - secondStart.getY())},
            b1 {secondStart.getX() - firstStart.getX()},
            b2 {secondStart.getY() - firstStart.getY()};

        const coord_t determinant = det(tFirstX, tSecondX, tFirstY, tSecondY);

        coord_t interX, interY;

        // The case, when the determinant is zero, doesn't interest us
        if (determinant == 0) {
            return LineIntersection{Point{0, 0}, false};
        }
        else {

            // If determinant doesn't equal zero, the lines intersect.
            // In this case, we are finding the point of intersection and checking, that this point belongs to our sections of these lines.

            interX = (tSecondY * b1 - tSecondX * b2) / determinant;
            interY = (tFirstX * b2 - tFirstY * b1) / determinant;

            if (interX >= 0 && interX <= 1 && interY >= 0 && interY <= 1) {
                return LineIntersection{Point{tFirstX * interX + firstStart.getX(), tFirstY * interX + firstStart.getY()}, true};
            }
            else {
                return LineIntersection{Point{0, 0}, true};
            }
        }
    }

    Intersection findTriangleInter(Polygon &first, Polygon &second) {

        // In this function we find all points, which are the vertexes of intersection polygon, and add their into <listOfInterPoints> vector.
        // We add the point only if this point is new in vector (we must avoid the duplication of intersection polygon vertexes).

        // The set of such points consists of two types of points:
        // 1. Points, that are the points of edge intersections.
        // 2. Points, that are vertexes in one of the triangles and contain in another triangle.

        // At the beginning, we find the second type of points and return, if one triangle is nested into another or triangles are matching.

        // Then we find all point of edges intersections, and if <listOfInterPoints> vector is empty, return that there isn't any intersection.
        // If this vector isn't empty, we return that the intersection is a polygon (it is the most general case of intersection).

        std::vector<Point> listOfInterPoints;

        addInsideVertex(listOfInterPoints, first, second);

        // Checking the case, when triangles are matching.

        if (listOfInterPoints.size() == 3) {

            // The boolean, that describes triangles are matching or not.

            bool match;

            for (size_t pointNumber = 0; pointNumber < 3; pointNumber++) {
                match = false;

                for (size_t vertexOfSecond = 0; vertexOfSecond < 3; vertexOfSecond++) {
                    if (first[vertexOfSecond] == second[pointNumber]) {
                        match = true;
                        break;
                    }
                }

                // In this case, we have that all vertexes of the one triangle located into another triangle and triangles are not matching.
                // So one triangle is nested into another.

                if (!match)
                    return Intersection{States::IntersectionState::Nested, Polygon(listOfInterPoints)};
            }
            return Intersection{States::IntersectionState::Matched, second};
        }

        bool nestedFlag = listOfInterPoints.empty();

        addInsideVertex(listOfInterPoints, second, first);

        if (nestedFlag && listOfInterPoints.size() == 3)
            return Intersection{States::IntersectionState::Nested, Polygon(listOfInterPoints)};

        // Find all point of edges intersections
        LineIntersection inter;

        for (size_t firstEdge = 0; firstEdge <= 2; firstEdge++) {
            for (size_t secondEdge = 0; secondEdge <= 2; secondEdge++) {

                inter = findLinesInter(first[firstEdge], first[(firstEdge + 1) % 3],
                                          second[secondEdge],second[(secondEdge + 1) % 3]);

                if (inter.isImportantCase) {
                    pushBackUnique(listOfInterPoints, inter.point);
                }
            }
        }

        if (listOfInterPoints.empty())
            return Intersection{States::IntersectionState::NoIntersection, Polygon(listOfInterPoints)};

        return Intersection{States::IntersectionState::Polygon, Polygon(listOfInterPoints)};
    }
}