#include "CalculateIntersections.h"

namespace Math {


    coord_t det(coord_t a1, coord_t a2, coord_t b1, coord_t b2) {
        return a1 * b2 - a2 * b1;
    }

    void push_back_unique(std::vector<Point> &list, Point &point) {
        if (std::find(list.begin(), list.end(), point) == list.end()) {
            list.push_back(point);
        }
    };

    bool isPointInside(Point &point, Polygon &figure) {

        using std::min, std::max;

        bool left = false, right = false;
        coord_t k;
        coord_t X0, dY, interX;

        for (size_t edge = 0; edge < figure.size(); edge++) {

            if (figure[edge].getY() == point.getY() && figure[(edge + 1) % figure.size()].getY() == point.getY()) {
                return false;
            }

            if (min(figure[edge].getY(), figure[(edge + 1) % figure.size()].getY()) <= point.getY() && \
            max(figure[edge].getY(), figure[(edge + 1) % figure.size()].getY()) >= point.getY()) {

                if (figure[edge].getX() - figure[(edge + 1) % figure.size()].getX() == 0) {

                    if (figure[edge].getX() <= point.getX()) {
                        left = true;
                    } else if (figure[edge].getX() >= point.getX()) {
                        right = true;
                    }

                } else {

                    k = (figure[(edge + 1) % figure.size()].getX() - figure[edge].getX()) /
                        (figure[(edge + 1) % figure.size()].getY() - figure[edge].getY());
                    if (figure[edge].getY() ==
                        min(figure[edge].getY(), figure[(edge + 1) % figure.size()].getY())) {
                        X0 = figure[edge].getX();
                        dY = point.getY() - figure[edge].getY();
                    } else {
                        X0 = figure[(edge + 1) % figure.size()].getX();
                        dY = point.getY() - figure[(edge + 1) % figure.size()].getY();
                    }
                    interX = X0 + k * dY;
                    if (interX <= point.getX()) {
                        left = true;
                    } else if (interX >= point.getX()) {
                        right = true;
                    }
                }
            }
            if (left && right) {
                return true;
            }
        }
        return false;
    }

    void addInsideVertex(std::vector<Point> &list, Polygon &internal, Polygon &external) {
        for (size_t vertex = 0; vertex < internal.size(); vertex++) {

            if (isPointInside(internal[vertex], external)) {
                push_back_unique(list, internal[vertex]);
            }

        }
    }

    std::vector<Point> sortPoints(std::vector<Point> list) {

        std::vector<Point> result;
        std::vector<Point> remnant = list;
        result.push_back(remnant[0]);
        remnant.erase(remnant.begin());
        size_t n = remnant.size();
        bool rightEdge;
        bool notARightPoint = false;

        for (size_t iter = 0; iter < n; iter++) {

            for (size_t checkingPoint = 0; checkingPoint < n - iter; checkingPoint++) {

                rightEdge = true;

                for (size_t startEdge = 0; startEdge < list.size(); startEdge++) {

                    if (!rightEdge) {
                        break;
                    }

                    for (size_t endEdge = 0; endEdge < list.size(); endEdge++) {

                        if (startEdge != endEdge && list[startEdge] != result[iter] &&
                            list[startEdge] != remnant[checkingPoint] && \
                        list[endEdge] != result[iter] && list[endEdge] != remnant[checkingPoint]) {

                            findLinesInter(result[iter], remnant[checkingPoint], list[startEdge], list[endEdge],
                                           notARightPoint);

                            if (notARightPoint) {
                                notARightPoint = false;
                                rightEdge = false;
                                break;

                            }

                        }

                    }

                }

                if (rightEdge) {
                    result.push_back(remnant[checkingPoint]);
                    remnant.erase(remnant.begin() + checkingPoint);
                    break;

                }
            }
        }
        return result;
    }

    Point findLinesInter(Point &firstStart, Point &firstEnd, \
         Point &secondStart, Point &secondEnd, bool &isImportantCase) {

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
            isImportantCase = false;
            return Point(0, 0);
        } else {

            interX = (tSecondY * b1 - tSecondX * b2) / determinant;
            interY = (tFirstX * b2 - tFirstY * b1) / determinant;

            if (interX >= 0 && interX <= 1 && interY >= 0 && interY <= 1) {
                isImportantCase = true;
                return Point(tFirstX * interX + firstStart.getX(), tFirstY * interX + firstStart.getY());
            } else {
                isImportantCase = false;
                return Point(0, 0);
            }

        }
    }

    Intersection findTriangleInter(Polygon &first, Polygon &second) {

        std::vector<Point> listOfInterPoints;
        Point newPoint;

        addInsideVertex(listOfInterPoints, first, second);

        if (listOfInterPoints.size() == 3) {

            bool match;

            for (size_t pointNumber = 0; pointNumber < 3; pointNumber++) {
                match = false;

                for (size_t vertexOfSecond = 0; vertexOfSecond < 3; vertexOfSecond++) {

                    if (first[vertexOfSecond] == second[pointNumber]) {
                        match = true;
                        continue;
                    }

                }

                if (!match) {
                    return Intersection{States::IntersectionState::Nested, Polygon(listOfInterPoints)};
                }

            }
            return Intersection{States::IntersectionState::Matched, second};
        }

        bool nestedFlag = listOfInterPoints.empty();

        addInsideVertex(listOfInterPoints, second, first);

        if (nestedFlag && listOfInterPoints.size() == 3) {
            return Intersection{States::IntersectionState::Nested, first};
        }

        bool isImportantCase = false;

        for (size_t firstEdge = 0; firstEdge <= 2; firstEdge++) {

            for (size_t secondEdge = 0; secondEdge <= 2; secondEdge++) {

                newPoint = findLinesInter(first[firstEdge], first[(firstEdge + 1) % 3], second[secondEdge],
                                          second[(secondEdge + 1) % 3], isImportantCase);

                if (isImportantCase) {
                    push_back_unique(listOfInterPoints, newPoint);
                    isImportantCase = false;
                }

            }

        }

        if (listOfInterPoints.empty()) {
            return Intersection{States::IntersectionState::NoIntersection, Polygon(listOfInterPoints)};
        }

        if (listOfInterPoints.size() > 3) {
            listOfInterPoints = sortPoints(listOfInterPoints);
        }

        return Intersection{States::IntersectionState::Polygon, Polygon(listOfInterPoints)};
    }

}
