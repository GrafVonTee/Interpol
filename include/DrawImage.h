#ifndef TRIANGLE_INTERSECTIONS_DRAW_IMAGE_H
#define TRIANGLE_INTERSECTIONS_DRAW_IMAGE_H

#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

namespace DrawOutput {
void draw_triangles_and_intersection(const ImVec2& a1, const ImVec2& a2, const ImVec2& a3,
                                     const ImVec2& b1, const ImVec2& b2, const ImVec2& b3,
                                     const std::vector<ImVec2>& intersection_points);
}
#endif // TRIANGLE_INTERSECTIONS_DRAW_IMAGE_H