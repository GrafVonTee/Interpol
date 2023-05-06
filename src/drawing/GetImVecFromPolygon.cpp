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
}
