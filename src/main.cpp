#include "imgui.h"
#include "DrawImage.h"
#include "GeometryUtils.h"
#include "StatesUtils.h"
#include "CalculateIntersections.h"
#include "Parsing.h"
#include "ConsoleInteraction.h"

std::vector<Geometry::Point> vec1 {Geometry::Point(1.0, 2.0), Geometry::Point(1.0, 4.0), Geometry::Point(3.0, 4.0)};

Geometry::Polygon tria1(vec1);

std::vector<Geometry::Point> vec2 {Geometry::Point(0.0, 0.0), Geometry::Point(0.0, 7.0), Geometry::Point(7.0, 0.0)};

Geometry::Polygon tria2(vec2);

Geometry::Intersection intersect = Math::findTriangleInter(tria1, tria2);

Geometry::Polygon poly = intersect.polygon;

std::vector<Geometry::Point> result = poly.getPointsCopy();


std::vector<ImVec2> fromPoints(const std::vector<Geometry::Point>& input){
    std::vector<ImVec2> res;
    res.reserve(input.size());
for (const auto & i : input)
        res.emplace_back(i.getX(), i.getY());
    return res;
}


int main() {
    draw_triangles_and_intersection(ImVec2(1.0, 2.0), ImVec2(1.0, 4.0), ImVec2(3.0, 4.0), ImVec2(0.0, 0.0), ImVec2(0.0, 7.0), ImVec2(7.0, 0.0), fromPoints(result));
    return 0;
}