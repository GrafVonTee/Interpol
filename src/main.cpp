#include <sstream>
#include "DrawImage.h"
#include "Parsing.h"
#include "ConsoleInteraction.h"
#include "StatesLibrary.h"
#include "ConstantsForDrawing.h"

int main() {
    std::string userName = Interaction::getUserName();
    Interaction::greeting(userName);
    std::istringstream demoPoints(DrawConst::HEX_AND_HEX_DEMO_INPUT);
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
    DrawOutput::drawPolygonsAndIntersection();

    Interaction::goodbye(userName);
    system("pause");

    return 0;
}