#include "DrawImage.h"


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

void draw_triangles_and_intersection(const ImVec2& a1, const ImVec2& a2, const ImVec2& a3, const ImVec2& b1, const ImVec2& b2, const ImVec2& b3, const std::vector<ImVec2>& intersection_points) {
    // create a new image
    auto* img = new unsigned char[1024 * 1024 * 3];
    memset(img, 255, 1024 * 1024 * 3); // fill with white pixels

        // Initialize GLFW
    glfwInit();

    // Create a GLFW window
    GLFWwindow* window = glfwCreateWindow(1024, 768, "ImGui GLFW Window", NULL, NULL);

    // Make the OpenGL context current
    glfwMakeContextCurrent(window);

    // Initialize GLAD
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.DisplaySize = ImVec2(1024, 1024);
    io.DisplayFramebufferScale = ImVec2(1, 1);
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    

    // create a new window
    ImGui::SetNextWindowSize(io.DisplaySize);
    ImGui::SetNextWindowPos(ImVec2(0, 0));


    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        
        ImGui::Begin("My Window", NULL);
        ImDrawList* draw_list = ImGui::GetWindowDrawList();

        // draw the first triangle
        draw_list->AddTriangle(a1, a2, a3, IM_COL32(255, 0, 0, 255), 2.0f);

        // draw the second triangle
        draw_list->AddTriangle(b1, b2, b3, IM_COL32(0, 255, 0, 255), 2.0f);

        // draw the intersection
        draw_list->AddPolyline(&intersection_points[0], intersection_points.size(), IM_COL32(255, 255, 0, 255), true, 4.0f);
    
        // end the window
        ImGui::End();

        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);

    }
    

    ImGui::DestroyContext();

    // Shutdown GLFW
    glfwDestroyWindow(window);
    glfwTerminate();
}
