#include <iostream>
#include <string>
#include <regex>
#include "GeometryUtils.h"
#include "ConsoleInteraction.h"
#include "Parsing.h"

using std::cout, std::cin, std::endl, std::cerr;
using std::string;

const string g_letters = "ABCDEFGHKLMN";

namespace Interaction {
    void greeting(string userName) {
        userName = Parsing::parseStringFromIndent(userName);
        auto inputState = Parsing::checkStringIsEmpty(userName);
        if (inputState == States::InputState::EmptyString)
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

    triangle_result_t getTriangle(int numberOfTriangle) {
        if ((numberOfTriangle > 2) or (numberOfTriangle < 1))
            throw std::out_of_range("Variable \'numberOfTriangle\' should equal either 1 or 2!");

        cout << "Let\'s enter your " << numberOfTriangle << " triangle!" << endl;
        std::vector<Geometry::Point> points;
        for (auto i = 0; i < Geometry::Letters::D; i++) {
            Geometry::Point point;
            States::InputState state;
            do {
                auto [tuple_point, tuple_state] = getPoint(
                        Geometry::Letters(i + ((numberOfTriangle == 1) ? skipToTriangle1 : skipToTriangle2))
                        );
                point = tuple_point;
                state = tuple_state;
            } while (state != States::InputState::Correct);
            points.push_back(point);
        }

        if (!checkPointsAreUnique(points)) {
            cerr << "You entered some equal points!\nPlease, reenter with unique ones!" << endl;
            return std::make_tuple(Geometry::Polygon(), States::InputState::EqualPoints);
        }

        return std::make_tuple(Geometry::Polygon(points), States::InputState::Correct);
    }

    bool checkPointsAreUnique(const std::vector<Geometry::Point> &vec) {
        for (auto i = 0; i < vec.size(); ++i)
            for (auto j = i + 1; j < vec.size(); ++j) {
                if (vec[i] == vec[j])
                    return false;
            }
        return true;
    }

    point_result_t getPoint(Geometry::Letters letter) {
        if (letter >= Geometry::Letters::AllLetters)
            throw std::out_of_range("Unexpected letter!");

        cout << "Please, enter new point " << g_letters[letter] << " in \'(x, y)\' format: ";
        string inputStr;
        std::getline(cin, inputStr);
        // cin.ignore();

        auto [resulted, state] = Parsing::parsePoint(inputStr);

        switch (state) {
            case States::InputState::IncorrectInput:
            case States::InputState::IncorrectFormat:
                cerr << "Incorrect input! Please, enter values in CORRECT foramt \'(x, y)\'!" << endl;
                return std::make_tuple(Geometry::Point(), state);
            case States::InputState::EmptyString:
                cerr << "String is empty! Please, enter values in format \'(x, y)\'!" << endl;
                return std::make_tuple(Geometry::Point(), state);
            default:
                std::stringstream stream(resulted);
                coord_t x, y;
                stream >> x >> y;
                return std::make_tuple(Geometry::Point(x, y), state);
        }
    }

    triangle_pair_t getBothTriangles() {
        cout << "The first thing you need is defining your two triangles (1 and 2)!" << endl;
        Geometry::Polygon triangle1, triangle2;
        States::InputState state;
        for (int i = 1; i <= 2; ++i) {
            do {
                cout << endl;
                auto [tuple_triangle, tuple_state] = getTriangle(i);
                if (i == 1)
                    triangle1 = tuple_triangle;
                else
                    triangle2 = tuple_triangle;
                state = tuple_state;
            } while (state != States::InputState::Correct);
        }

        return std::make_tuple(triangle1, triangle2);
    }

    void printPoint(const Geometry::Point &point, Geometry::Letters letter) {
        cout << "Point " << g_letters[letter] << " = " << point << endl;
    }

    void printTriangle(const Geometry::Polygon &triangle, int triangleNumber) {
        auto neededSkip = (triangleNumber == 1) ? skipToTriangle1 : skipToTriangle2;
        cout << "Triangle " << g_letters.substr(neededSkip, 3)
             << " with points:" << endl;
        for (auto i = 0; i <= Geometry::Letters::C; ++i)
            printPoint(triangle[i], Geometry::Letters(i + neededSkip));
        cout << endl;
    }

    void printIntersection(const Geometry::Intersection &intersection) {
        cout << "Congrats!" << endl;
        using IState = States::IntersectionState;
        switch (intersection.state) {
            case IState::NoIntersection:
                cout << "There is no intersection between your triangles!" << endl;
                break;
            case IState::Matched:
                cout << "Your triangles match!" << endl;
                break;
            case IState::Nested:
                cout << "One of your triangles is nested inside another!" << endl;
                break;
            case IState::Polygon:
                cout << "Your intersection is a polygon!" << endl;
                printPolygon(intersection.polygon);
        }
        cout << endl;
    }

    void printPolygon(const Geometry::Polygon &polygon) {
        auto polygonType = getTypeNameOfPolygon(polygon.getState());
        auto polygonName = g_letters.substr(skipToIntersection, (unsigned int)polygon.getState());
        if (polygonType == "not a polygon")
            cout << "Your polygon... is something strange???"
                 << "I do not know when this output can be printed." << endl;

        cout << "Your polygon is a " << polygonType << " " << polygonName << " with points:" << endl;
        for (auto i = 0; i < polygon.size(); ++i)
            printPoint(polygon[i], Geometry::Letters(i + skipToIntersection));
    }

    std::string getTypeNameOfPolygon(const States::PolygonState state) {
        std::string polygonTypes[] {
            "not a polygon",
            "point",
            "edge",
            "triangle",
            "quadrilateral",
            "pentagon",
            "hexagon",
        };
        return polygonTypes[(unsigned int)state];
    }
}