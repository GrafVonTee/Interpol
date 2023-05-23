#ifndef TRIANGLE_INTERSECTIONS_GETIMVECFROMPOLYGON_H
#define TRIANGLE_INTERSECTIONS_GETIMVECFROMPOLYGON_H

#include <tuple>
#include <vector>
#include <algorithm>
#include "imgui.h"
#include "GeometryUtils.h"

namespace DrawUtils {
    using im_vec_triangle_t = std::tuple<ImVec2, ImVec2, ImVec2>;

    im_vec_triangle_t getTupleOfPointsFromPolygon(const Geometry::Polygon &triangle, ImVec2 offset = ImVec2(0,0));
    std::vector<ImVec2> getVectorOfPointsFromPolygon(const Geometry::Polygon& polygon, ImVec2 offset = ImVec2(0,0));
    ImVec2 getImVec2(const Geometry::Point &p, ImVec2 offset = ImVec2(0,0));

    void findParameters(const Geometry::Polygon &tr1, const Geometry::Polygon &tr2,
                        const coord_t squareSideSize,
                        double& scale_x, double& scale_y, double& delta_x, double& delta_y,
                        double& min_x, double& min_y);

    Geometry::Polygon scaleAndTranslate(Geometry::Polygon &polygon,
                           double& scale_x, double& scale_y, double& delta_x, double& delta_y,
                           double& min_x, double& min_y);

    void setActualPointsLabels(Geometry::Polygon &triangle1,
                               Geometry::Polygon &triangle2,
                               Geometry::Intersection &intersection);
}
#endif //TRIANGLE_INTERSECTIONS_GETIMVECFROMPOLYGON_H
