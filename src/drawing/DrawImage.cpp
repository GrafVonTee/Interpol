#include <iomanip>
#include <sstream>
#include <unordered_set>
#include "DrawImage.h"
#include "GetImVecFromPolygon.h"
#include "ConstantsForDrawing.h"
#include "CalculateIntersections.h"
#include "StatesLibrary.h"

// // Enable for imgui demo window
// #include "imgui_demo.cpp"

using figures_state_t = Manipulator::FiguresState;


namespace DrawOutput {
    void drawPolygonsAndIntersection() {

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
        GLFWwindow *window = glfwCreateWindow((int) DrawConst::WINDOW_WIDTH, (int) DrawConst::WINDOWS_HEIGHT,
                                              "Polygon Intersection",
                                              nullptr, nullptr);

        // Make the OpenGL context current
        glfwMakeContextCurrent(window);
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

        auto& statesLib = Manipulator::StatesLibrary::getInstance();
        figures_state_t figures = statesLib.getStateRef();

        bool showError = false;

        std::string errorMessage;

        while (!glfwWindowShouldClose(window)) {

            glfwPollEvents();                   

            // Start the Dear ImGui frame
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();
            
            // Set ImGui window properties
            ImGui::SetNextWindowPos(ImVec2(DrawConst::WINDOW_WIDTH / 3, 0), ImGuiCond_Once);
            ImGui::SetNextWindowSize(ImVec2(2 * DrawConst::WINDOW_WIDTH / 3, DrawConst::WINDOWS_HEIGHT), ImGuiCond_Once);

            DrawCanvas();

            // Set ImGui window properties
            ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Once);
            ImGui::SetNextWindowSize(ImVec2(DrawConst::WINDOW_WIDTH / 3, DrawConst::WINDOWS_HEIGHT), ImGuiCond_Once);
            
            try
            {                
                DrawProperties();
            }
            catch(const std::exception& e)
            {       
                ImGui::End();
                showError = true;
                errorMessage = e.what();
            }
            
            if (showError){
                ImGui::Begin("Properties", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
                    if (ErrorMarker(errorMessage.c_str())){
                        showError = false;
                        ImGui::End();
                    }
                ImGui::End();
            }
            // DrawProperties();

            // Rendering
            ImGui::Render();
            int displayW, displayH;
            glfwGetFramebufferSize(window, &displayW, &displayH);
            glViewport(0, 0, displayW, displayH);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            glfwSwapBuffers(window);
        }

        ImGui_ImplGlfw_Shutdown();
        ImGui_ImplOpenGL3_Shutdown();
        ImGui::DestroyContext();

        // Shutdown GLFW
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    inline void DrawCanvas() {

        const figures_state_t& figures = Manipulator::StatesLibrary::getInstance().getStateView();
        
        ImGui::Begin("Canvas", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
        {

            ImDrawList *drawList = ImGui::GetWindowDrawList();
            ImVec2 pos = ImGui::GetCursorScreenPos();

            DrawUtils::scalingParameters parameters = DrawUtils::findParameters(figures.polygon1,
                                                                                figures.polygon2,
                                                                                DrawConst::SQUARE_SIDE_SIZE);

            DrawPolygon(drawList, figures.polygon1, parameters, pos, DrawConst::RED_COLOR);
            DrawPolygon(drawList, figures.polygon2, parameters, pos, DrawConst::GREEN_COLOR);
            DrawPolygon(drawList, figures.intersection.polygon, parameters, pos, DrawConst::YELLOW_COLOR);

            std::unordered_set<Geometry::Point, Geometry::Point::HashFunction> s;
            for (const Geometry::Polygon& figurePtr : {figures.polygon1, figures.polygon2, figures.intersection.polygon}){
                std::vector<Geometry::Point> copy = figurePtr.getPointsCopy();
                std::copy(copy.begin(), copy.end(), std::inserter(s, s.end()));
            }

            for (const Geometry::Point& pointPtr : s){
                DrawPoint(drawList, pointPtr, parameters, pos, DrawConst::WHITE_COLOR);
            }
        }
        ImGui::End();
    }

    inline void DrawProperties() {

        Manipulator::StatesLibrary &library = Manipulator::StatesLibrary::getInstance();
        figures_state_t figures = library.getStateCopy();

        // with this set to true, polygon can't be modified
        bool muted = true;

        ImGui::Begin("Properties", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
        {
            DisplayRevertButton();

            DisplayPolygon(figures.polygon1, "Polygon 1", States::FigureName::Polygon1);
            DisplayPolygon(figures.polygon2, "Polygon 2", States::FigureName::Polygon2);
            // intersections are forbidden from getting modified
            DisplayPolygon(figures.intersection.polygon, "Intersection", States::FigureName::Intersection, muted);
        }
        ImGui::End();
    }

    void DrawPoint(
        ImDrawList *drawList,
        const Geometry::Point& point, 
        const DrawUtils::scalingParameters& parameters, 
        const ImVec2& offset,
        const ImU32& col)
    {
        Geometry::Point drawnPoint = DrawUtils::scaleAndTranslatePoint(point, parameters);
        ImVec2 relativePoint = DrawUtils::getImVec2(drawnPoint, offset);
        drawList->AddCircleFilled(
            relativePoint,
            DrawConst::POINT_SIZE,
            col
        );
        drawList->AddText(
            nullptr, 
            DrawConst::LETTER_FONT_SIZE, 
            relativePoint,
            col,
            (" " + point.getLabel()).c_str()
        );
    }

    void DrawPolygon(
        ImDrawList *drawList,
        const Geometry::Polygon& polygon, 
        const DrawUtils::scalingParameters& parameters, 
        const ImVec2& offset, 
        const ImU32& col)
    {
        Geometry::Polygon drawnPolygon = DrawUtils::scaleAndTranslate(polygon, parameters);
        auto polygon_points = DrawUtils::getVectorOfPointsFromPolygon(drawnPolygon, offset);
        // draw the intersection
        if (polygon_points.size() >= 3)
            drawList->AddConvexPolyFilled(
                &polygon_points[0],
                (int) polygon_points.size(),
                col
            );

        else if (polygon_points.size() == 2)
            drawList->AddLine(
                polygon_points[0],
                polygon_points[1],
                col,
                DrawConst::LINE_THICKNESS
            );

        else if (polygon_points.size() == 1)
            drawList->AddCircleFilled(
                polygon_points[0], 
                DrawConst::INTERSECTION_POINT_SIZE, 
                col
            );
    }

    void DisplayPolygon(
            Geometry::Polygon &polygon,
            const std::string& title,
            States::FigureName figname,
            bool muted)
    {
        std::vector<Geometry::Point> &points1 = polygon.getPointsRef();
        ImGui::Text("%s", title.c_str());

        bool anyPointChanged = false;
        for (Geometry::Point& point : points1){
            if (DisplayPoint(point, muted))
                anyPointChanged = true;
            if (!muted) {
                ImGui::SameLine();
                DisplayDeleteButton(polygon, point, figname);
            }
        }
        polygon.sortPoints();
        if (anyPointChanged)
            Manipulator::StatesLibrary::getInstance().updateStateWith(polygon, figname);

        if (!muted) {
            DisplayAddButton(polygon, figname);
            // ImGui::SameLine();
            // if (polygon.size() >= 3)
        }
    }

    void HelpMarker(const char* desc)
    {
        ImGui::TextDisabled("(?)");
        if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayShort) && ImGui::BeginTooltip())
        {
            ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
            ImGui::TextUnformatted(desc);
            ImGui::PopTextWrapPos();
            ImGui::EndTooltip();
        }
    }
    
    bool ErrorMarker(const char* desc)
    {
        ImGui::TextDisabled("(!)");
        if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayShort) && ImGui::BeginTooltip())
        {
            if (ImGui::IsMouseDown(ImGuiMouseButton_Left)){
                return true;
            }
            ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
            ImGui::TextUnformatted(desc);
            ImGui::PopTextWrapPos();
            ImGui::EndTooltip();
        }
        return false;
        
    }

    void DisplayRevertButton() 
    {
        Manipulator::StatesLibrary &library = Manipulator::StatesLibrary::getInstance();
        ImGui::BeginDisabled(library.getSize() <= 1);
            if (ImGui::Button("Revert last change")) {
                library.popState();
            }
        ImGui::EndDisabled();
        ImGui::SameLine();
        HelpMarker(
            "It is recommended to revert any changes that create concave polygons as they aren't implemented properly yet and will cause issues.");
    }

    void DisplayAddButton(Geometry::Polygon& polygon, States::FigureName figname) {

        char x_buffer[DrawConst::BUFFER_SIZE];
        char y_buffer[DrawConst::BUFFER_SIZE];

        ImGui::Text("Add new point with coordinates:");
        
        // Name the button in the format "Add point PointName"        
        std::string labelNumber = std::to_string(polygon.size() + 1);
        size_t *labelChoices = DrawUtils::checkAvailableLabels(polygon);        
        // labeling with regard to possible missing numbers in point labels
        for (size_t j = 0; j < polygon.size() + 1; j++) {
            if (labelChoices[j] != -1){
                labelNumber = std::to_string(labelChoices[j]);
                break;
            }            
        }
        char labelLetter = polygon.getPointsRef().front().getLabel().front();
        std::string label = labelLetter + labelNumber;
        std::string name = "Add " + label;
        
        Geometry::Point front = polygon.getPointsRef().front();
        Geometry::Point back = polygon.getPointsRef().back();
        // offset the new point from the middle of section 
        auto offset = (float)pow((pow(front.getX() - back.getX(), 2) + pow(front.getX() - back.getX(), 2)), 0.5);
        Geometry::Point newPoint = Geometry::Point((front.getX() + back.getX())/2 + offset/5, (front.getY() + back.getY())/2);
        // DrawPoint();
        std::stringstream stream1;
        std::stringstream stream2;
        stream1 << std::fixed << std::setprecision(2) << newPoint.getX();
        stream2 << std::fixed << std::setprecision(2) << newPoint.getY();
        std::string s1 = stream1.str();
        std::string s2 = stream2.str();
        
        strcpy(x_buffer, s1.c_str());
        strcpy(y_buffer, s2.c_str());

        // Muted point coords name their points with " #"
        std::string fieldName = " " + label + ".x";
        
        // Width is in screen pixels
        ImGui::PushItemWidth(150);

        bool modified = false;
        bool changed = false;

        modified = ImGui::InputText(fieldName.c_str(), x_buffer, DrawConst::BUFFER_SIZE,
                            ImGuiInputTextFlags_CharsDecimal | ImGuiInputTextFlags_EnterReturnsTrue);

        if ((modified)and(newPoint.getX()!=atof(x_buffer))){ 
            newPoint.setX(atof(x_buffer));
        }

        ImGui::SameLine();
        fieldName = " " +  label + ".y";
        modified = ImGui::InputText(fieldName.c_str(), y_buffer, DrawConst::BUFFER_SIZE,
                            ImGuiInputTextFlags_CharsDecimal | ImGuiInputTextFlags_EnterReturnsTrue);

        if ((modified)and(newPoint.getY()!=atof(y_buffer))){
            newPoint.setY(atof(y_buffer));
        }
        // HSV stands for Hue/Saturation/Value
        ImGui::PushStyleColor(ImGuiCol_Button,
                              (ImVec4)ImColor::HSV(DrawConst::HSVGreenDefault.Hue,
                                                   DrawConst::HSVGreenDefault.Saturation,
                                                   DrawConst::HSVGreenDefault.Value
                                                   )
                             );
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered,
                              (ImVec4)ImColor::HSV(DrawConst::HSVGreenHovered.Hue,
                                                   DrawConst::HSVGreenHovered.Saturation,
                                                   DrawConst::HSVGreenHovered.Value
                                                   )
                             );
        ImGui::PushStyleColor(ImGuiCol_ButtonActive,
                              (ImVec4)ImColor::HSV(DrawConst::HSVGreenActive.Hue,
                                                   DrawConst::HSVGreenActive.Saturation,
                                                   DrawConst::HSVGreenActive.Value
                                                   )
                              );
        
        ImGui::SameLine();
        if (ImGui::Button(name.c_str())) {

            polygon.emplaceBack(newPoint);
            Manipulator::StatesLibrary::getInstance().updateStateWith(polygon, figname);
        }

        ImGui::PopStyleColor(3);
    }

    void DisplayDeleteButton(Geometry::Polygon& polygon, Geometry::Point& point, States::FigureName figname) {
        // HSV stands for Hue/Saturation/Value        
        ImGui::PushStyleColor(ImGuiCol_Button,
                              (ImVec4)ImColor::HSV(DrawConst::HSVRedDefault.Hue,
                                                   DrawConst::HSVRedDefault.Saturation,
                                                   DrawConst::HSVRedDefault.Value
                                                   )
                             );
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered,
                              (ImVec4)ImColor::HSV(DrawConst::HSVRedHovered.Hue,
                                                   DrawConst::HSVRedHovered.Saturation,
                                                   DrawConst::HSVRedHovered.Value
                                                   )
                              );
        ImGui::PushStyleColor(ImGuiCol_ButtonActive,
                              (ImVec4)ImColor::HSV(DrawConst::HSVRedActive.Hue,
                                                   DrawConst::HSVRedActive.Saturation,
                                                   DrawConst::HSVRedActive.Value
                                                   )
                             );
        
        ImGui::BeginDisabled((polygon.size() < 3));
            std::string label = point.getLabel();

            std::string name = "Delete " + label;
            if (ImGui::Button(name.c_str())){
                polygon.popAt(point);
                Manipulator::StatesLibrary::getInstance().updateStateWith(polygon, figname);
            }       
        ImGui::EndDisabled();

        ImGui::PopStyleColor(3);
    }

    bool DisplayPoint(Geometry::Point &point, bool muted) {

        int readonly = ImGuiInputTextFlags_None;
        if (muted) readonly = ImGuiInputTextFlags_ReadOnly;

        char x_buffer[DrawConst::BUFFER_SIZE];
        char y_buffer[DrawConst::BUFFER_SIZE];

        std::stringstream stream1;
        std::stringstream stream2;
        stream1 << std::fixed << std::setprecision(2) << point.getX();
        stream2 << std::fixed << std::setprecision(2) << point.getY();
        std::string s1 = stream1.str();
        std::string s2 = stream2.str();
        
        strcpy(x_buffer, s1.c_str());
        strcpy(y_buffer, s2.c_str());

        // Muted point coords name their points with " #"        
        std::string prefix = (muted) ? " #" : " ";
        std::string name = prefix + point.getLabel() + ".x";
        
        // Width is in screen pixels
        ImGui::PushItemWidth(150);

        bool modified = false;
        bool changed = false;

        modified = ImGui::InputText(name.c_str(), x_buffer, DrawConst::BUFFER_SIZE,
                            ImGuiInputTextFlags_CharsDecimal | ImGuiInputTextFlags_EnterReturnsTrue | readonly);

        if (!muted && modified && (point.getX()!=atof(x_buffer))){ 
            point.setX(atof(x_buffer));
            // Manipulator::StatesLibrary::getInstance().updateState();
            changed = true;
        }

        ImGui::SameLine();
        name = prefix + point.getLabel() + ".y";
        modified = ImGui::InputText(name.c_str(), y_buffer, DrawConst::BUFFER_SIZE,
                            ImGuiInputTextFlags_CharsDecimal | ImGuiInputTextFlags_EnterReturnsTrue | readonly);

        if (!muted && modified && (point.getY()!=atof(y_buffer))){
            point.setY(atof(y_buffer));
            // Manipulator::StatesLibrary::getInstance().updateState();
            changed = true;
        }

        

        return changed;
    }
}