#ifndef TRIANGLE_INTERSECTIONS_CONSTANTSFORDRAWING_H
#define TRIANGLE_INTERSECTIONS_CONSTANTSFORDRAWING_H

#include "imgui.h"

namespace DrawConst {

    struct scalingParameters {
        float Hue;
        float Saturation;
        float Value;
    };

    extern const scalingParameters HSVGreenDefault;
    extern const scalingParameters HSVGreenHovered;
    extern const scalingParameters HSVGreenActive;

    extern const scalingParameters HSVRedDefault;
    extern const scalingParameters HSVRedHovered;
    extern const scalingParameters HSVRedActive;

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
}
#endif //TRIANGLE_INTERSECTIONS_CONSTANTSFORDRAWING_H