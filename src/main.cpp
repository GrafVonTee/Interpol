#include <sstream>
#include "DrawImage.h"
#include "CalculateIntersections.h"
#include "Parsing.h"
#include "ConsoleInteraction.h"
#include "GetImVecFromPolygon.h"

int main() {
    std::string userName = Interaction::getUserName();
    Interaction::greeting(userName);    
    std::istringstream demoPoints("(300.0, 400.0)\n(100.0, 200.0)\n(100.0, 400.0)\n(100.0, 500.0)\n(100.0, 100.0)\n(500.0, 100.0)\n");

    std::istream *input = &std::cin;

    if ((userName == "Demo")||(userName == "demo")){
        input = &demoPoints;
    }

    auto [tr1, tr2] = Interaction::getBothTriangles(*input);
    Interaction::printTriangle(tr1, 1);
    Interaction::printTriangle(tr2, 2);

    auto intersection = Math::findTriangleInter(tr1, tr2);
    Interaction::printIntersection(intersection);

    auto [a1, a2, a3] = DrawUtils::getTupleFromPolygon(tr1);
    auto [b1, b2, b3] = DrawUtils::getTupleFromPolygon(tr2);
    auto intersectionPoints = DrawUtils::getVectorFromPolygon(intersection.polygon);

    Interaction::welcomeToGui();
    DrawOutput::draw_triangles_and_intersection(
            a1, a2, a3,
            b1, b2, b3,
            intersectionPoints
    );

    Interaction::goodbye(userName);

    return 0;
}