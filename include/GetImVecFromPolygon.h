#ifndef TRIANGLE_INTERSECTIONS_GETIMVECFROMPOLYGON_H
#define TRIANGLE_INTERSECTIONS_GETIMVECFROMPOLYGON_H

#include <tuple>
#include <vector>
#include "imgui.h"
#include "GeometryUtils.h"

namespace DrawUtils {
    using im_vec_triangle_t = std::tuple<ImVec2, ImVec2, ImVec2>;
    constexpr size_t squareSideSize_c = 700;

    im_vec_triangle_t getTupleFromPolygon(const Geometry::Polygon &triangle);
    std::vector<ImVec2> getVectorFromPolygon(Geometry::Polygon& polygon);

    void findParameters(const ImVec2& a1, const ImVec2& a2, const ImVec2& a3,
                        const ImVec2& b1, const ImVec2& b2, const ImVec2& b3,
                        double a,
                        double& scale_x, double& scale_y, double& delta_x, double& delta_y, double& min_x, double& min_y);

    void scaleAndTranslate(ImVec2& a1, ImVec2& a2, ImVec2& a3,
                           ImVec2& b1, ImVec2& b2, ImVec2& b3,
                           std::vector<ImVec2>& intersection_points,
                           double& scale_x, double& scale_y, double& delta_x, double& delta_y,
                           double& min_x, double& min_y);
}
#endif //TRIANGLE_INTERSECTIONS_GETIMVECFROMPOLYGON_H
