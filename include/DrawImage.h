#ifndef TRIANGLE_INTERSECTIONS_DRAW_IMAGE_H
#define TRIANGLE_INTERSECTIONS_DRAW_IMAGE_H

#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "GeometryUtils.h"
#include "GetImVecFromPolygon.h"

#define RED_COLOR    IM_COL32(186, 36,  66, 255)
#define GREEN_COLOR  IM_COL32(40,  156, 80, 255)
#define YELLOW_COLOR IM_COL32(204, 189, 12, 255)
#define WHITE_COLOR  IM_COL32(255, 255, 255, 255)

namespace DrawOutput {
    void draw_triangles_and_intersection(Geometry::Polygon &tr1,
                                         Geometry::Polygon &tr2,
                                         Geometry::Intersection &intersection);
    void DrawPoints(
        ImDrawList *draw_list, 
        const Geometry::Polygon &polygon, 
        const DrawUtils::scalingParameters& parameters,
        const ImVec2& offset = ImVec2(0, 0), 
        const ImU32& col = WHITE_COLOR
    );
    void DrawPolygon(
        ImDrawList *draw_list, 
        const Geometry::Polygon& polygon, 
        const DrawUtils::scalingParameters& parameters, 
        const ImVec2& offset = ImVec2(0, 0), 
        const ImU32& col = WHITE_COLOR
    );
    // set muted to "true" if you don't want your point to be editable
    void DisplayPoint(Geometry::Point &point, bool muted = false);
    void DisplayPolygon(Geometry::Polygon &polygon, const std::string& title = "default", bool muted = false);
    void DisplayAddButton();
    void DisplayDeleteButton();

}
#endif // TRIANGLE_INTERSECTIONS_DRAW_IMAGE_H