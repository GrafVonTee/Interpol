#include <sstream>
#include "GeometryUtils.h"
#include "CalculateIntersections.h"
#include "Parsing.h"
#include "ConsoleInteraction.h"
#include "StatesUtils.h"

int main() {
    std::istringstream inpStream("(1,1)\n(2,2)\n(1,3)\n(1,1)\n(2,2)\n(1,3)\n");
    auto [tr1, tr2] = Interaction::getBothTriangles(inpStream);
    Interaction::printTriangle(tr1, 1);
    Interaction::printTriangle(tr2, 2);
    return 0;
}