#include <iostream>
#include <sstream>
#include <limits>
#include "GeometryUtils.h"
#include "ConsoleInteraction.h"
#include "Parsing.h"

using std::cout, std::cin, std::endl, std::cerr;

namespace Interaction {
    void greeting(const std::string &userName) {
        cout << "Greetings, " << (userName.empty() ? "Traveller" : userName) << "!" << endl;
        cout << "This program will immerse you in the wonderful world of\n\tPolygon Intersections!" << endl;
        cout << "All you need is entering the values of your two polygons..." << endl;
        cout << "...and take resulted intersection!" << endl;
        cout << endl;
    }

    void welcomeToGui() {
        cout << "Well, let's take a look on your figures and intersection between them!" << endl;
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

    triangle_result_t getTriangle(const std::string &letter,
                                  std::istream& inputStream,
                                  std::ostream& outputStream) {

        // Get points until both of them become correct
        outputStream << "Let\'s enter your triangle!" << endl;
        std::vector<Geometry::Point> points;
        constexpr short numberOfPoints = 3;
        for (auto i = 0; i < numberOfPoints; i++) {
            Geometry::Point point;
            States::InputState state;
            std::string pointLetter = letter + std::to_string(i+1);
            do {
                auto [tuple_point, tuple_state] = getPoint(
                        pointLetter,
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

    polygon_result_t getPolygon(const std::string& letter, std::istream& inputStream, std::ostream& outputStream) {
        int numPoints;

        while (true) {
            outputStream << "Enter the number of points for the polygon " << letter << ": ";
            inputStream >> numPoints;

            if (!inputStream) {
                outputStream << "Invalid input. Please enter a number.\n";
                inputStream.clear();
                inputStream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }

            inputStream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if (numPoints <= 0) {
                outputStream << "Invalid number of points. Please enter a positive integer.\n";
            } else {
                break;
            }
        }

        std::vector<Geometry::Point> points;
        points.reserve(numPoints);

        for (int i = 1; i <= numPoints; ++i) {
            std::string pointLetter = letter + std::to_string(i);
            Geometry::Point point;
            States::InputState state;

            do {
                auto [tuplePoint, tupleState] = getPoint(pointLetter, inputStream, outputStream);
                point = tuplePoint;
                state = tupleState;
            } while (state != States::InputState::Correct);

            points.emplace_back(point);
        }

        Geometry::Polygon polygon;
        States::InputState state = States::InputState::Correct;

        try {
            polygon = Geometry::Polygon(points);
        } catch (const std::logic_error& e) {
            outputStream << e.what() << std::endl;
            polygon = Geometry::Polygon();
            state = States::InputState::IncorrectInput;
        }

        return std::make_tuple(polygon, state);
    }


    point_result_t getPoint(const std::string &letter,
                            std::istream &inputStream,
                            std::ostream& outputStream)
    {
        outputStream << "Please, enter new point " << letter << " in \'(x, y)\' format: ";
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
                return std::make_tuple(Geometry::Point(x, y, letter), state);
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
                std::string letterTriangle = (i == 1) ? "A" : "B";
                auto [tuple_triangle, tuple_state] = getTriangle(letterTriangle, inputStream, outputStream);
                if (i == 1)
                    triangle1 = tuple_triangle;
                else
                    triangle2 = tuple_triangle;
                state = tuple_state;
            } while (state != States::InputState::Correct);
        }

        return std::make_tuple(triangle1, triangle2);
    }

    polygon_pair_t getBothPolygons(std::istream& inputStream, std::ostream& outputStream) {
        outputStream << "The first thing you need is to define your two polygons (1 and 2)!" << std::endl;
        Geometry::Polygon polygon1, polygon2;
        States::InputState state;
        for (int i = 1; i <= 2; ++i) {
            do {
                outputStream << std::endl;
                std::string letterPolygon = (i == 1) ? "A" : "B";
                auto [tuplePolygon, tupleState] = getPolygon(letterPolygon, inputStream, outputStream);
                if (i == 1)
                    polygon1 = tuplePolygon;
                else
                    polygon2 = tuplePolygon;
                state = tupleState;
            } while (state != States::InputState::Correct);
        }

        return std::make_tuple(polygon1, polygon2);
    }

    void printPoint(const Geometry::Point &point) {
        cout << "Point " << point.getLabel() << " = " << point << endl;
    }

    void printTriangle(const Geometry::Polygon &triangle) {
        std::string nameOfTriangle;
        for (size_t i = 0; i < triangle.size() - 1; ++i)
            nameOfTriangle += triangle[i].getLabel() + ",";
        nameOfTriangle += triangle[2].getLabel();

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
                cout << "There is no intersection between your figures!" << endl;
                break;
            case IState::Matched:
                cout << "Your figures match!" << endl;
                break;
            case IState::Nested:
                cout << "One of your figure is nested inside another!" << endl;
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
        for (size_t i = 0; i < polygon.size() - 1; ++i)
            polygonName += polygon[i].getLabel() + ",";
        if (polygon.size())
            polygonName += polygon[polygon.size() - 1].getLabel();

        if (polygonType == "not a polygon")
            cout << "Your polygon... is something strange???"
                 << "I do not know when this output could be printed." << endl;

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
                "polygon",
        };
        return polygonTypes[(unsigned int)state];
    }


    void askSorting(Geometry::Polygon& polygon, std::ostream& out = std::cout, std::istream& in = std::cin) {
        // Ask the user if they want to sort the points by traversal
        out << "Do you want to sort the points by traversal? (yes/no): ";
        std::string answer;
        std::getline(in, answer);

        if ((answer == "yes") || (answer == "y") || (answer == "Y") || (answer == "YES")) {
            // Determine the starting letter based on the polygon's label
            char startingLetter = polygon[0].getLabel()[0];

            // Update the point labels based on traversal order
            for (std::size_t i = 0; i < polygon.size(); ++i) {
                std::string pointLabel = std::string(1, startingLetter) + std::to_string(i + 1);

                // Update the point label if it doesn't start with the correct letter
                if (polygon[i].getLabel()[0] != startingLetter) {
                    polygon[i].setLabel(pointLabel);
                }
            }
        }
        // Print the polygon
        printPolygon(polygon);
    }
}