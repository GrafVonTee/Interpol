#include "DrawImage.h"


void draw_triangles_and_intersection(const ImVec2& a1, const ImVec2& a2, const ImVec2& a3, const ImVec2& b1, const ImVec2& b2, const ImVec2& b3, const std::vector<ImVec2>& intersection_points) {
    // create a new image
    unsigned char* img = new unsigned char[512 * 512 * 3];
    memset(img, 255, 512 * 512 * 3); // fill with white pixels

    // initialize ImGui
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.DisplaySize = ImVec2(512, 512);
    io.DisplayFramebufferScale = ImVec2(1, 1);
    ImGui::StyleColorsDark();

    // create a new window
    ImGui::SetNextWindowSize(io.DisplaySize);
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::Begin("My Window", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
    ImDrawList* draw_list = ImGui::GetWindowDrawList();

    // draw the first triangle
    draw_list->AddTriangle(a1, a2, a3, IM_COL32(255, 0, 0, 255), 2.0f);

    // draw the second triangle
    draw_list->AddTriangle(b1, b2, b3, IM_COL32(0, 255, 0, 255), 2.0f);

    // draw the intersection
    draw_list->AddPolyline(&intersection_points[0], intersection_points.size(), IM_COL32(255, 255, 0, 255), true, 2.0f);

    // end the window
    ImGui::End();

    // cleanup
    delete[] img;
    ImGui::DestroyContext();
}
