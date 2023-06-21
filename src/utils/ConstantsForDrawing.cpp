#include "ConstantsForDrawing.h"

namespace DrawConst {

    const ColorParameters HSV_GREEN_DEFAULT = {2 / 7.0f, 0.6f, 0.6f};;
    const ColorParameters HSV_GREEN_HOVERED = {2 / 7.0f, 0.7f, 0.7f};
    const ColorParameters HSV_GREEN_ACTIVE = {2 / 7.0f, 0.8f, 0.8f};

    const ColorParameters HSV_RED_DEFAULT = {0 / 7.0f, 0.6f, 0.6f};;
    const ColorParameters HSV_RED_HOVERED = {0 / 7.0f, 0.7f, 0.7f};;
    const ColorParameters HSV_RED_ACTIVE = {0 / 7.0f, 0.8f, 0.8f};;

    const float LETTER_FONT_SIZE = 23.f;
    const float LINE_THICKNESS = 10.f;
    const float INTERSECTION_POINT_SIZE = 10.f;
    const float POINT_SIZE = 5.f;

    const float WINDOW_WIDTH = 1600;
    const float WINDOWS_HEIGHT = 900;
    const float DISPLAY_SIZE = 1600;
    const float DISPLAY_SCALE = 2;

    const float SQUARE_SIDE_SIZE = 800;

    constinit int BUFFER_SIZE = 32;

    const ImU32& RED_COLOR = IM_COL32(186, 36,  66, 255);
    const ImU32& GREEN_COLOR = IM_COL32(40,  156, 80, 255);
    const ImU32& YELLOW_COLOR = IM_COL32(204, 189, 12, 255);
    const ImU32& WHITE_COLOR = IM_COL32(255, 255, 255, 255);

    const std::string HEX_AND_HEX_DEMO_INPUT = std::string("6\n")
                                  + "(0, 900.0)\n"
                                  + "(800.0, 800.0)\n"
                                  + "(900.0, 400.0)\n"
                                  + "(800.0, 100.0)\n"
                                  + "(500.0, 0)\n"
                                  + "(100.0, 100.0)\n"
                                  + "6\n"
                                  + "(900.0, 0)\n"
                                  + "(0, 200.0)\n"
                                  + "(0, 500.0)\n"
                                  + "(100.0, 800.0)\n"
                                  + "(400.0, 900.0)\n"
                                  + "(700.0, 900.0)\n";

    const std::string TRIANGLE_AND_TRIANGLE_DEMO_INPUT = std::string("3\n")
                                            + "(200.0, 900.0)\n"
                                            + "(200.0, 200.0)\n"
                                            + "(900.0, 100.0)\n"
                                            + "3\n"
                                            + "(100.0, 800.0)\n"
                                            + "(500.0, 300.0)\n"
                                            + "(700.0, 500.0)\n";
}