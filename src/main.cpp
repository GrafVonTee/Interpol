#include <sstream>
#include <cstdlib>
#include "DrawImage.h"
#include "CalculateIntersections.h"
#include "Parsing.h"
#include "ConsoleInteraction.h"
#include "GetImVecFromPolygon.h"

int main() {
    std::string userName = Interaction::getUserName();
    Interaction::greeting(userName);    
    std::istringstream demoPoints("(20.0, 90.0)\n(20.0, 20.0)\n(90.0, 10.0)\n(10.0, 80.0)\n(50.0, 30.0)\n(70.0, 50.0)\n");

    std::istream *input = &std::cin;

    if ((userName == "Demo")||(userName == "demo")){
        input = &demoPoints;
    }

    auto [tr1, tr2] = Interaction::getBothTriangles(*input);
    Interaction::printTriangle(tr1, 1);
    Interaction::printTriangle(tr2, 2);

    auto intersection = Math::findTriangleInter(tr1, tr2);
    Interaction::printIntersection(intersection);

    auto [a1, a2, a3] = DrawUtils::getTupleOfPointsFromPolygon(tr1);
    auto [b1, b2, b3] = DrawUtils::getTupleOfPointsFromPolygon(tr2);
    auto intersectionPoints = DrawUtils::getVectorOfPointsFromPolygon(intersection.polygon);

    double scale_x, scale_y, delta_x, delta_y, min_x, min_y;

    DrawUtils::findParameters(a1, a2, a3, b1, b2, b3, DrawUtils::SquareSideSize,
                              scale_x, scale_y, delta_x, delta_y, min_x, min_y);
    DrawUtils::scaleAndTranslate(a1, a2, a3, b1, b2, b3, intersectionPoints,
                                 scale_x, scale_y, delta_x, delta_y, min_x, min_y);
    DrawUtils::addIndents(a1, a2, a3,
                          b1, b2, b3,
                          intersectionPoints,
                          DrawUtils::IndentSize);

    Interaction::welcomeToGui();
    DrawOutput::draw_triangles_and_intersection(
            a1, a2, a3,
            b1, b2, b3,
            intersectionPoints
    );

    Interaction::goodbye(userName);
    system("pause");

    return 0;
}