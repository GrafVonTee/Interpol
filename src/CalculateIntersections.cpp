#include "CalculateIntersections.h"

namespace Math {

    coord_t det(coord_t a1, coord_t a2, coord_t b1, coord_t b2) {
        return a1 * b2 - a2 * b1;
    }


    Point findLinesInter(Point firstStart, Point firstEnd,\
        Point secondStart,Point secondEnd,  States::IntersectionState& state) {
        coord_t tFirstX, tFirstY, tSecondX, tSecondY, b1, b2;
        coord_t interX, interY;
        tFirstX = firstEnd.getX() - firstStart.getX();
        tFirstY = firstEnd.getY() - firstStart.getY();
        tSecondX = -(secondEnd.getX() - secondStart.getX());
        tSecondY = -(secondEnd.getY() - secondStart.getY());
        b1 = secondStart.getX() - firstStart.getX();
        b2 = secondStart.getY() - firstStart.getY();
        coord_t determinant = det(tFirstX, tSecondX, tFirstY, tSecondY);
        if (determinant == 0) {
            if (b1 == b2) {
                if (firstEnd.getX() >= secondStart.getX() || firstStart.getX() <= secondEnd.getX()) {
                    if (firstEnd.getX() == secondStart.getX()) {
                        return Point(firstEnd.getX(), firstEnd.getY());
                    }
                    if (firstStart.getX() == secondEnd.getX()) {
                        return Point(firstStart.getX(), firstStart.getY());
                    }
                } else {
                    return Point(0, 0);
                }
            } else {
                state = States::IntersectionState::NoIntersection;
                return Point(0, 0);
            }
        } else {
            interX = tSecondY * b1 - tFirstY * b2;
            interY = tFirstX * b2 - tSecondX * b1;
            if (interX >= 0 && interY <= 1 && interY >= 0 && interY <= 1) {
                return Point(interX, interY);
            } else {
                state = States::IntersectionState::NoIntersection;
                return Point(0, 0);
            }
        }
    }
    Polygon findTriangleInter(Polygon& first, Polygon& second) {
        for (int dot = 0; dot<=2; dot++){

        }
        return Polygon();
    }
}

