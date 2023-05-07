#include "GetImVecFromPolygon.h"

namespace DrawUtils {
    ImVec2 getImVec2(const Geometry::Point &p) {
        return ImVec2{(float)p.getX(), (float)p.getY()};
    }

    im_vec_triangle_t getTupleFromPolygon(const Geometry::Polygon &triangle) {
        if (triangle.size() != 3)
            throw std::logic_error("Functions \'getTupleFromPolygon\' got not a triangle argument!");

        return std::make_tuple(
                getImVec2(triangle[0]),
                getImVec2(triangle[1]),
                getImVec2(triangle[2])
        );
    }

    std::vector<ImVec2> getVectorFromPolygon(Geometry::Polygon& polygon) {
        std::vector<ImVec2> pointsVector;
        pointsVector.reserve(polygon.size());
        for (auto point : polygon.getPointsCopy())
            pointsVector.emplace_back(getImVec2(point));
        return pointsVector;
    }

    void findParameters(const ImVec2& a1, const ImVec2& a2, const ImVec2& a3,
                        const ImVec2& b1, const ImVec2& b2, const ImVec2& b3,
                        double a,
                        double& scale_x, double& scale_y, double& delta_x, double& delta_y, double& min_x, double& min_y){
        min_x = std::min({a1.x, a2.x, a3.x, b1.x, b2.x, b3.x});
        double max_x = std::max({a1.x, a2.x, a3.x, b1.x, b2.x, b3.x});
        min_y = std::min({a1.y, a2.y, a3.y, b1.y, b2.y, b3.y});
        double max_y = std::max({a1.y, a2.y, a3.y, b1.y, b2.y, b3.y});

        scale_x = a / (max_x - min_x);
        scale_y = a / (max_y - min_y);

        delta_x = (a - (max_x - min_x) * scale_x) / 2;
        delta_y = (a - (max_y - min_y) * scale_y) / 2;
    }

    void scaleAndTranslate(ImVec2& a1, ImVec2& a2, ImVec2& a3,
                           ImVec2& b1, ImVec2& b2, ImVec2& b3,
                           std::vector<ImVec2>& intersection_points,
                           double& scale_x, double& scale_y, double& delta_x, double& delta_y,
                           double& min_x, double& min_y){

        for(ImVec2 &point : intersection_points){
            point.x = (point.x - min_x) * scale_x + delta_x;
            point.y = (point.y - min_y) * scale_y + delta_y;
        }

        for (auto v: {&a1, &a2, &a3, &b1, &b2, &b3}) {
            v->x = (v->x - min_x) * scale_x + delta_x;
            v->y = (v->y - min_y) * scale_y + delta_y;
        }
    }

    void addIndents(ImVec2& a1, ImVec2& a2, ImVec2& a3,
                    ImVec2& b1, ImVec2& b2, ImVec2& b3,
                    std::vector<ImVec2>& intersection_points,
                    const coord_t indentSize) {

        for (auto v: { &a1, &a2, &a3, &b1, &b2, &b3 }) {
            v->x += indentSize;
            v->y += indentSize;
        }

        for (auto &v: intersection_points) {
            v.x += indentSize;
            v.y += indentSize;
        }
    }
}
