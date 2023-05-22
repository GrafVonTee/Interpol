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


            ImGui::SetNextWindowPos(ImVec2(DrawConst::WINDOW_WIDTH / 3, 0), ImGuiCond_Once);
            ImGui::SetNextWindowSize(ImVec2(2 * DrawConst::WINDOW_WIDTH / 3, DrawConst::WINDOWS_HEIGHT), ImGuiCond_Once);
            ImGui::Begin("Canvas", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
            ImDrawList *draw_list = ImGui::GetWindowDrawList();
            
            
            ImVec2 pos = ImGui::GetCursorScreenPos();

            double scale_x, scale_y, delta_x, delta_y, min_x, min_y;

            DrawUtils::findParameters(tr1, tr2, DrawConst::SQUARE_SIDE_SIZE,
                                    scale_x, scale_y, delta_x, delta_y, min_x, min_y);
            Geometry::Polygon drawnTr1 = DrawUtils::scaleAndTranslate(tr1, scale_x, scale_y, 
                                    delta_x, delta_y, min_x, min_y);
            Geometry::Polygon drawnTr2 = DrawUtils::scaleAndTranslate(tr2, scale_x, scale_y, 
                                    delta_x, delta_y, min_x, min_y);
            Geometry::Polygon drawnIntersection = DrawUtils::scaleAndTranslate(intersection.polygon, scale_x, scale_y, 
                                    delta_x, delta_y, min_x, min_y);    
                                    
            // Geometry::Polygon drawnTr1 = tr1;
            // Geometry::Polygon drawnTr2 = tr2;
            // Geometry::Polygon drawnIntersection = intersection.polygon;                                 
                                        

            auto [a1, a2, a3] = DrawUtils::getTupleOfPointsFromPolygon(drawnTr1, pos);
            auto [b1, b2, b3] = DrawUtils::getTupleOfPointsFromPolygon(drawnTr2, pos);
            auto intersection_points = DrawUtils::getVectorOfPointsFromPolygon(drawnIntersection, pos);

            

            // draw the first triangle
            draw_list->AddTriangleFilled(
                a1,
                a2,
                a3,
                RED_COLOR
            );
            

            // draw the second triangle
            draw_list->AddTriangleFilled(
                b1,
                b2,
                b3,
                GREEN_COLOR
            );

            // draw the intersection
            if (intersection_points.size() >= 3)               
                draw_list->AddConvexPolyFilled(&intersection_points[0],
                                               (int) intersection_points.size(),
                                               YELLOW_COLOR);

            else if (intersection_points.size() == 2)
                draw_list->AddLine(intersection_points[0],
                                   intersection_points[1],
                                   YELLOW_COLOR,
                                   DrawConst::LINE_THICKNESS);
            else if (intersection_points.size() == 1)
                draw_list->AddCircleFilled(intersection_points[0], DrawConst::INTERSECTION_POINT_SIZE, YELLOW_COLOR);

            for (const Geometry::Polygon* figurePtr : {&drawnTr1, &drawnTr2, &drawnIntersection}) {
                const std::vector<Geometry::Point>& points = const_cast<Geometry::Polygon*>(figurePtr)->getPointsRef();                
                for (const Geometry::Point& point : points) {
                    ImVec2 relativePoint = ImVec2(pos.x + (float) point.getX(), pos.y + (float) point.getY());
                    draw_list->AddCircleFilled(
                        relativePoint,
                        DrawConst::POINT_SIZE,
                        WHITE_COLOR);
                    draw_list->AddText(
                        nullptr, 
                        DrawConst::LETTER_FONT_SIZE, 
                        relativePoint,
                        WHITE_COLOR,
                        (" " + point.getLabel()).c_str());
                }
            }

            ImGui::End();



            ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Once);
            ImGui::SetNextWindowSize(ImVec2(DrawConst::WINDOW_WIDTH / 3, DrawConst::WINDOWS_HEIGHT), ImGuiCond_Once);
            
            ImGui::Begin("Properties", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
            
            std::vector<Geometry::Point> &points1 = tr1.getPointsRef();
            ImGui::Text("Polygon 1");
            for (Geometry::Point& point : points1) {                
                float pointXY[2] = {(float)point.getX(), (float)point.getY()};
                ImGui::InputFloat2((" " + point.getLabel()).c_str(), pointXY);
                point.setX(pointXY[0]);
                point.setY(pointXY[1]);
                tr1.sortPoints();
                intersection = Math::findTriangleInter(tr1, tr2);
            }
            std::vector<Geometry::Point> &points2 = tr2.getPointsRef();
            ImGui::Text("Polygon 2");
            for (Geometry::Point& point : points2) {
                float pointXY[2] = {(float)point.getX(), (float)point.getY()};
                ImGui::InputFloat2((" " + point.getLabel()).c_str(), pointXY);
                point.setX(pointXY[0]);
                point.setY(pointXY[1]);
                tr2.sortPoints();      
                intersection = Math::findTriangleInter(tr1, tr2);  
            }    
            std::vector<Geometry::Point> interPoints = intersection.polygon.getPointsRef();
            ImGui::Text("Intersection");
            for (Geometry::Point point : interPoints) {
                float pointXY[2] = {(float)point.getX(), (float)point.getY()};
                ImGui::InputFloat2(("  " + point.getLabel()).c_str(), pointXY);
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
}