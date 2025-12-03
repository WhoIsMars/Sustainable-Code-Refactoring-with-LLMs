#include "resistor_color.h"

inline int color_code(resistor_band_t color) 
{ 
    return color;
}

static const resistor_band_t colorArray[] = {
    BLACK, BROWN, RED, ORANGE, YELLOW, GREEN, BLUE, VIOLET, GREY, WHITE
};

const resistor_band_t *colors(void) { 
    return colorArray; 
}