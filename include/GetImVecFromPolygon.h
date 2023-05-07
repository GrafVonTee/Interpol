#ifndef TRIANGLE_INTERSECTIONS_GETIMVECFROMPOLYGON_H
#define TRIANGLE_INTERSECTIONS_GETIMVECFROMPOLYGON_H

#include <tuple>
#include <vector>
#include <algorithm>
#include "imgui.h"
#include "GeometryUtils.h"

namespace DrawUtils {
    using im_vec_triangle_t = std::tuple<ImVec2, ImVec2, ImVec2>;
    constexpr coord_t SquareSideSize = 700;
    constexpr coord_t IndentSize = 34;

    im_vec_triangle_t getTupleOfPointsFromPolygon(const Geometry::Polygon &triangle);
    std::vector<ImVec2> getVectorOfPointsFromPolygon(Geometry::Polygon& polygon);

    void findParameters(const ImVec2& a1, const ImVec2& a2, const ImVec2& a3, /// Points of first triangle
                        const ImVec2& b1, const ImVec2& b2, const ImVec2& b3, /// Points of second triangle
                        const coord_t squareSideSize,
                        double& scale_x, double& scale_y, double& delta_x, double& delta_y, double& min_x, double& min_y);

    void scaleAndTranslate(ImVec2& a1, ImVec2& a2, ImVec2& a3, /// Points of first triangle
                           ImVec2& b1, ImVec2& b2, ImVec2& b3, /// Points of second triangle
                           std::vector<ImVec2>& intersection_points,
                           double& scale_x, double& scale_y, double& delta_x, double& delta_y,
                           double& min_x, double& min_y);

    void addIndents(ImVec2& a1, ImVec2& a2, ImVec2& a3, /// Points of first triangle
                    ImVec2& b1, ImVec2& b2, ImVec2& b3, /// Points of second triangle
                    std::vector<ImVec2>& intersection_points,
                    const coord_t indentSize);
}
#endif //TRIANGLE_INTERSECTIONS_GETIMVECFROMPOLYGON_H
