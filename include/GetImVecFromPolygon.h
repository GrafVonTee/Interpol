#ifndef TRIANGLE_INTERSECTIONS_GETIMVECFROMPOLYGON_H
#define TRIANGLE_INTERSECTIONS_GETIMVECFROMPOLYGON_H

#include <tuple>
#include <vector>
#include <algorithm>
#include "imgui.h"
#include "GeometryUtils.h"

namespace DrawUtils {
    using im_vec_triangle_t = std::tuple<ImVec2, ImVec2, ImVec2>;

    struct scalingParameters{
        float scale_x = 0;
        float scale_y = 0;
        float delta_x = 0;
        float delta_y = 0;
        float min_x = 0;
        float min_y = 0;
    };


    im_vec_triangle_t getTupleOfPointsFromPolygon(const Geometry::Polygon &triangle, ImVec2 offset = ImVec2(0,0));
    std::vector<ImVec2> getVectorOfPointsFromPolygon(const Geometry::Polygon& polygon, ImVec2 offset = ImVec2(0,0));
    ImVec2 getImVec2(const Geometry::Point &p, ImVec2 offset = ImVec2(0,0));

    scalingParameters findParameters(const Geometry::Polygon &tr1, 
                        const Geometry::Polygon &tr2,
                        const coord_t squareSideSize);

    Geometry::Polygon scaleAndTranslate(const Geometry::Polygon &polygon, scalingParameters parameters);

    Geometry::Polygon addIndents(Geometry::Polygon &polygon,
                    const coord_t indentSize);

    void setActualPointsLabels(Geometry::Polygon &triangle1,
                               Geometry::Polygon &triangle2,
                               Geometry::Intersection &intersection);
}
#endif //TRIANGLE_INTERSECTIONS_GETIMVECFROMPOLYGON_H
