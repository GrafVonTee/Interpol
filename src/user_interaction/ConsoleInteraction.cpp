#include <iostream>
#include <string>
#include "GeometryUtils.h"
#include "ConsoleInteraction.h"
#include "Parsing.h"

using std::cout, std::cin, std::endl;
using std::string;

namespace Interaction {
    void greeting(string userName) {
        userName = Parsing::parseStringFromIndent(userName);
        auto inputState = Parsing::checkStringIsEmpty(userName);
        if (inputState == States::InputState::IncorrectInput)
            userName = "Traveler";

        cout << "Greetings, " << userName << "!" << endl;
        cout << "This program will immerse you in the wonderful world of\n\tTriangle Intersections!" << endl;
        cout << "All you need is entering the values of your two triangles..." << endl;
        cout << "...and take resulted polygon!" << endl;
        cout << endl;
    }

    string getUserName() {
        cout << "Please, enter your name if you wish (otherwise just press Enter): ";
        string userName;
        std::getline(cin, userName);
        cout << endl;
        return userName;
    }

    Geometry::Polygon getTriangle() {
        string letters = "ABCDEF";

    }
}