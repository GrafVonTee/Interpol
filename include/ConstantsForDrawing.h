#ifndef TRIANGLE_INTERSECTIONS_CONSTANTSFORDRAWING_H
#define TRIANGLE_INTERSECTIONS_CONSTANTSFORDRAWING_H

#include <string>
#include "imgui.h"

namespace DrawConst {

    struct ColorParameters {
        float Hue;
        float Saturation;
        float Value;
    };

    extern const ColorParameters HSV_GREEN_DEFAULT;
    extern const ColorParameters HSV_GREEN_HOVERED;
    extern const ColorParameters HSV_GREEN_ACTIVE;

    extern const ColorParameters HSV_RED_DEFAULT;
    extern const ColorParameters HSV_RED_HOVERED;
    extern const ColorParameters HSV_RED_ACTIVE;

    extern const float LETTER_FONT_SIZE;
    extern const float LINE_THICKNESS;
    extern const float INTERSECTION_POINT_SIZE;
    extern const float POINT_SIZE;

    extern const float WINDOW_WIDTH;
    extern const float WINDOWS_HEIGHT;
    extern const float DISPLAY_SIZE;
    extern const float DISPLAY_SCALE;
    
    extern const float SQUARE_SIDE_SIZE;
    extern constinit int BUFFER_SIZE;

    extern const ImU32& RED_COLOR;
    extern const ImU32& GREEN_COLOR;
    extern const ImU32& YELLOW_COLOR;
    extern const ImU32& WHITE_COLOR;

    extern const std::string HEX_AND_HEX_DEMO_INPUT;
    extern const std::string TRIANGLE_AND_TRIANGLE_DEMO_INPUT;
}
#endif //TRIANGLE_INTERSECTIONS_CONSTANTSFORDRAWING_H