#ifndef TRIANGLE_INTERSECTIONS_CONSOLE_INTERACTION_H
#define TRIANGLE_INTERSECTIONS_CONSOLE_INTERACTION_H

#include <tuple>
#include <string>

namespace Interaction {
    using point_result_t = std::tuple<Geometry::Point, States::InputState>;
    using triangle_result_t = std::tuple<Geometry::Polygon, States::InputState>;
    using triangle_pair_t = std::tuple<Geometry::Polygon, Geometry::Polygon>;

    void greeting(const std::string &userName);
    void goodbye(const std::string &userName);
    void welcomeToGui();
    std::string getUserName();
    triangle_result_t getTriangle(const std::string &letter,
                                  std::istream& inputStream = std::cin,
                                  std::ostream& outputStream = std::cout);
    point_result_t getPoint(const std::string &letter,
                            std::istream& inputStream = std::cin,
                            std::ostream& outputStream = std::cout);
    triangle_pair_t getBothTriangles(std::istream& inputStream = std::cin,
                                     std::ostream& outputStream = std::cout);

    void printPoint(const Geometry::Point &point);
    void printTriangle(const Geometry::Polygon &triangle);
    void printIntersection(const Geometry::Intersection &intersection);
    void printPolygon(const Geometry::Polygon &polygon);

    std::string getTypeNameOfPolygon(const States::PolygonState &state);
}
#endif //TRIANGLE_INTERSECTIONS_CONSOLE_INTERACTION_H