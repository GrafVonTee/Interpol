#include "GetImVecFromPolygon.h"

namespace DrawUtils {
    ImVec2 getImVec2(const Geometry::Point &p) {
        return ImVec2{(float)p.getX(), (float)p.getY()};
    }

    im_vec_triangle_t getTupleOfPointsFromPolygon(const Geometry::Polygon &triangle) {
        if (triangle.size() != 3)
            throw std::logic_error("Functions \'getTupleFromPolygon\' got not a triangle argument!");

        return std::make_tuple(
                getImVec2(triangle[0]),
                getImVec2(triangle[1]),
                getImVec2(triangle[2])
        );
    }

    std::vector<ImVec2> getVectorOfPointsFromPolygon(Geometry::Polygon& polygon) {
        std::vector<ImVec2> pointsVector;
        pointsVector.reserve(polygon.size());
        for (auto point : polygon.getPointsCopy())
            pointsVector.emplace_back(getImVec2(point));
        return pointsVector;
    }

    void findParameters(const ImVec2& a1, const ImVec2& a2, const ImVec2& a3, /// Points of first triangle
                        const ImVec2& b1, const ImVec2& b2, const ImVec2& b3, /// Points of second triangle
                        const coord_t squareSideSize,
                        double& scale_x, double& scale_y, double& delta_x, double& delta_y, double& min_x, double& min_y)
    {
        min_x = std::min({a1.x, a2.x, a3.x, b1.x, b2.x, b3.x});
        double max_x = std::max({a1.x, a2.x, a3.x, b1.x, b2.x, b3.x});
        min_y = std::min({a1.y, a2.y, a3.y, b1.y, b2.y, b3.y});
        double max_y = std::max({a1.y, a2.y, a3.y, b1.y, b2.y, b3.y});

        scale_x = squareSideSize / (max_x - min_x);
        scale_y = squareSideSize / (max_y - min_y);

        delta_x = (squareSideSize - (max_x - min_x) * scale_x) / 2;
        delta_y = (squareSideSize - (max_y - min_y) * scale_y) / 2;
    }

    void scaleAndTranslate(ImVec2& a1, ImVec2& a2, ImVec2& a3, /// Points of first triangle
                           ImVec2& b1, ImVec2& b2, ImVec2& b3, /// Points of second triangle
                           std::vector<ImVec2>& intersectionPoints,
                           double& scale_x, double& scale_y, double& delta_x, double& delta_y,
                           double& min_x, double& min_y){

        for(ImVec2 &point : intersectionPoints){
            point.x = (point.x - min_x) * scale_x + delta_x;
            point.y = (point.y - min_y) * scale_y + delta_y;
        }

        for (ImVec2* point: {&a1, &a2, &a3, &b1, &b2, &b3}) {
            point->x = (point->x - min_x) * scale_x + delta_x;
            point->y = (point->y - min_y) * scale_y + delta_y;
        }
    }

    void addIndents(ImVec2& a1, ImVec2& a2, ImVec2& a3,
                    ImVec2& b1, ImVec2& b2, ImVec2& b3,
                    std::vector<ImVec2>& intersectionPoints,
                    const coord_t indentSize) {

        for (ImVec2* point: { &a1, &a2, &a3, &b1, &b2, &b3 }) {
            point->x += indentSize;
            point->y += indentSize;
        }

        for (ImVec2& point: intersectionPoints) {
            point.x += indentSize;
            point.y += indentSize;
        }
    }
}
