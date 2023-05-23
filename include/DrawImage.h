#ifndef TRIANGLE_INTERSECTIONS_DRAW_IMAGE_H
#define TRIANGLE_INTERSECTIONS_DRAW_IMAGE_H

#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "GeometryUtils.h"

#define RED_COLOR    IM_COL32(186, 36,  66, 255)
#define GREEN_COLOR  IM_COL32(40,  156, 80, 255)
#define YELLOW_COLOR IM_COL32(204, 189, 12, 255)
#define WHITE_COLOR  IM_COL32(255, 255, 255, 255)

namespace DrawOutput {
    void draw_triangles_and_intersection(Geometry::Polygon &tr1,
                                         Geometry::Polygon &tr2,
                                         Geometry::Intersection &intersection);
}
#endif // TRIANGLE_INTERSECTIONS_DRAW_IMAGE_H