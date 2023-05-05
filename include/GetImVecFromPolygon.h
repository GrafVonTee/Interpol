#ifndef TRIANGLE_INTERSECTIONS_GETIMVECFROMPOLYGON_H
#define TRIANGLE_INTERSECTIONS_GETIMVECFROMPOLYGON_H

#include <tuple>
#include <vector>
#include "imgui.h"
#include "GeometryUtils.h"

namespace DrawUtils {
    using im_vec_triangle_t = std::tuple<ImVec2, ImVec2, ImVec2>;

    im_vec_triangle_t getTupleFromPolygon(const Geometry::Polygon &triangle);
    std::vector<ImVec2> getVectorFromPolygon(const Geometry::Polygon &polygon);
}

#endif //TRIANGLE_INTERSECTIONS_GETIMVECFROMPOLYGON_H
