#include "DrawImage.h"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        // Set the window to close when the Escape key is pressed
        glfwSetWindowShouldClose(window, true);
    }
}

namespace DrawOutput {
    #define WIDTH 1024
    #define HEIGHT 768

    void draw_triangles_and_intersection(const ImVec2 &a1, const ImVec2 &a2, const ImVec2 &a3,
                                         const ImVec2 &b1, const ImVec2 &b2, const ImVec2 &b3,
                                         const std::vector<ImVec2> &intersection_points) {

        #if defined(IMGUI_IMPL_OPENGL_ES2)
                const char* glsl_version = "#version 100";
                glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
                glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
                glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
        #elif defined(__APPLE__)
                const char *glsl_version = "#version 120";
                glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
                glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
                glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
                glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        #else
                const char* glsl_version = "#version 130";
                glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
                glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
                glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        #endif

        // create a new image
        // auto *img = new unsigned char[1024 * 1024 * 3];
        // memset(img, 255, 1024 * 1024 * 3);

        // Initialize GLFW
        glfwInit();

        // Create a GLFW window
        GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT,
                                              "Triangle Intersection",
                                              nullptr, nullptr);

        // Make the OpenGL context current
        glfwMakeContextCurrent(window);

        // Initialize GLAD
        gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();
        (void) io;
        io.DisplaySize = ImVec2(1024, 1024);
        io.DisplayFramebufferScale = ImVec2(1, 1);

        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();

        // Setup Platform/Renderer backends
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init(glsl_version);


        // create a new window
        ImGui::SetNextWindowSize(io.DisplaySize);
        ImGui::SetNextWindowPos(ImVec2(0, 0));

        glfwSetKeyCallback(window, key_callback);

        while (!glfwWindowShouldClose(window)) {
            glfwPollEvents();

            // Start the Dear ImGui frame
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            ImGui::Begin("Intersection", nullptr);
            ImDrawList *draw_list = ImGui::GetWindowDrawList();

            // draw the first triangle
            draw_list->AddTriangle(a1, a2, a3,
                                   IM_COL32(255, 0, 0, 255),
                                   2.0f);

            // draw the second triangle
            draw_list->AddTriangle(b1, b2, b3,
                                   IM_COL32(0, 255, 0, 255),
                                   2.0f);

            // draw the intersection
            draw_list->AddPolyline(&intersection_points[0],
                                   (int) intersection_points.size(),
                                   IM_COL32(255, 255, 0, 255),
                                   true, 5.0f);

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
        
        // delete[] img;

        ImGui_ImplGlfw_Shutdown();
        ImGui_ImplOpenGL3_Shutdown();
        ImGui::DestroyContext();

        // Shutdown GLFW
        glfwDestroyWindow(window);
        glfwTerminate();
    }
}