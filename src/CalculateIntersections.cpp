#include "CalculateIntersections.h"

namespace Math {


    coord_t det(coord_t a1, coord_t a2, coord_t b1, coord_t b2) {
        return a1 * b2 - a2 * b1;
    }

    coord_t distance(Point &first, Point &second) {
        return sqrt(pow(first.getX() - second.getX(), 2) + pow(first.getY() - second.getY(), 2));
    }

    void push_back_unique(std::vector<Point> &list, Point &point) {
        if (std::find(list.begin(), list.end(), point) != list.end()) {
            list.push_back(point);
        }
    };

    void smartSwap(std::vector<Point> &list, Point &center) {
        if (list.size() == 2) {
            if (distance(list[0], center) > distance(list[1], center)) {
                Point temp = list[0];
                list[0] = list[1];
                list[1] = temp;
            }
        }
    }

    bool isPointInside(Point &point, Polygon &figure) {
        bool left, right = false;
        coord_t pointInEdge;
        for (size_t edge = 0; edge < figure.size(); edge++) {
            if (std::min(figure[edge].getY(), figure[(edge + 1) % figure.size()].getY()) <= point.getY() && \
            std::max(figure[edge].getY(), figure[(edge + 1) % figure.size()].getY()) >= point.getY()) {

            }
            if (left && right) {
                return true;
            }
        }
        return false;
    }

    Point findLinesInter(Point &firstStart, Point &firstEnd, \
        Point &secondStart, Point &secondEnd, SectionsState &state) {
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

                if (std::max(firstStart.getX(), firstEnd.getX()) < std::min(secondStart.getX(), secondEnd.getX()) || \
                 std::min(firstStart.getX(), firstEnd.getX()) > std::max(secondStart.getX(), secondEnd.getX())) {
                    state = SectionsState::NoIntersection;
                    return Point(0, 0);
                } else if (std::max(firstStart.getX(), firstEnd.getX()) <=
                           std::max(secondStart.getX(), secondEnd.getX()) && \
                std::min(firstStart.getX(), firstEnd.getX()) >= std::min(secondStart.getX(), secondEnd.getX())) {
                    state = SectionsState::FirstFullInSecond;
                    return Point(0, 0);
                } else if (std::max(firstStart.getX(), firstEnd.getX()) >=
                           std::max(secondStart.getX(), secondEnd.getX()) && \
                std::min(firstStart.getX(), firstEnd.getX()) <= std::min(secondStart.getX(), secondEnd.getX())) {
                    state = SectionsState::SecondFullInFirst;
                    return Point(0, 0);
                } else if (std::min(secondStart.getX(), secondEnd.getX()) > firstStart.getX() &&
                           firstStart.getX() < std::max(secondStart.getX(), secondEnd.getX())) {
                    state = SectionsState::StartInEndOut;
                } else if (std::min(secondStart.getX(), secondEnd.getX()) > firstEnd.getX() &&
                           firstEnd.getX() < std::max(secondStart.getX(), secondEnd.getX())) {
                    state = SectionsState::StartOutEndIn;
                } else if (firstStart.getX() == secondStart.getX() || firstStart.getX() == secondStart.getY()) {
                    state = SectionsState::Dot;
                    return firstStart;
                } else {
                    state = SectionsState::Dot;
                    return firstEnd;
                }

            } else {
                state = SectionsState::NoIntersection;
                return Point(0, 0);
            }

        } else {
            interX = tSecondY * b1 - tFirstY * b2;
            interY = tFirstX * b2 - tSecondX * b1;
            if (interX >= 0 && interY <= 1 && interY >= 0 && interY <= 1) {
                return Point(tFirstX * interX, tFirstX * interY);
            } else {
                state = SectionsState::NoIntersection;
                return Point(0, 0);
            }
        }
    }

    Polygon findTriangleInter(Polygon &first, Polygon &second) {
        std::vector<Point> listOfInterPoints;
        Point newPoint;
        SectionsState state{SectionsState::NoIntersection};
        for (size_t firstPoint = 0; firstPoint <= 2; firstPoint++) {
            std::vector<Point> intermediateList;
            for (size_t secondPoint = 0; secondPoint <= 2; secondPoint++) {
                newPoint = findLinesInter(first[firstPoint], first[(firstPoint + 1) % 3], second[secondPoint],
                                          second[(secondPoint + 1) % 3], state);
                switch (state) {
                    case SectionsState::Dot: {
                        push_back_unique(intermediateList, newPoint);
                    }
                        break;
                    case SectionsState::FirstFullInSecond: {
                        push_back_unique(intermediateList, first[firstPoint]);
                        push_back_unique(intermediateList, first[(firstPoint + 1) % 3]);
                    }
                        break;
                    case SectionsState::SecondFullInFirst: {
                        push_back_unique(intermediateList, second[secondPoint]);
                        push_back_unique(intermediateList, second[(secondPoint + 1) % 3]);
                    }
                        break;
                    case SectionsState::StartInEndOut: {
                        push_back_unique(intermediateList, first[firstPoint]);
                        push_back_unique(intermediateList, newPoint);
                    }
                        break;
                    case SectionsState::StartOutEndIn: {
                        push_back_unique(intermediateList, first[(firstPoint + 1) % 3]);
                        push_back_unique(intermediateList, newPoint);
                    }
                        break;
                }
                state = SectionsState::NoIntersection;
            }
            if (intermediateList.size() == 1 && !(listOfInterPoints.empty()) &&
                first[firstPoint] != listOfInterPoints[listOfInterPoints.size()])
                smartSwap(intermediateList, first[firstPoint]);
            for (size_t elem = 0; elem < intermediateList.size(); elem++) {
                push_back_unique(listOfInterPoints, intermediateList[elem]);
            }
        }
        if (listOfInterPoints.size() == 0) {

        }
        return Polygon(listOfInterPoints);
    }
}

