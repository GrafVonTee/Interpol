#include "imgui.h"
#include "DrawImage.h"
#include "GeometryUtils.h"
#include "StatesUtils.h"
#include "CalculateIntersections.h"
#include "Parsing.h"
#include "ConsoleInteraction.h"

std::vector<Geometry::Point> vec1 {Geometry::Point(100.0, 200.0), Geometry::Point(100.0, 400.0), Geometry::Point(300.0, 400.0)};

Geometry::Polygon tria1(vec1);

std::vector<Geometry::Point> vec2 {Geometry::Point(100.0, 100.0), Geometry::Point(100.0, 500.0), Geometry::Point(500.0, 100.0)};

Geometry::Polygon tria2(vec2);

Geometry::Intersection intersect = Math::findTriangleInter(tria1, tria2);

Geometry::Polygon poly = intersect.polygon;

std::vector<Geometry::Point> result = poly.getPointsCopy();


std::vector<ImVec2> fromPoints(const std::vector<Geometry::Point>& input) {
    std::vector<ImVec2> res;
    res.reserve(input.size());
    for (const auto i: input)
        res.emplace_back(i.getX(), i.getY());
    return res;
}


int main() {
    draw_triangles_and_intersection(
            ImVec2(100.0, 200.0),ImVec2(100.0, 400.0),ImVec2(300.0, 400.0),
            ImVec2(100.0, 100.0),ImVec2(100.0, 500.0), ImVec2(500.0, 100.0),
            fromPoints(result));
    return 0;
}