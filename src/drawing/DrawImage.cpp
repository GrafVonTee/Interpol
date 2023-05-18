#include "DrawImage.h"
#include "GetImVecFromPolygon.h"

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
    #define RED_COLOR    IM_COL32(186, 36,  66, 255)
    #define GREEN_COLOR  IM_COL32(40,  156, 80, 255)
    #define YELLOW_COLOR IM_COL32(204, 189, 12, 255)
    #define WHITE_COLOR  IM_COL32(255, 255, 255, 255)

    void draw_triangles_and_intersection(const Geometry::Polygon &tr1,
                                         const Geometry::Polygon &tr2,
                                         const Geometry::Intersection &intersection) {

        auto [a1, a2, a3] = DrawUtils::getTupleOfPointsFromPolygon(tr1);
        auto [b1, b2, b3] = DrawUtils::getTupleOfPointsFromPolygon(tr2);
        auto intersection_points = DrawUtils::getVectorOfPointsFromPolygon(intersection.polygon);

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
        io.DisplayFramebufferScale = ImVec2(2, 2);

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
            draw_list->AddTriangleFilled(a1, a2, a3,
                                   RED_COLOR);
            

            // draw the second triangle
            draw_list->AddTriangleFilled(b1, b2, b3,
                                   GREEN_COLOR);

            // draw the intersection
            if (intersection_points.size() >= 3)
                draw_list->AddConvexPolyFilled(&intersection_points[0],
                                               (int) intersection_points.size(),
                                               YELLOW_COLOR);

            else if (intersection_points.size() == 2)
                draw_list->AddLine(intersection_points[0],
                                   intersection_points[1],
                                   YELLOW_COLOR,
                                   10.f);
            else
                draw_list->AddCircleFilled(intersection_points[0], 10.f, YELLOW_COLOR);

            for (const Geometry::Polygon* figurePtr : {&tr1, &tr2, &intersection.polygon}) {
                const std::vector<Geometry::Point>& points = const_cast<Geometry::Polygon*>(figurePtr)->getPointsRef();
                for (const Geometry::Point& point : points) {
                    draw_list->AddCircleFilled(ImVec2((float) point.getX(), (float) point.getY()),
                                               5.f,
                                               WHITE_COLOR);
                    draw_list->AddText(ImVec2((float) point.getX(), (float) point.getY()),
                                       WHITE_COLOR,
                                       (' ' + std::string(1, point.getLabel())).c_str());
                }
            }


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