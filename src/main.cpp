#include "DrawImage.h"
#include "CalculateIntersections.h"
#include "Parsing.h"
#include "ConsoleInteraction.h"
#include "GetImVecFromPolygon.h"

int main() {
    std::string userName = Interaction::getUserName();
    Interaction::greeting(userName);

    auto [tr1, tr2] = Interaction::getBothTriangles();
    Interaction::printTriangle(tr1, 1);
    Interaction::printTriangle(tr2, 2);

    auto intersection = Math::findTriangleInter(tr1, tr2);
    Interaction::printIntersection(intersection);

    auto [a1, a2, a3] = DrawUtils::getTupleFromPolygon(tr1);
    auto [b1, b2, b3] = DrawUtils::getTupleFromPolygon(tr2);
    auto intersectionPoints = DrawUtils::getVectorFromPolygon(intersection.polygon);

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

    return 0;
}