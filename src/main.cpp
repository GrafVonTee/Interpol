#include <sstream>
#include "DrawImage.h"
#include "CalculateIntersections.h"
#include "Parsing.h"
#include "ConsoleInteraction.h"
#include "GetImVecFromPolygon.h"
#include "ConstantsForDrawing.h"

int main() {
    std::string userName = Interaction::getUserName();
    Interaction::greeting(userName);
    std::istringstream demoPoints("(20.0, 90.0)\n(20.0, 20.0)\n(90.0, 10.0)\n(10.0, 80.0)\n(50.0, 30.0)\n(70.0, 50.0)\n");
    std::ostringstream empty;

    std::istream *input = &std::cin;
    std::ostream *output = &std::cout;

    if ((userName == "Demo")||(userName == "demo")){
        input = &demoPoints;
        output = &empty;
    }

    auto [tr1, tr2] = Interaction::getBothTriangles(*input, *output);
    auto intersection = Math::findTriangleInter(tr1, tr2);
    DrawUtils::setActualPointsLabels(tr1, tr2, intersection);

    Interaction::printTriangle(tr1);
    Interaction::printTriangle(tr2);
    Interaction::printIntersection(intersection);

    double scale_x, scale_y, delta_x, delta_y, min_x, min_y;

    DrawUtils::findParameters(tr1, tr2, DrawConst::SquareSideSize,
                              scale_x, scale_y, delta_x, delta_y, min_x, min_y);
    DrawUtils::scaleAndTranslate(tr1, tr2, intersection,
                                 scale_x, scale_y, delta_x, delta_y, min_x, min_y);
    DrawUtils::addIndents(tr1, tr2, intersection,
                          DrawConst::IndentSize);

    Interaction::welcomeToGui();
    DrawOutput::draw_triangles_and_intersection(tr1, tr2, intersection);

    Interaction::goodbye(userName);
    system("pause");

    return 0;
}