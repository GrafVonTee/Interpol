#include "CalculateIntersections.h"

namespace Math {


    coord_t det(coord_t a1, coord_t a2, coord_t b1, coord_t b2) {
        return a1 * b2 - a2 * b1;
    }

    coord_t distance(Point &first, Point &second) {
        return sqrt(pow(first.getX() - second.getX(), 2) + pow(first.getY() - second.getY(), 2));
    }

    void push_back_unique(std::vector<Point> &list, Point &point) {
        if (std::find(list.begin(), list.end(), point) == list.end()) {
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

    bool isPointInside(Point& point, Polygon &figure) {
        bool left = false, right = false;
        coord_t k;
        coord_t X0, dY, interX;
        for (size_t edge = 0; edge < figure.size(); edge++) {
            if (figure[edge].getY() == point.getY() && figure[(edge + 1) % figure.size()].getY() == point.getY()){
                return false;
            }
            if (std::min(figure[edge].getY(), figure[(edge + 1) % figure.size()].getY()) <= point.getY() && \
            std::max(figure[edge].getY(), figure[(edge + 1) % figure.size()].getY()) >= point.getY()) {
                if (figure[edge].getX() - figure[(edge + 1) % figure.size()].getX()==0){
                    if (figure[edge].getX()<point.getX()){
                        left=true;
                    }
                    else if (figure[edge].getX()>point.getX()){
                        right=true;
                    }
                }
                else{
                    k=(figure[(edge + 1) % figure.size()].getX()-figure[edge].getX())/(figure[(edge + 1) % figure.size()].getY()-figure[edge].getY());
                    if (figure[edge].getY()==std::min(figure[edge].getY(), figure[(edge + 1) % figure.size()].getY())){
                        X0 = figure[edge].getX();
                        dY = point.getY() - figure[edge].getY();
                    }
                    else{
                        X0=figure[(edge + 1) % figure.size()].getX();
                        dY = point.getY() - figure[(edge + 1) % figure.size()].getY();
                    }
                    interX=X0+k*dY;
                    if (interX < point.getX()){
                        left = true;
                    }
                    else if (interX > point.getX()){
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

            if (tFirstX/tFirstY == b1/b2) {

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
                } else if (std::min(secondStart.getX(), secondEnd.getX()) < firstStart.getX() &&
                           firstStart.getX() < std::max(secondStart.getX(), secondEnd.getX())) {
                    state = SectionsState::StartInEndOut;
                    if (std::min(firstStart.getX(), firstEnd.getX())<secondStart.getX() &&  std::max(firstStart.getX(), firstEnd.getX())>secondStart.getX()){
                        return secondStart;
                    }
                    else {
                        return secondEnd;
                    }
                } else if (std::min(secondStart.getX(), secondEnd.getX()) < firstEnd.getX() &&
                           firstEnd.getX() < std::max(secondStart.getX(), secondEnd.getX())) {
                    state = SectionsState::StartOutEndIn;
                    if (std::min(firstStart.getX(), firstEnd.getX())<secondStart.getX() &&  std::max(firstStart.getX(), firstEnd.getX())>secondStart.getX()){
                        return secondStart;
                    }
                    else {
                        return secondEnd;
                    }
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

        }
        else {
            interX = (tSecondY * b1 - tSecondX * b2)/determinant;
            interY = (tFirstX * b2 - tFirstY * b1)/determinant;
            if (interX >= 0 && interX <= 1 && interY >= 0 && interY <= 1) {
                state = SectionsState::Dot;
                return Point(tFirstX * interX+firstStart.getX(), tFirstY * interX+firstStart.getY());
            } else {
                state = SectionsState::NoIntersection;
                return Point(0, 0);
            }
        }
    }

    Intersection findTriangleInter(Polygon &first, Polygon &second) {
        std::vector<Point> listOfInterPoints;
        std::vector<Point> insidePointsOfDinamic;
        for (size_t vertex = 0; vertex <= 2; vertex++){
            if (isPointInside(second[vertex], first)){
                insidePointsOfDinamic.push_back(second[vertex]);
            }
        }
        if (insidePointsOfDinamic.size()==3){
            return Intersection{States::IntersectionState::Nested, Polygon(insidePointsOfDinamic)};
        }
        if (insidePointsOfDinamic.size()==2){

        }
        Point newPoint;
        SectionsState state{SectionsState::NoIntersection};

        for (size_t firstPoint = 0; firstPoint <= 2; firstPoint++) {
            if (isPointInside(first[firstPoint],second)){
                push_back_unique(listOfInterPoints,first[firstPoint]);
            }
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
            if (intermediateList.size() == 2)
                smartSwap(intermediateList, first[firstPoint]);
            for (size_t elem = 0; elem < intermediateList.size(); elem++) {
                push_back_unique(listOfInterPoints, intermediateList[elem]);
            }
        }
        if (insidePointsOfDinamic.size()==1){

        }
        if (listOfInterPoints.size()==2) {
            for (size_t pointNumber=0;pointNumber<3; pointNumber++) {
                if (!isPointInside(first[pointNumber], second)) {
                    return Intersection{States::IntersectionState::Polygon, Polygon(listOfInterPoints)};
                }
            }
            bool match;
            for (size_t pointNumber=0;pointNumber<3; pointNumber++) {
                match=false;
                for (size_t vertexOfSecond=0;vertexOfSecond<3; vertexOfSecond++){
                    if (second[vertexOfSecond]==first[pointNumber]){
                        match=true;
                        continue;
                    }
                }
                if (!match){
                    return Intersection{States::IntersectionState::Polygon,Polygon(listOfInterPoints)};
                }
            }
            return Intersection{States::IntersectionState::Matched,Polygon(listOfInterPoints)};
        }
        std::cout<<listOfInterPoints.size();
        return Intersection{States::IntersectionState::Polygon,Polygon(listOfInterPoints)};
    }
}

