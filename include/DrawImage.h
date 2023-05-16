#ifndef TRIANGLE_INTERSECTIONS_DRAW_IMAGE_H
#define TRIANGLE_INTERSECTIONS_DRAW_IMAGE_H

#include <vector>
#include "GeometryUtils.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

namespace DrawOutput {
void draw_triangles_and_intersection(const Geometry::Polygon &tr1,
                                     const Geometry::Polygon &tr2,
                                     const Geometry::Intersection &intersection);
}
#endif // TRIANGLE_INTERSECTIONS_DRAW_IMAGE_H