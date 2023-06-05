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
#include "ConstantsForDrawing.h"

namespace DrawOutput {
    void draw_polygons_and_intersection();

    void DrawPoint(
        ImDrawList *draw_list, 
        const Geometry::Point& point, 
        const DrawUtils::scalingParameters& parameters,
        const ImVec2& offset = ImVec2(0, 0), 
        const ImU32& col = DrawConst::WHITE_COLOR
    );
    void DrawPolygon(
        ImDrawList *draw_list, 
        const Geometry::Polygon& polygon, 
        const DrawUtils::scalingParameters& parameters, 
        const ImVec2& offset = ImVec2(0, 0), 
        const ImU32& col = DrawConst::WHITE_COLOR
    );
    // set muted to "true" if you don't want your point to be editable
    void DisplayPoint(Geometry::Point &point, bool muted = false);
    void DisplayPolygon(Geometry::Polygon &polygon, const std::string& title = "default", bool muted = false);    
    void DisplayAddButton(Geometry::Polygon &polygon);
    void DisplayDeleteButton(Geometry::Polygon &polygon);
    void DisplayRevertButton();
    inline void DrawCanvas();
    inline void DrawProperties();
}
#endif // TRIANGLE_INTERSECTIONS_DRAW_IMAGE_H