#include <sstream>
#include "DrawImage.h"
#include "CalculateIntersections.h"
#include "Parsing.h"
#include "ConsoleInteraction.h"
#include "GetImVecFromPolygon.h"

int main() {
    std::string userName = Interaction::getUserName();
    Interaction::greeting(userName);
    std::istringstream demoPoints("(200.0, 900.0)\n(200.0, 200.0)\n(900.0, 100.0)\n(100.0, 800.0)\n(500.0, 300.0)\n(700.0, 500.0)\n");
    std::ostringstream empty;

    std::istream *input = &std::cin;
    std::ostream *output = &std::cout;

    if ((userName == "Demo") || (userName == "demo")) {
        input = &demoPoints;
        output = &empty;
    }

    auto [p1, p2] = Interaction::getBothPolygons(*input, *output);
    auto intersection = Math::findPolygonsInter(p1, p2);
    DrawUtils::setActualPointsLabels(p1, p2, intersection);

    Interaction::printPolygon(p1);
    Interaction::printPolygon(p2);
    Interaction::printIntersection(intersection);


    Interaction::welcomeToGui();
    DrawOutput::draw_triangles_and_intersection(p1, p2, intersection);

    Interaction::goodbye(userName);
    system("pause");

    return 0;
}