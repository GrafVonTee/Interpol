#include "DrawImage.h"
#include "GetImVecFromPolygon.h"
#include "ConstantsForDrawing.h"
#include "imgui_demo.cpp"
#include "CalculateIntersections.h"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        // Set the window to close when the Escape key is pressed
        glfwSetWindowShouldClose(window, true);
    }
}

namespace DrawOutput {
    void draw_triangles_and_intersection(Geometry::Polygon &tr1,
                                         Geometry::Polygon &tr2,
                                         Geometry::Intersection &intersection) {



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
        GLFWwindow *window = glfwCreateWindow(DrawConst::WINDOW_WIDTH, DrawConst::WINDOWS_HEIGHT,
                                              "Triangle Intersection",
                                              nullptr, nullptr);

        // Make the OpenGL context current
        glfwMakeContextCurrent(window);
        // glfwHideWindow(window);
        glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
        glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);

        // Initialize GLAD
        gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();
        (void) io;
        io.DisplaySize = ImVec2(DrawConst::DISPLAY_SIZE, DrawConst::DISPLAY_SIZE);
        io.DisplayFramebufferScale = ImVec2(DrawConst::DISPLAY_SCALE, DrawConst::DISPLAY_SCALE);

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
            
            // Set ImGui window properties
            ImGui::SetNextWindowPos(ImVec2(DrawConst::WINDOW_WIDTH / 3, 0), ImGuiCond_Once);
            ImGui::SetNextWindowSize(ImVec2(2 * DrawConst::WINDOW_WIDTH / 3, DrawConst::WINDOWS_HEIGHT), ImGuiCond_Once);

            ImGui::Begin("Canvas", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
            {
                ImDrawList *draw_list = ImGui::GetWindowDrawList(); 
                ImVec2 pos = ImGui::GetCursorScreenPos();

                DrawUtils::scalingParameters parameters = DrawUtils::findParameters(tr1, tr2, DrawConst::SQUARE_SIDE_SIZE);

                DrawPolygon(draw_list, tr1, parameters, pos, RED_COLOR);
                DrawPolygon(draw_list, tr2, parameters, pos, GREEN_COLOR);
                DrawPolygon(draw_list, intersection.polygon, parameters, pos, YELLOW_COLOR);
                for (const Geometry::Polygon* figurePtr : {&tr1, &tr2, &intersection.polygon}) {
                    DrawPoints(draw_list, figurePtr, parameters, pos, WHITE_COLOR);                    
                }
            }
            ImGui::End();

            // Set ImGui window properties
            ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Once);
            ImGui::SetNextWindowSize(ImVec2(DrawConst::WINDOW_WIDTH / 3, DrawConst::WINDOWS_HEIGHT), ImGuiCond_Once);
            
            ImGui::Begin("Properties", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
            {
                DisplayPolygon(tr1, "Polygon 1");
                DisplayPolygon(tr2, "Polygon 2");
                intersection = Math::findTriangleInter(tr1, tr2);
                DrawUtils::setActualPointsLabels(tr1, tr2, intersection);                
                DisplayPolygon(intersection.polygon, "Intersection", true);
            }
            ImGui::End();
            

            // ImGui::ShowDemoWindow();

            // Rendering
            ImGui::Render();
            int display_w, display_h;
            glfwGetFramebufferSize(window, &display_w, &display_h);
            glViewport(0, 0, display_w, display_h);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
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

    void DrawPoints(
        ImDrawList *draw_list, 
        const Geometry::Polygon* polygon, 
        DrawUtils::scalingParameters parameters, 
        ImVec2 offset, 
        ImU32 col)
    {
        Geometry::Polygon drawnPolygon = DrawUtils::scaleAndTranslate(*polygon, parameters);
        const std::vector<Geometry::Point>& points = drawnPolygon.getPointsRef();                
        for (const Geometry::Point& point : points) {
            ImVec2 relativePoint = ImVec2(offset.x + (float) point.getX(), offset.y + (float) point.getY());
            draw_list->AddCircleFilled(
                relativePoint,
                DrawConst::POINT_SIZE,
                WHITE_COLOR
            );
            draw_list->AddText(
                nullptr, 
                DrawConst::LETTER_FONT_SIZE, 
                relativePoint,
                WHITE_COLOR,
                (" " + point.getLabel()).c_str()
            );
        }
    }

    void DrawPolygon(
        ImDrawList *draw_list, 
        Geometry::Polygon polygon, 
        DrawUtils::scalingParameters parameters, 
        ImVec2 offset, 
        ImU32 col)
    {
        Geometry::Polygon drawnPolygon = DrawUtils::scaleAndTranslate(polygon, parameters);
        auto polygon_points = DrawUtils::getVectorOfPointsFromPolygon(drawnPolygon, offset);
        // draw the intersection
        if (polygon_points.size() >= 3)               
            draw_list->AddConvexPolyFilled(
                &polygon_points[0],
                (int) polygon_points.size(),
                col
            );

        else if (polygon_points.size() == 2)
            draw_list->AddLine(
                polygon_points[0],
                polygon_points[1],
                col,
                DrawConst::LINE_THICKNESS
            );

        else if (polygon_points.size() == 1)
            draw_list->AddCircleFilled(
                polygon_points[0], 
                DrawConst::INTERSECTION_POINT_SIZE, 
                col
            );

    }

    void DisplayPolygon(Geometry::Polygon &polygon, const char* title, bool muted)
    {
        std::vector<Geometry::Point> &points1 = polygon.getPointsRef();
        if (muted)
            points1 = polygon.getPointsRef();
        ImGui::Text(title);
        for (Geometry::Point& point : points1) {   
            DisplayPoint(point, muted);                    
            polygon.sortPoints();
        }
    }

    void DisplayPoint(Geometry::Point &point, bool muted)
    {
        const char* prefix = " ";
        if (muted)
            prefix = "  ";
        float pointXY[2] = {(float)point.getX(), (float)point.getY()};
        ImGui::InputFloat2((prefix + point.getLabel()).c_str(), pointXY);
        if (!muted)
        {
            point.setX(pointXY[0]);
            point.setY(pointXY[1]);
        }
    }

}

