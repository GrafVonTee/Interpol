#include <iostream>
#include <sstream>
#include "GeometryUtils.h"
#include "ConsoleInteraction.h"
#include "Parsing.h"

using std::cout, std::cin, std::endl, std::cerr;

const std::string g_letters = "ABCDEFGHKLMN";

namespace Interaction {
    void greeting(const std::string &userName) {
        cout << "Greetings, " << (userName.empty() ? "Traveller" : userName) << "!" << endl;
        cout << "This program will immerse you in the wonderful world of\n\tTriangle Intersections!" << endl;
        cout << "All you need is entering the values of your two triangles..." << endl;
        cout << "...and take resulted polygon!" << endl;
        cout << endl;
    }

    void welcomeToGui() {
        cout << "Well, let's take a look on your triangles and intersection between them!" << endl;
        cout << "Another window has opened now, just click on the blue angle, hold and pull it to down-right side" << endl;
        cout << "You will see what you wrote" << endl;
        cout << endl;
    }

    void goodbye(const std::string &userName) {
        cout << "Goodbye, " << (userName.empty() ? "Traveller" : userName) << "!" << endl;
    }

    std::string getUserName() {
        cout << "Please, enter your name if you wish (otherwise just press Enter): ";
        std::string userName;
        std::getline(cin, userName);
        cout << endl;

        userName = Parsing::parseStringFromIndent(userName);
        auto inputState = Parsing::checkStringIsEmpty(userName);

        return userName;
    }

    triangle_result_t getTriangle(int numberOfTriangle,
                                  std::istream& inputStream,
                                  std::ostream& outputStream) {
        // Just for developers checking
        if ((numberOfTriangle > 2) or (numberOfTriangle < 1))
            throw std::out_of_range("Variable \'numberOfTriangle\' should equal either 1 or 2!");

        // Get points until both of them become correct
        outputStream << "Let\'s enter your " << numberOfTriangle << " triangle!" << endl;
        std::vector<Geometry::Point> points;
        for (auto i = 0; i < Geometry::Letters::D; i++) {
            Geometry::Point point;
            States::InputState state;
            do {
                auto [tuple_point, tuple_state] = getPoint(
                        Geometry::Letters(i + ((numberOfTriangle == 1) ? skipToTriangle1 : skipToTriangle2)),
                        inputStream, outputStream);
                point = tuple_point;
                state = tuple_state;
            } while (state != States::InputState::Correct);
            points.push_back(point);
        }

        // Check entered points can actually form triangle
        Geometry::Polygon polygon;
        States::InputState state = States::InputState::Correct;
        try {
            polygon = Geometry::Polygon(points);
        } catch (const std::logic_error& e) {
            cerr << e.what() << endl;
            polygon = Geometry::Polygon();
            state = States::InputState::IncorrectInput;
        }

        return std::make_tuple(polygon, state);
    }

    point_result_t getPoint(Geometry::Letters letter,
                            std::istream &inputStream,
                            std::ostream& outputStream) {
        // Just for developers checking
        if (letter >= Geometry::Letters::AllLetters)
            throw std::out_of_range("Unexpected letter!");

        outputStream << "Please, enter new point " << g_letters[letter] << " in \'(x, y)\' format: ";
        std::string inputStr;
        std::getline(inputStream, inputStr);
        // cin.ignore();

        auto [resulted, state] = Parsing::parsePoint(inputStr);

        switch (state) {
            case States::InputState::IncorrectInput:
                cerr << "Incorrect input! Please, enter values in CORRECT format \'(x, y)\'!" << endl;
                return std::make_tuple(Geometry::Point(), state);
            case States::InputState::EmptyString:
                cerr << "String is empty! Please, enter values in format \'(x, y)\'!" << endl;
                return std::make_tuple(Geometry::Point(), state);
            default:
                std::stringstream stream(resulted);
                coord_t x, y;
                stream >> x >> y;
                char label = g_letters[letter];
                return std::make_tuple(Geometry::Point(x, y, label), state);
        }
    }

    triangle_pair_t getBothTriangles(std::istream &inputStream,
                                     std::ostream& outputStream) {
        // Get triangles until both of them become correct

        outputStream << "The first thing you need is defining your two triangles (1 and 2)!" << endl;
        Geometry::Polygon triangle1, triangle2;
        States::InputState state;
        for (int i = 1; i <= 2; ++i) {
            do {
                outputStream << endl;
                auto [tuple_triangle, tuple_state] = getTriangle(i, inputStream, outputStream);
                if (i == 1)
                    triangle1 = tuple_triangle;
                else
                    triangle2 = tuple_triangle;
                state = tuple_state;
            } while (state != States::InputState::Correct);
        }

        return std::make_tuple(triangle1, triangle2);
    }

    void printPoint(const Geometry::Point &point) {
        cout << "Point " << point.getLabel() << " = " << point << endl;
    }

    void printTriangle(const Geometry::Polygon &triangle) {
        std::string nameOfTriangle = "###";
        for (size_t i = 0; i < triangle.size(); ++i)
            nameOfTriangle[i] = triangle[i].getLabel();

        cout << "Triangle " << nameOfTriangle
             << " with points:" << endl;
        for (auto i = 0; i < triangle.size(); ++i)
            printPoint(triangle[i]);
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
        std::string polygonName;
        for (size_t i = 0; i < polygon.size(); ++i)
            polygonName.push_back(polygon[i].getLabel());

        if (polygonType == "not a polygon")
            cout << "Your polygon... is something strange???"
                 << "I do not know when this output can be printed." << endl;

        cout << "Your polygon is a " << polygonType << " " << polygonName << " with points:" << endl;
        for (auto i = 0; i < polygon.size(); ++i)
            printPoint(polygon[i]);
    }

    std::string getTypeNameOfPolygon(const States::PolygonState &state) {
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