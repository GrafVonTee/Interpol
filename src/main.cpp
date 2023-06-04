#include <sstream>
#include "DrawImage.h"
#include "Parsing.h"
#include "ConsoleInteraction.h"
#include "GetImVecFromPolygon.h"
#include "StatesLibrary.h"

const std::string hexAndHex = std::string("6\n")
                                          + "(0, 900.0)\n"
                                          + "(800.0, 800.0)\n"
                                          + "(900.0, 400.0)\n"
                                          + "(800.0, 100.0)\n"
                                          + "(500.0, 0)\n"
                                          + "(100.0, 100.0)\n"
                                          + "6\n"
                                          + "(900.0, 0)\n"
                                          + "(0, 200.0)\n"
                                          + "(0, 500.0)\n"
                                          + "(100.0, 800.0)\n"
                                          + "(400.0, 900.0)\n"
                                          + "(700.0, 900.0)\n";

const std::string triangleAndTriangle = std::string("3\n")
                                                    + "(200.0, 900.0)\n"
                                                    + "(200.0, 200.0)\n"
                                                    + "(900.0, 100.0)\n"
                                                    + "3\n"
                                                    + "(100.0, 800.0)\n"
                                                    + "(500.0, 300.0)\n"
                                                    + "(700.0, 500.0)\n";

int main() {
    std::string userName = Interaction::getUserName();
    Interaction::greeting(userName);
    std::istringstream demoPoints(hexAndHex);
    std::ostringstream empty;

    std::istream *input = &std::cin;
    std::ostream *output = &std::cout;

    if ((userName == "Demo") || (userName == "demo") || (userName == "DEMO")) {
        input = &demoPoints;
        output = &empty;
    }

    auto& statesLib = Manipulator::StatesLibrary::getInstance();
    statesLib.emplaceState(Interaction::getFiguresStateFromInput(*input, *output));
    Interaction::printStateFromLibrary();

    Interaction::welcomeToGui();
    DrawOutput::draw_polygons_and_intersection();

    Interaction::goodbye(userName);
    system("pause");

    return 0;
}